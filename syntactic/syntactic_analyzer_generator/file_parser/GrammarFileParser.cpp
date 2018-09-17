//
// Created by programajor on 4/18/18.
//

#include <vector>
#include <string>
#include "../models/GrammarElement.h"
#include "GrammarFileParser.h"
#include "../../../utils/Utils.h"
#include "../models/NonTerminal.h"

using namespace std;

enum LineType {FULL, LEFT, MIDDLE, RIGHT, LEFT_MIDDLE, RIGHT_MIDDLE};

const regex fullExpressionLine = regex("^\\s*#\\s*([A-Za-z0-9_'#:=\\\\]*)\\s*\\:\\:\\=\\s*(.*)\\s*");
const regex leftPartExpressionLine = regex("^\\s*#\\s*([A-Za-z0-9_'#:=\\\\]*)\\s*");
const regex leftAndEqualExpressionLine = regex("^\\s*#\\s*([A-Za-z0-9_'#:=\\\\]*)\\s*\\:\\:\\=\\s*");
const regex EqualPartExpressionLine = regex("\\s*\\:\\:\\=\\s*");
const regex rightPartExpressionLine = regex("\\s*(.*)\\s*");
const regex rightAndEqualExpressionLine = regex("\\s*\\:\\:\\=\\s*(.*)\\s*");

std::vector <string> GrammarFileParser::parse_grammar_file(
        vector < GrammarElement * > *rules, unordered_set <GrammarExpression * > *expressions,
        ifstream * lexical_file_stream, unordered_set <string> *terminals,
        unordered_set < string > *non_terminals, GrammarElement ** startRule) {
    string line;
    vector<string> lines;
    vector<string> errors;
    map<string, NonTerminal*> nameToNonTerminal;
    map<string, GrammarElement*> nameToTerminal;
    if (lexical_file_stream->is_open()) {
        LineType prevLineType = FULL;
        GrammarElement* prevGrammarElement = nullptr;
        string rightHandSide = "";
        bool leftDefineFound = false;
        while (getline (*lexical_file_stream, line)) {
            smatch matcher;
            lines.push_back(line);
            if (line.empty()) {
                continue;
            } else if (regex_match(line, fullExpressionLine)) {
                if (prevLineType == LEFT_MIDDLE || prevLineType == MIDDLE) {
                    addError(&errors , "Multiple Equal Signs", lines.size());
                }
                parseRightHandSide(rightHandSide, terminals, non_terminals, &nameToNonTerminal, &nameToTerminal, rules, prevGrammarElement,
                                   &errors, lines.size());
                rightHandSide = "";
                prevGrammarElement = insertNonTerminal(line, fullExpressionLine, &nameToNonTerminal,
                                                       matcher, rules, prevGrammarElement, startRule, non_terminals, &errors, lines.size());
                regex_search(line, matcher, fullExpressionLine);
                bool error = isValidatRightHandSide(matcher[2], &errors, lines.size());
                if (!error) {
                    rightHandSide += matcher[2];
                }
                prevLineType = FULL;
                leftDefineFound = true;
            } else if (regex_match(line, leftAndEqualExpressionLine)) {
                if (prevLineType == LEFT_MIDDLE || prevLineType == MIDDLE) {
                    addError(&errors, "Multiple Equal Signs", lines.size());
                }
                parseRightHandSide(rightHandSide, terminals, non_terminals, &nameToNonTerminal, &nameToTerminal, rules, prevGrammarElement,
                                   &errors, lines.size());
                rightHandSide = "";
                prevGrammarElement = insertNonTerminal(line, leftAndEqualExpressionLine, &nameToNonTerminal,
                                                       matcher, rules, prevGrammarElement, startRule, non_terminals,
                                                       &errors, lines.size());
                prevLineType = LEFT_MIDDLE;
                leftDefineFound = true;
            } else if (regex_match(line, rightAndEqualExpressionLine)) {
                if (prevLineType == LEFT_MIDDLE) {
                    addError(&errors, "Multiple Equal Signs", lines.size());
                } else if (prevLineType != LEFT) {
                    addError(&errors, "Non Terminal not Available, Cannot start with equal", lines.size());
                }
                regex_search(line, matcher, rightAndEqualExpressionLine);
                bool error = isValidatRightHandSide(matcher[1], &errors, lines.size());
                if (!error) {
                    rightHandSide += matcher[1];
                }
                prevLineType = RIGHT_MIDDLE;
            } else if (regex_match(line, leftPartExpressionLine)) {
                if (prevLineType == LEFT || prevLineType == LEFT_MIDDLE) {
                    addError(&errors, "No RHS for non terminal", lines.size() - 1);
                }
                parseRightHandSide(rightHandSide, terminals, non_terminals, &nameToNonTerminal, &nameToTerminal, rules, prevGrammarElement,
                                   &errors, lines.size());
                rightHandSide = "";
                prevGrammarElement = insertNonTerminal(line, leftPartExpressionLine, &nameToNonTerminal,
                                                       matcher, rules, prevGrammarElement, startRule, non_terminals,
                                                       &errors, lines.size());
                prevLineType = LEFT;
                leftDefineFound = true;
            } else if (regex_match(line, rightPartExpressionLine)) {
                if (!leftDefineFound) {
                    addError(&errors, "No Definition for RHS found transition should start with #", lines.size() );
                } else if (prevLineType == LEFT || rules->size() == 0) {
                    addError(&errors, "No EQUAL sign for non terminal", lines.size() - 1);
                }
                regex_search(line, matcher, rightPartExpressionLine);
                bool error = isValidatRightHandSide(matcher[1], &errors, lines.size());
                if (!error) {
                    rightHandSide += matcher[1];
                }
                prevLineType = RIGHT;
            } else if (regex_match(line, EqualPartExpressionLine)) {
                if (prevLineType == LEFT_MIDDLE) {
                    addError(&errors, "Multiple Equal Signs", lines.size());
                } else if (prevLineType != LEFT) {
                    addError(&errors, "Non Terminal not Available, Cannot start with equal", lines.size());
                }
                prevLineType = MIDDLE;
            } else {
                addError(&errors, "Invalid Line Syntax", lines.size());
            }
        }
        if (!rightHandSide.empty()) {
            parseRightHandSide(rightHandSide, terminals, non_terminals,
                               &nameToNonTerminal, &nameToTerminal, rules, prevGrammarElement, &errors, lines.size());
        }
    } else {
        errors.push_back("Input Stream is Closed");
    }

    for (int i = 0; i < rules->size(); ++i) {
        NonTerminal* nonTerminal = static_cast<NonTerminal *> ((*rules)[i]);
        if (!nonTerminal->eps && nonTerminal->leads_to.size() == 0) {
            errors.push_back("Non terminal " + nonTerminal->getName()
                             + " doesn't lead to any expressions");
        }
        for (int j = 0; j < nonTerminal->leads_to.size(); ++j) {
            expressions->insert(nonTerminal->leads_to[j]);
        }
    }

    for (auto it = terminals->begin(); it != terminals->end(); it++) {
        GrammarElement* terminal = nameToTerminal[*it];
        rules->push_back(terminal);
    }

    return errors;
}

GrammarElement * GrammarFileParser::insertNonTerminal(string line, const regex pattern, map<string, NonTerminal *> *nameToNonTerminal, smatch matcher,
                                                      vector<GrammarElement *> *rules, GrammarElement *prevGrammarElement, GrammarElement **startRule,
                                                      unordered_set<string> *non_terminals, vector<string> *errors, int lineMum) {
    regex_search(line, matcher, pattern);
    string temp = matcher[1];
    string name = "";
    for (int i = 0; i < temp.length(); ++i) {
        bool isSpecial = isQuote(temp[i]) || temp[i] == '#' || temp[i] == '|' || temp[i] == ':' || temp[i] == '=';
        if (isSpecial && (i == 0 || temp[i - 1] != '\\')) {
            addError(errors, temp[i] + " is a reserved char and must be preceeded with \\" , lineMum);
        } else if (isSpecial) {
            name[name.length() - 1] = temp[i];
        } else {
            name += temp[i];
        }
    }

    if (nameToNonTerminal->find(name) == nameToNonTerminal->end()) {
        GrammarElement* element = new NonTerminal(name, NON_TERMINAL);
        (*nameToNonTerminal)[name] = static_cast<NonTerminal*> (element);
        static_cast<NonTerminal*> (element)->eps = false;
        rules->push_back(element);
        non_terminals->insert(name);
        if (prevGrammarElement == nullptr) {
            *startRule = element;
        }
        return element;
    } else {
        return (*nameToNonTerminal)[name];
    }
}

void GrammarFileParser::addError(vector<string> *errors, string error, int lineNumber) {
    errors->push_back("ERROR: " + error + " at line " + to_string(lineNumber));
}

void GrammarFileParser::parseRightHandSide(string rightHandSide, unordered_set<string> *terminals, unordered_set<string> *non_terminals,
                                           map<string, NonTerminal *> *nameToNonTerminal, map<string, GrammarElement *> *nameToTerminal, vector<GrammarElement *> *rules,
                                           GrammarElement *prevGrammarElement, vector<string> *errors, int lineMum) {
    vector<string> strings = splitOrs(rightHandSide, errors);
    if (strings.size() != 0) {
        for (int i = 0; i < strings.size(); i++) {
            GrammarExpression* expression = new GrammarExpression(prevGrammarElement);
            vector<string> terminalsAndNonTerminals = split_spaces(strings[i]);
            bool isEpslon = false;
            for (int j = 0; j < terminalsAndNonTerminals.size(); ++j) {
                string curr = terminalsAndNonTerminals[j];
                if (curr.empty()) {
                    addError(errors, "Empty Element", lineMum);
                    continue;
                }
                bool quoteFound = false;
                string temp = "";
                for (int k = 0; k < curr.length(); ++k) {
                    if (isQuote(curr[k]) && (k == 0 || curr[k - 1] != '\\')) {
                        if (!quoteFound && !temp.empty()) {
                            if (nameToNonTerminal->find(temp) == nameToNonTerminal->end()) {
                                GrammarElement* element = new NonTerminal(temp, NON_TERMINAL);
                                (*nameToNonTerminal)[temp] = static_cast<NonTerminal *>(element);
                                static_cast<NonTerminal*> (element)->eps = false;
                                rules->push_back(element);
                                non_terminals->insert(temp);
                            }
                            expression->expression.push_back(static_cast<GrammarElement *> ((*nameToNonTerminal)[temp]));
                            (*nameToNonTerminal)[temp]->referenced_in.push_back(expression);
                            temp = "";
                            quoteFound = true;
                            continue;
                        }
                        if (quoteFound) {
                            if (temp.empty()) {
                                addError(errors, "Empty Terminal", lineMum);
                                continue;
                            } else {
                                if (temp == "\\L" && expression->expression.size() == 0
                                    && prevGrammarElement != nullptr) {
                                    isEpslon = true;
                                } else {
                                    isEpslon = false;
                                    if (nameToTerminal->find(temp) == nameToTerminal->end()) {
                                        GrammarElement* element = new GrammarElement(temp, TERMINAL);
                                        terminals->insert(temp);
                                        (*nameToTerminal)[temp] = element;
                                    }
                                    expression->expression.push_back((*nameToTerminal)[temp]);
                                    temp = "";
                                }
                            }
                            quoteFound = false;
                        } else {
                            quoteFound = true;
                        }
                    } else if (isQuote(curr[k]) && k > 0 && curr[k - 1] == '\\') {
                        temp[temp.length() - 1] = curr[k];
                    } else if((curr[k] == '=' || curr[k] == ':' || curr[k] == '#') && k > 0 && curr[k - 1] == '\\') {
                        temp[temp.length() - 1] = curr[k];
                    } else if((curr[k] == '=' || curr[k] == ':' || curr[k] == '#') && (k == 0 || curr[k - 1] != '\\')) {
                        addError(errors, curr[k] + " is a reserved char and must be preceeded with \\" , lineMum);
                    } else {
                        temp += curr[k];
                    }
                }
                if (quoteFound) {
                    addError(errors, "Terminals Cannot have spaces", lineMum);
                } else if (!temp.empty() && temp != "\\L") {
                    if (nameToNonTerminal->find(temp) == nameToNonTerminal->end()) {
                        GrammarElement* element = new NonTerminal(temp, NON_TERMINAL);
                        (*nameToNonTerminal)[temp] = static_cast<NonTerminal *>(element);
                        static_cast<NonTerminal*> (element)->eps = false;
                        rules->push_back(element);
                        non_terminals->insert(temp);
                    }
                    expression->expression.push_back(static_cast<GrammarElement *> ((*nameToNonTerminal)[temp]));
                    (*nameToNonTerminal)[temp]->referenced_in.push_back(expression);
                    temp = "";
                }
            }
            if (isEpslon && expression->expression.size() == 0 && prevGrammarElement != nullptr) {
                static_cast<NonTerminal*> (prevGrammarElement)->eps = true;
                delete expression;
            } else if (prevGrammarElement != nullptr) {
                static_cast<NonTerminal*> (prevGrammarElement)->leads_to.push_back(expression);
            }
        }
    }
}

bool GrammarFileParser::isValidatRightHandSide(string rightHandSide, vector<string> *errors, int lineNumber) {
    int quotesCount = 0;
    for (int i = 0; i < rightHandSide.length(); ++i) {
        if (isQuote(rightHandSide[i] && (i == 0 || rightHandSide[i] != '\\'))) {
            quotesCount++;
        }
    }
    if (quotesCount % 2 == 0) {
        return false;
    } else {
        addError(errors, "Unclosed Quote, INVALID RHS", lineNumber);
        return true;
    }
}

bool GrammarFileParser::isQuote(char c) {
    return c == '\'';
}

vector<string> GrammarFileParser::splitOrs(string curr, vector<string> *errors) {
    vector<string> ret;
    string temp = "";
    if (curr.length() == 0) return ret;
    if (curr[0] == '|') {
        errors->push_back("Cannot start RHS with |");
    } else if (curr[curr.length() - 1] == '|') {
        errors->push_back("Cannot end RHS with |");
    } else {
        for (int j = 0; j < curr.length(); ++j) {
            if (j > 0 && curr[j] != '\\' && curr[j] == '|') {
                ret.push_back(temp);
                temp = "";
            } else {
                temp += curr[j];
            }
        }
        if (!temp.empty()) {
            ret.push_back(temp);
            temp = "";
        }
    }
    return ret;
}
