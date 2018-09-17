/*
 * GrammarFileParserTest.cpp
 *
 *  Created on: Apr 18, 2018
 *      Author: amrnasr
 */

#include "../../../test_headers/p2_tests.h"

#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <vector>
#include "GrammarFileParser.h"

void projectPdfTestCase();

void sheetThreeProblemThreeTestCase();
void sheetThreeProblemFourTestCase();

bool compareRules(vector<GrammarElement *> *rules, vector<GrammarElement *> *expectedRules);
bool compareSets(unordered_set<string> *real, unordered_set<string> *expected);

using namespace std;

void test_grammar_file_parser() {
    sheetThreeProblemThreeTestCase();
    sheetThreeProblemFourTestCase();
    projectPdfTestCase();
}


void sheetThreeProblemThreeTestCase() {
    GrammarFileParser fileParser;
    ifstream infile;
    infile.open("./test_files/syntatic_grammar_parser/sheet_3_problem_3.txt");
    if (!infile) {
        cout << "GRAMMAR PARSER TEST : COULDN\"T OPEN WANTED FILE" << endl;
        return;
    }
    vector<GrammarElement *> rules;
    unordered_set<GrammarExpression *> expressions;
    unordered_set<string> terminals;
    unordered_set<string> non_terminals;
    GrammarElement *startRule;

    GrammarElement* EE = new NonTerminal("E", NON_TERMINAL);
    NonTerminal* E = static_cast<NonTerminal*>(EE);
    E->eps = false;

    GrammarElement* TE = new NonTerminal("T", NON_TERMINAL);
    NonTerminal* T = static_cast<NonTerminal*>(TE);
    T->eps = false;

    GrammarElement* EDE = new NonTerminal("E'", NON_TERMINAL);
    NonTerminal* ED = static_cast<NonTerminal*>(EDE);
    ED->eps = true;

    GrammarElement* FE = new NonTerminal("F", NON_TERMINAL);
    NonTerminal* F = static_cast<NonTerminal*>(FE);
    F->eps = false;

    GrammarElement* TDE = new NonTerminal("T'", NON_TERMINAL);
    NonTerminal* TD = static_cast<NonTerminal*>(TDE);
    TD->eps = true;

    GrammarElement* PE = new NonTerminal("P", NON_TERMINAL);
    NonTerminal* P = static_cast<NonTerminal*>(PE);
    P->eps = false;

    GrammarElement* FDE = new NonTerminal("F'", NON_TERMINAL);
    NonTerminal* FD = static_cast<NonTerminal*>(FDE);
    FD->eps = true;

    GrammarElement* plus = new GrammarElement("+", TERMINAL);
    GrammarElement* star = new GrammarElement("*", TERMINAL);
    GrammarElement* open = new GrammarElement("(", TERMINAL);
    GrammarElement* close = new GrammarElement(")", TERMINAL);
    GrammarElement* a = new GrammarElement("a", TERMINAL);
    GrammarElement* b = new GrammarElement("b", TERMINAL);
    GrammarElement* Em = new GrammarElement("Em", TERMINAL);

    GrammarExpression* ex1 = new GrammarExpression(E);
    ex1->expression = {T, ED};
    E->leads_to.push_back(ex1);

    GrammarExpression* ex2 = new GrammarExpression(T);
    ex2->expression = {F, TD};
    T->leads_to.push_back(ex2);

    GrammarExpression* ex3 = new GrammarExpression(ED);
    ex3->expression = {plus, E};
    ED->leads_to.push_back(ex3);

    GrammarExpression* ex4 = new GrammarExpression(F);
    ex4->expression = {P, FD};
    F->leads_to.push_back(ex4);

    GrammarExpression* ex5 = new GrammarExpression(TD);
    ex5->expression = {T};
    TD->leads_to.push_back(ex5);

    GrammarExpression* ex6 = new GrammarExpression(P);
    ex6->expression = {open, E, close};
    P->leads_to.push_back(ex6);

    GrammarExpression* ex7 = new GrammarExpression(P);
    ex7->expression = {a};
    P->leads_to.push_back(ex7);

    GrammarExpression* ex8 = new GrammarExpression(P);
    ex8->expression = {b};
    P->leads_to.push_back(ex8);

    GrammarExpression* ex9 = new GrammarExpression(P);
    ex9->expression = {Em};
    P->leads_to.push_back(ex9);

    GrammarExpression* ex10 = new GrammarExpression(FD);
    ex10->expression = {star, F};
    FD->leads_to.push_back(ex10);

    vector<GrammarElement *> expectedRules = {EE, TE, EDE, FE, TDE, PE, FDE, plus, star, open,
                                              close, a, b, Em};

    vector<string> errors = fileParser.parse_grammar_file(&rules, &expressions, &infile,
                                                          &terminals, &non_terminals, &startRule);

    unordered_set<string> expectedNonTerminals = {"E", "E'", "T", "T'", "F", "F'", "P"};
    unordered_set<string> expectedTerminals = {"+", "*'", "(", ")'", "a", "b'", "Em"};

    if (!errors.size() == 0) {
        cout << "Syntactic Grammar Parser Errors: " + to_string(errors.size()) + " errors detected" << endl;
        for (int i = 0; i < errors.size(); ++i) {
            cout << errors[i] << endl;
        }
    }

    bool error = compareSets(&non_terminals, &expectedNonTerminals);
    error |= compareSets(&terminals, &expectedTerminals);
    error |= compareRules(&rules, &expectedRules);
    if (error) {
        cout << "Sheet 3 problem 3 parsing error" << endl;
    } else {
        cout << "Sheet 3 problem 3 parsing success" << endl;
    }
}

void sheetThreeProblemFourTestCase() {
    GrammarFileParser fileParser;
    ifstream infile;
    infile.open("./test_files/syntatic_grammar_parser/sheet_3_problem_4.txt");
    if (!infile) {
        cout << "GRAMMAR PARSER TEST : COULDN\"T OPEN WANTED FILE" << endl;
        return;
    }
    vector<GrammarElement *> rules;
    unordered_set<GrammarExpression *> expressions;
    unordered_set<string> terminals;
    unordered_set<string> non_terminals;
    GrammarElement *startRule;

    GrammarElement* SE = new NonTerminal("S", NON_TERMINAL);
    NonTerminal* S = static_cast<NonTerminal*>(SE);
    S->eps = false;
    GrammarElement* RE = new NonTerminal("R", NON_TERMINAL);
    NonTerminal* R = static_cast<NonTerminal*>(RE);
    R->eps = true;
    GrammarElement* TE = new NonTerminal("T", NON_TERMINAL);
    NonTerminal* T = static_cast<NonTerminal*>(TE);
    T->eps = true;
    GrammarElement* UE = new NonTerminal("U", NON_TERMINAL);
    NonTerminal* U = static_cast<NonTerminal*>(UE);
    U->eps = true;
    GrammarElement* VE = new NonTerminal("V", NON_TERMINAL);
    NonTerminal* V = static_cast<NonTerminal*>(VE);
    V->eps = true;

    GrammarElement* s = new GrammarElement("s", TERMINAL);
    GrammarElement* b = new GrammarElement("b", TERMINAL);
    GrammarElement* t = new GrammarElement("t", TERMINAL);
    GrammarElement* u = new GrammarElement("u", TERMINAL);
    GrammarElement* v = new GrammarElement("v", TERMINAL);

    GrammarExpression* ex1 = new GrammarExpression(S);
    ex1->expression = {R, T};
    S->leads_to.push_back(ex1);

    GrammarExpression* ex2 = new GrammarExpression(R);
    ex2->expression = {s, U, R, b};
    R->leads_to.push_back(ex2);

    GrammarExpression* ex3 = new GrammarExpression(T);
    ex3->expression = {V, t, T};
    T->leads_to.push_back(ex3);

    GrammarExpression* ex4 = new GrammarExpression(U);
    ex4->expression = {u, U};
    U->leads_to.push_back(ex4);

    GrammarExpression* ex5 = new GrammarExpression(V);
    ex5->expression = {v, V};
    V->leads_to.push_back(ex5);

    vector<GrammarElement *> expectedRules = {SE, RE, TE, UE, VE, s, b, t, u, v};

    vector<string> errors = fileParser.parse_grammar_file(&rules, &expressions, &infile,
                                                          &terminals, &non_terminals, &startRule);

    unordered_set<string> expectedNonTerminals = {"T", "R", "S", "U", "V"};
    unordered_set<string> expectedTerminals = {"t", "r", "s", "u", "v"};

    if (!errors.size() == 0) {
        cout << "Syntactic Grammar Parser Errors: " + to_string(errors.size()) + " errors detected" << endl;
        for (int i = 0; i < errors.size(); ++i) {
            cout << errors[i] << endl;
        }
    }

    bool error = compareSets(&non_terminals, &expectedNonTerminals);
    error |= compareSets(&terminals, &expectedTerminals);
    error |= compareRules(&rules, &expectedRules);
    if (error) {
        cout << "Sheet 3 problem 4 parsing error" << endl;
    } else {
        cout << "Sheet 3 problem 4 parsing success" << endl;
    }
}

void projectPdfTestCase() {
    GrammarFileParser fileParser;
    ifstream infile;
    infile.open("./test_files/syntatic_grammar_parser/correct_rules.txt");
    if (!infile) {
        cout << "GRAMMAR PARSER TEST : COULDN\"T OPEN WANTED FILE" << endl;
        return;
    }
    vector<GrammarElement *> rules;
    unordered_set<GrammarExpression *> expressions;
    unordered_set<string> terminals;
    unordered_set<string> non_terminals;
    GrammarElement *startRule;

    GrammarElement *METHOD_BODY_E = new NonTerminal("METHOD_BODY", NON_TERMINAL);
    GrammarElement *STATEMENT_LIST_E = new NonTerminal("STATEMENT_LIST", NON_TERMINAL);
    GrammarElement *STATEMENT_E = new NonTerminal("STATEMENT", NON_TERMINAL);
    GrammarElement *DECLARATION_E = new NonTerminal("DECLARATION", NON_TERMINAL);
    GrammarElement *IF_E = new NonTerminal("IF", NON_TERMINAL);
    GrammarElement *WHILE_E = new NonTerminal("WHILE", NON_TERMINAL);
    GrammarElement *ASSIGNMENT_E = new NonTerminal("ASSIGNMENT", NON_TERMINAL);
    GrammarElement *PRIMITIVE_TYPE_E = new NonTerminal("PRIMITIVE_TYPE", NON_TERMINAL);
    GrammarElement *EXPRESSION_E = new NonTerminal("EXPRESSION", NON_TERMINAL);
    GrammarElement *SIMPLE_EXPRESSION_E = new NonTerminal("SIMPLE_EXPRESSION", NON_TERMINAL);
    GrammarElement *TERM_E = new NonTerminal("TERM", NON_TERMINAL);
    GrammarElement *SIGN_E = new NonTerminal("SIGN", NON_TERMINAL);
    GrammarElement *FACTOR_E = new NonTerminal("FACTOR", NON_TERMINAL);

    NonTerminal *METHOD_BODY = static_cast<NonTerminal *>(METHOD_BODY_E);
    NonTerminal *STATEMENT_LIST = static_cast<NonTerminal *>(STATEMENT_LIST_E);
    NonTerminal *STATEMENT = static_cast<NonTerminal *>(STATEMENT_E);
    NonTerminal *DECLARATION = static_cast<NonTerminal *>(DECLARATION_E);
    NonTerminal *IF = static_cast<NonTerminal *>(IF_E);
    NonTerminal *WHILE = static_cast<NonTerminal *>(WHILE_E);
    NonTerminal *ASSIGNMENT = static_cast<NonTerminal *>(ASSIGNMENT_E);
    NonTerminal *PRIMITIVE_TYPE = static_cast<NonTerminal *>(PRIMITIVE_TYPE_E);
    NonTerminal *EXPRESSION = static_cast<NonTerminal *>(EXPRESSION_E);
    NonTerminal *SIMPLE_EXPRESSION = static_cast<NonTerminal *>(SIMPLE_EXPRESSION_E);
    NonTerminal *TERM = static_cast<NonTerminal *>(TERM_E);
    NonTerminal *SIGN = static_cast<NonTerminal *>(SIGN_E);
    NonTerminal *FACTOR = static_cast<NonTerminal *>(FACTOR_E);
    METHOD_BODY->eps = false;
    STATEMENT_LIST->eps = false;
    STATEMENT->eps = false;
    DECLARATION->eps = false;
    IF->eps = false;
    WHILE->eps = false;
    ASSIGNMENT->eps = false;
    PRIMITIVE_TYPE->eps = false;
    EXPRESSION->eps = false;
    SIMPLE_EXPRESSION->eps = false;
    TERM->eps = false;
    SIGN->eps = false;
    FACTOR->eps = false;

    GrammarElement* id_terminal = new GrammarElement("id", TERMINAL);
    GrammarElement* semicolon_terminal = new GrammarElement(";", TERMINAL);
    GrammarElement* int_terminal = new GrammarElement("int", TERMINAL);
    GrammarElement* float_terminal = new GrammarElement("float", TERMINAL);
    GrammarElement* if_terminal = new GrammarElement("if", TERMINAL);
    GrammarElement* openBracket_terminal = new GrammarElement("(", TERMINAL);
    GrammarElement* closedBracket_terminal = new GrammarElement(")", TERMINAL);
    GrammarElement* openCurlyBracket_terminal = new GrammarElement("{", TERMINAL);
    GrammarElement* closedCurlyBracket_terminal = new GrammarElement("}", TERMINAL);
    GrammarElement* else_terminal = new GrammarElement("else", TERMINAL);
    GrammarElement* while_terminal = new GrammarElement("while", TERMINAL);
    GrammarElement* relop_terminal = new GrammarElement("relop", TERMINAL);
    GrammarElement* addop_terminal = new GrammarElement("addop", TERMINAL);
    GrammarElement* mulop_terminal = new GrammarElement("mulop", TERMINAL);
    GrammarElement* equal_terminal = new GrammarElement("=", TERMINAL);
    GrammarElement* num_terminal = new GrammarElement("num", TERMINAL);
    GrammarElement* plus_terminal = new GrammarElement("+", TERMINAL);
    GrammarElement* minus_terminal = new GrammarElement("-", TERMINAL);

    GrammarExpression* ex1 = new GrammarExpression(METHOD_BODY);
    ex1->expression = {STATEMENT_LIST};
    METHOD_BODY->leads_to.push_back(ex1);

    GrammarExpression* ex2 = new GrammarExpression(STATEMENT_LIST);
    ex2->expression = {STATEMENT};
    STATEMENT_LIST->leads_to.push_back(ex2);

    GrammarExpression* ex3 = new GrammarExpression(STATEMENT_LIST);
    ex3->expression = {STATEMENT_LIST, STATEMENT};
    STATEMENT_LIST->leads_to.push_back(ex3);

    GrammarExpression* ex4 = new GrammarExpression(STATEMENT);
    ex4->expression = {DECLARATION};
    STATEMENT->leads_to.push_back(ex4);

    GrammarExpression* ex5 = new GrammarExpression(STATEMENT);
    ex5->expression = {IF};
    STATEMENT->leads_to.push_back(ex5);

    GrammarExpression* ex6 = new GrammarExpression(STATEMENT);
    ex6->expression = {WHILE};
    STATEMENT->leads_to.push_back(ex6);

    GrammarExpression* ex7 = new GrammarExpression(STATEMENT);
    ex7->expression = {ASSIGNMENT};
    STATEMENT->leads_to.push_back(ex7);

    GrammarExpression* ex8 = new GrammarExpression(DECLARATION);
    ex8->expression = {PRIMITIVE_TYPE, id_terminal, semicolon_terminal};
    DECLARATION->leads_to.push_back(ex8);

    GrammarExpression* ex9 = new GrammarExpression(IF);
    ex9->expression = {if_terminal, openBracket_terminal, EXPRESSION, closedBracket_terminal,
                       openCurlyBracket_terminal, STATEMENT, closedCurlyBracket_terminal,
                       else_terminal, openCurlyBracket_terminal, STATEMENT,
                       closedCurlyBracket_terminal};
    IF->leads_to.push_back(ex9);

    GrammarExpression* ex10 = new GrammarExpression(WHILE);
    ex10->expression = {while_terminal, openBracket_terminal, EXPRESSION, closedBracket_terminal,
                        openCurlyBracket_terminal, STATEMENT, closedCurlyBracket_terminal};
    WHILE->leads_to.push_back(ex10);

    GrammarExpression* ex11 = new GrammarExpression(ASSIGNMENT);
    ex11->expression = {id_terminal, equal_terminal, EXPRESSION, semicolon_terminal};
    ASSIGNMENT->leads_to.push_back(ex11);

    GrammarExpression* ex12 = new GrammarExpression(PRIMITIVE_TYPE);
    ex12->expression = {int_terminal};
    PRIMITIVE_TYPE->leads_to.push_back(ex12);

    GrammarExpression* ex13 = new GrammarExpression(PRIMITIVE_TYPE);
    ex13->expression = {float_terminal};
    PRIMITIVE_TYPE->leads_to.push_back(ex13);

    GrammarExpression* ex14 = new GrammarExpression(EXPRESSION);
    ex14->expression = {SIMPLE_EXPRESSION};
    EXPRESSION->leads_to.push_back(ex14);

    GrammarExpression* ex15 = new GrammarExpression(EXPRESSION);
    ex15->expression = {SIMPLE_EXPRESSION, relop_terminal, SIMPLE_EXPRESSION};
    EXPRESSION->leads_to.push_back(ex15);

    GrammarExpression* ex16 = new GrammarExpression(SIMPLE_EXPRESSION);
    ex16->expression = {TERM};
    SIMPLE_EXPRESSION->leads_to.push_back(ex16);

    GrammarExpression* ex17 = new GrammarExpression(SIMPLE_EXPRESSION);
    ex17->expression = {SIGN, TERM};
    SIMPLE_EXPRESSION->leads_to.push_back(ex17);

    GrammarExpression* ex18 = new GrammarExpression(SIMPLE_EXPRESSION);
    ex18->expression = {SIMPLE_EXPRESSION, addop_terminal, TERM};
    SIMPLE_EXPRESSION->leads_to.push_back(ex18);

    GrammarExpression* ex19 = new GrammarExpression(TERM);
    ex19->expression = {FACTOR};
    TERM->leads_to.push_back(ex19);

    GrammarExpression* ex20 = new GrammarExpression(TERM);
    ex20->expression = {TERM, mulop_terminal, FACTOR};
    TERM->leads_to.push_back(ex20);

    GrammarExpression* ex21 = new GrammarExpression(SIGN);
    ex21->expression = {plus_terminal};
    SIGN->leads_to.push_back(ex21);

    GrammarExpression* ex22 = new GrammarExpression(SIGN);
    ex22->expression = {minus_terminal};
    SIGN->leads_to.push_back(ex22);

    GrammarExpression* ex23 = new GrammarExpression(FACTOR);
    ex23->expression = {id_terminal};
    FACTOR->leads_to.push_back(ex23);

    GrammarExpression* ex24 = new GrammarExpression(FACTOR);
    ex24->expression = {num_terminal};
    FACTOR->leads_to.push_back(ex24);

    GrammarExpression* ex25 = new GrammarExpression(FACTOR);
    ex25->expression = {openBracket_terminal, EXPRESSION, closedBracket_terminal};
    FACTOR->leads_to.push_back(ex25);

    vector<GrammarElement *> expectedRules = {METHOD_BODY_E, STATEMENT_LIST_E, STATEMENT_E,
                                              DECLARATION_E, IF_E, WHILE_E, ASSIGNMENT_E,
                                              PRIMITIVE_TYPE_E, EXPRESSION_E, SIMPLE_EXPRESSION_E,
                                              TERM_E, SIGN_E, FACTOR_E, id_terminal, semicolon_terminal,
                                              int_terminal, float_terminal, if_terminal, openBracket_terminal,
                                              closedBracket_terminal, openCurlyBracket_terminal,
                                              closedCurlyBracket_terminal, else_terminal, while_terminal,
                                              relop_terminal, addop_terminal, mulop_terminal, equal_terminal,
                                              num_terminal, plus_terminal, minus_terminal};

    vector<string> errors = fileParser.parse_grammar_file(&rules, &expressions, &infile,
                                                          &terminals, &non_terminals, &startRule);

    if (!errors.size() == 0) {
        cout << "Syntactic Grammar Parser Errors: " + to_string(errors.size()) + " errors detected" << endl;
        for (int i = 0; i < errors.size(); ++i) {
            cout << errors[i] << endl;
        }
    }

    unordered_set<string> expectedNonTerminals = {"METHOD_BODY", "STATEMENT_LIST", "STATEMENT",
                                                  "DECLARATION", "IF", "WHILE", "ASSIGNMENT",
                                                  "PRIMITIVE_TYPE", "EXPRESSION", "SIMPLE_EXPRESSION",
                                                  "TERM", "SIGN", "FACTOR"};

    unordered_set<string> expectedTerminals = {"id", ";", "int", "float", "if", "(", ")",
                                               "{", "}", "else", "while", "relop", "addop",
                                               "mulop", "=", "num", "+", "-"};

    bool error = compareSets(&non_terminals, &expectedNonTerminals);
    error |= compareSets(&terminals, &expectedTerminals);
    error |= compareRules(&rules, &expectedRules);
    if (error) {
        cout << "Project pdf example parsing error" << endl;
    } else {
        cout << "Project pdf example parsing success" << endl;
    }
}

bool compareRules(vector<GrammarElement *> *rules, vector<GrammarElement *> *expectedRules) {
    bool error = false;
    if (rules->size() != expectedRules->size()) {
        cout << "Syntactic Grammar Parser Errors: Rules found " + to_string(rules->size())
                + " instead of " << expectedRules->size() << endl;
        for (int i = 0; i < rules->size(); ++i) {
            cout << (*rules)[i]->getName() << endl;
        }
        error = true;
    }

    if (rules->size() == expectedRules->size()) {
        for (int i = 0; i < expectedRules->size(); i++) {
            if ((*rules)[i]->getType() == NON_TERMINAL && (*expectedRules)[i]->getType() == NON_TERMINAL) {
                NonTerminal* rule = static_cast<NonTerminal *>((*rules)[i]);
                NonTerminal* expectedRule = static_cast<NonTerminal *>((*expectedRules)[i]);
                if (rule->getName() != expectedRule->getName()) {
                    cout << "Grammar Rule with name " << rule->getName() << " instead of " << expectedRule->getName() << endl;
                    error = true;
                } else if (rule->getType() != expectedRule->getType()) {
                    cout << "Grammar Rule with name " << rule->getName() << " has type "
                         << to_string(rule->getType())
                         << " rules instead of " << to_string(expectedRule->getType()) << endl;
                    error = true;
                } else if (rule->eps != expectedRule->eps) {
                    cout << "Grammar Rule with name " << rule->getName() << " has eps "
                         << to_string(rule->eps)
                         << " rules instead of " << to_string(expectedRule->eps) << endl;
                    error = true;
                } else if (rule->leads_to.size() != expectedRule->leads_to.size()) {
                    cout << "Grammar Rule with name " << rule->getName() << " has "
                         << to_string(rule->leads_to.size())
                         << " rules instead of " << to_string(expectedRule->leads_to.size()) << endl;
                    error = true;
                } else {
                    for (int j = 0; j < rule->leads_to.size(); ++j) {
                        GrammarExpression *expression = rule->leads_to[j];
                        GrammarExpression *expectedExpression = expectedRule->leads_to[j];
                        if (expression->expression.size() != expectedExpression->expression.size()) {
                            cout << "Grammar Rule with name " << rule->getName() << "Expression"
                                 << j + 1 << " has size " << to_string(expression->expression.size())
                                 << " instead of " << to_string(expectedExpression->expression.size()) << endl;
                            error = true;
                        } else {
                            for (int k = 0; k < expression->expression.size(); ++k) {
                                GrammarElement *element = expression->expression[k];
                                GrammarElement *expectedElement = expectedExpression->expression[k];
                                if (element->getName() != expectedElement->getName()) {
                                    cout << "Grammar Element Number " << k + 1 << " in expression "
                                         <<  j + 1 << " in rule" << i + 1 << " has name " << element->getName()
                                         << " instead of " << expectedElement->getName() << endl;
                                    error = true;
                                } else if (element->getType() != expectedElement->getType()) {
                                    cout << "Grammar Element Number " << k + 1 << " in expression "
                                         <<  j + 1 << " in rule" << i + 1 << " has type " << element->getType()
                                         << " instead of " << expectedElement->getType() << endl;
                                    error = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return error;
}

bool compareSets(unordered_set<string> *real, unordered_set<string> *expected) {
    bool error = false;
    if (real->size() != expected->size()) {
        cout << "Sets have " << real->size() << " elements instead of " << expected->size() << endl;
        error = true;
        for (auto itr = expected->begin(); itr != expected->end(); ++itr) {
            if (real->find(*itr) == real->end()) {
                cout << "element " << *itr << " not found in set" << endl;
                error = true;
            }
        }
    }
    return error;
}
