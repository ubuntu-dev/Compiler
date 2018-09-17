/*
 * GrammarFileParser.h
 *
 *  Created on: Apr 17, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_FILE_PARSER_GRAMMARFILEPARSER_H_
#define SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_FILE_PARSER_GRAMMARFILEPARSER_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_set>
#include "../models/GrammarElement.h"
#include "../models/GrammarExpression.h"
#include "../models/NonTerminal.h"

using namespace std;

class GrammarFileParser {
public:
    // Will return vector of errors, empty if no errors.
    vector<string> parse_grammar_file(vector<GrammarElement *> *rules, unordered_set<GrammarExpression *> * expressions,
                                      ifstream * lexical_file_stream, unordered_set<string> *terminals,
                                      unordered_set<string> *non_terminals, GrammarElement ** startRule);

private:
    static const regex startExpressionLine;
    static const regex continueExpressionLine;

    void addError(vector<string> *errors, string error, int lineNumber);

//    GrammarElement *
//    insertNonTerminal(string line, regex pattern, map<string, NonTerminal *> nameToExpression, smatch matcher,
//                          vector<GrammarElement *> *rules, GrammarElement *pElement, GrammarElement *pGrammarElement,
//                          unordered_set<string> *pSet);

//    void parseRightHandSide(string rightHandSide, unordered_set<string> *terminals, unordered_set<string> *non_terminals,
//                                map<string, NonTerminal *> nameToExpression, vector<GrammarElement *> *rules,
//                                GrammarElement *prevGrammarElement, vector<string> *pVector);

    bool isValidatRightHandSide(string match, vector<string> *errors, int lineNumber);

    bool isQuote(char c);

//    vector<vector<string>> splitOrs(vector<string> strings, vector<string> *errors);

//    void parseRightHandSide(string rightHandSide, unordered_set<string> *terminals, unordered_set<string> *non_terminals,
//                            map<string, NonTerminal *> nameToExpression, vector<GrammarElement *> *rules,
//                            GrammarElement *prevGrammarElement, vector<string> *errors, int lineMum);

    void parseRightHandSide(string rightHandSide, unordered_set<string> *terminals, unordered_set<string> *non_terminals,
                            map<string, NonTerminal *> *nameToNonTerminal, map<string, GrammarElement *> *nameToTerminal, vector<GrammarElement *> *rules,
                            GrammarElement *prevGrammarElement, vector<string> *errors, int lineMum);

//    void parseRightHandSide(string rightHandSide, unordered_set<string> *terminals, unordered_set<string> *non_terminals,
//                            map<string, NonTerminal *> *nameToExpression, vector<GrammarElement *> *rules,
//                            GrammarElement *prevGrammarElement, vector<string> *errors);

    GrammarElement *
    insertNonTerminal(string line, const regex pattern, map<string, NonTerminal *> *nameToNonTerminal, smatch matcher,
                      vector<GrammarElement *> *rules, GrammarElement *prevGrammarElement, GrammarElement **startRule,
                      unordered_set<string> *non_terminals, vector<string> *errors, int lineMum);

    vector<string> splitOrs(string curr, vector<string> *errors);
};


#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_FILE_PARSER_GRAMMARFILEPARSER_H_ */
