/*
 * GrammarTableBuilderTest.cpp
 *
 *  Created on: Apr 18, 2018
 *      Author: Marc Magdi
 */

#include "../../../test_headers/p2_tests.h"
#include "GrammarTableBuilder.h"
#include "../models/NonTerminal.h"
#include "../calculator_test_utils/TestGraph.h"

bool compareGrammarTable(GrammarTable* t1, GrammarTable* t2);
bool test_sheet_four_problem_two();
bool test_lecture_example_2_invalid();
bool compareErrorVector(vector<string>* e1, vector<string>* e2);
bool test_lecture_example_3();

void test_grammar_table_builder() {
    bool valid = true;
    valid &= test_sheet_four_problem_two();
    valid &= test_lecture_example_2_invalid();
    valid &= test_lecture_example_3();

    if (valid) {
        cout << "Grammar Table Builder test pass..." << endl;
    }
}

void test_pdf_problem() {
    // setup mock object
    GrammarElement *METHOD_BODY_E = new NonTerminal("METHOD_BODY", NON_TERMINAL);
    GrammarElement *STATEMENT_LIST_E = new NonTerminal("STATEMENT_LIST", NON_TERMINAL);
    GrammarElement *STATEMENT_E = new NonTerminal("STATEMENT", NON_TERMINAL);
    GrammarElement *DECLARATION_E = new NonTerminal("DECLARATION", NON_TERMINAL);
    GrammarElement *PRIMITIVE_TYPE_E = new NonTerminal("PRIMITIVE_TYPE", NON_TERMINAL);
    GrammarElement *IF_E = new NonTerminal("IF", NON_TERMINAL);
    GrammarElement *WHILE_E = new NonTerminal("WHILE", NON_TERMINAL);
    GrammarElement *ASSIGNMENT_E = new NonTerminal("ASSIGNMENT", NON_TERMINAL);
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
    NonTerminal *FACTOR = static_cast<NonTerminal *>(FACTOR_E);
    NonTerminal *SIGN = static_cast<NonTerminal *>(SIGN_E);

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
    ex1->first_strings.insert(STATEMENT_LIST->first_strings.begin(), STATEMENT_LIST->first_strings.end());
    METHOD_BODY->leads_to.push_back(ex1);

    GrammarExpression* ex2 = new GrammarExpression(STATEMENT_LIST);
    ex2->expression = {STATEMENT};
    ex2->first_strings.insert(STATEMENT->first_strings.begin(), STATEMENT->first_strings.end());
    STATEMENT_LIST->leads_to.push_back(ex2);

    GrammarExpression* ex3 = new GrammarExpression(STATEMENT_LIST);
    ex3->expression = {STATEMENT_LIST, STATEMENT};
    ex3->first_strings.insert(STATEMENT_LIST->first_strings.begin(), STATEMENT_LIST->first_strings.end());
    STATEMENT_LIST->leads_to.push_back(ex3);

    GrammarExpression* ex4 = new GrammarExpression(STATEMENT);
    ex4->expression = {DECLARATION};
    ex4->first_strings.insert(DECLARATION->first_strings.begin(), DECLARATION->first_strings.end());
    STATEMENT->leads_to.push_back(ex4);

    GrammarExpression* ex5 = new GrammarExpression(STATEMENT);
    ex5->expression = {IF};
    ex5->first_strings.insert(IF->first_strings.begin(), IF->first_strings.end());
    STATEMENT->leads_to.push_back(ex5);

    GrammarExpression* ex6 = new GrammarExpression(STATEMENT);
    ex6->expression = {WHILE};
    ex6->first_strings.insert(WHILE->first_strings.begin(), WHILE->first_strings.end());
    STATEMENT->leads_to.push_back(ex6);

    GrammarExpression* ex7 = new GrammarExpression(STATEMENT);
    ex7->expression = {ASSIGNMENT};
    ex7->first_strings.insert(ASSIGNMENT->first_strings.begin(), ASSIGNMENT->first_strings.end());
    STATEMENT->leads_to.push_back(ex7);

    GrammarExpression* ex8 = new GrammarExpression(DECLARATION);
    ex8->expression = {PRIMITIVE_TYPE, id_terminal, semicolon_terminal};
    ex8->first_strings.insert(PRIMITIVE_TYPE->first_strings.begin(), PRIMITIVE_TYPE->first_strings.end());
    DECLARATION->leads_to.push_back(ex8);

    GrammarExpression* ex9 = new GrammarExpression(IF);
    ex9->expression = {if_terminal, openBracket_terminal, EXPRESSION, closedBracket_terminal,
                       openCurlyBracket_terminal, STATEMENT, closedCurlyBracket_terminal,
                       else_terminal, openCurlyBracket_terminal, STATEMENT,
                       closedCurlyBracket_terminal};
    ex9->first_strings.insert(if_terminal->getName());
    IF->leads_to.push_back(ex9);

    GrammarExpression* ex10 = new GrammarExpression(WHILE);
    ex10->expression = {while_terminal, openBracket_terminal, EXPRESSION, closedBracket_terminal,
                        openCurlyBracket_terminal, STATEMENT, closedCurlyBracket_terminal};

    ex10->first_strings.insert(while_terminal->getName());
    WHILE->leads_to.push_back(ex10);

    GrammarExpression* ex11 = new GrammarExpression(ASSIGNMENT);
    ex11->expression = {id_terminal, equal_terminal, EXPRESSION, semicolon_terminal};
    ex11->first_strings.insert(id_terminal->getName());
    ASSIGNMENT->leads_to.push_back(ex11);

    GrammarExpression* ex12 = new GrammarExpression(PRIMITIVE_TYPE);
    ex12->expression = {int_terminal};
    ex12->first_strings.insert(int_terminal->getName());
    PRIMITIVE_TYPE->leads_to.push_back(ex12);

    GrammarExpression* ex13 = new GrammarExpression(PRIMITIVE_TYPE);
    ex13->expression = {float_terminal};
    ex13->first_strings.insert(float_terminal->getName());
    PRIMITIVE_TYPE->leads_to.push_back(ex13);

    GrammarExpression* ex14 = new GrammarExpression(EXPRESSION);
    ex14->expression = {SIMPLE_EXPRESSION};
    ex14->first_strings.insert(SIMPLE_EXPRESSION->first_strings.begin(), SIMPLE_EXPRESSION->first_strings.end());
    EXPRESSION->leads_to.push_back(ex14);

    GrammarExpression* ex15 = new GrammarExpression(EXPRESSION);
    ex15->expression = {SIMPLE_EXPRESSION, relop_terminal, SIMPLE_EXPRESSION};
    ex15->first_strings.insert(SIMPLE_EXPRESSION->first_strings.begin(), SIMPLE_EXPRESSION->first_strings.end());
    EXPRESSION->leads_to.push_back(ex15);

    GrammarExpression* ex16 = new GrammarExpression(SIMPLE_EXPRESSION);
    ex16->expression = {TERM};
    ex16->first_strings.insert(TERM->first_strings.begin(), TERM->first_strings.end());
    SIMPLE_EXPRESSION->leads_to.push_back(ex16);

    GrammarExpression* ex17 = new GrammarExpression(SIMPLE_EXPRESSION);
    ex17->expression = {SIGN, TERM};
    ex17->first_strings.insert(SIGN->first_strings.begin(), SIGN->first_strings.end());
    SIMPLE_EXPRESSION->leads_to.push_back(ex17);

    GrammarExpression* ex18 = new GrammarExpression(SIMPLE_EXPRESSION);
    ex18->expression = {SIMPLE_EXPRESSION, addop_terminal, TERM};
    ex18->first_strings.insert(SIMPLE_EXPRESSION->first_strings.begin(), SIMPLE_EXPRESSION->first_strings.end());
    SIMPLE_EXPRESSION->leads_to.push_back(ex18);

    GrammarExpression* ex19 = new GrammarExpression(TERM);
    ex19->expression = {FACTOR};
    ex19->first_strings.insert(FACTOR->first_strings.begin(), FACTOR->first_strings.end());
    TERM->leads_to.push_back(ex19);

    GrammarExpression* ex20 = new GrammarExpression(TERM);
    ex20->expression = {TERM, mulop_terminal, FACTOR};
    ex20->first_strings.insert(TERM->first_strings.begin(), TERM->first_strings.end());
    TERM->leads_to.push_back(ex20);

    GrammarExpression* ex21 = new GrammarExpression(SIGN);
    ex21->expression = {plus_terminal};
    ex21->first_strings.insert(plus_terminal->getName());
    SIGN->leads_to.push_back(ex21);

    GrammarExpression* ex22 = new GrammarExpression(SIGN);
    ex22->expression = {minus_terminal};
    ex22->first_strings.insert(minus_terminal->getName());
    SIGN->leads_to.push_back(ex22);

    GrammarExpression* ex23 = new GrammarExpression(FACTOR);
    ex23->expression = {id_terminal};
    ex23->first_strings.insert(id_terminal->getName());
    FACTOR->leads_to.push_back(ex23);

    GrammarExpression* ex24 = new GrammarExpression(FACTOR);
    ex24->expression = {num_terminal};
    ex24->first_strings.insert(num_terminal->getName());
    FACTOR->leads_to.push_back(ex24);

    GrammarExpression* ex25 = new GrammarExpression(FACTOR);
    ex25->expression = {openBracket_terminal, EXPRESSION, closedBracket_terminal};
    ex25->first_strings.insert(openBracket_terminal->getName());
    FACTOR->leads_to.push_back(ex25);

    // set first
    SIGN->first_strings.insert({"+", "-"});
    FACTOR->first_strings.insert({"id", "num", "("});
    TERM->first_strings.insert({"id", "num", "("});
    SIMPLE_EXPRESSION->first_strings.insert({"id", "num", "(", "+", "-"});
    EXPRESSION->first_strings.insert({"id", "num", "(", "+", "-"});
    ASSIGNMENT->first_strings.insert({"id"});
    WHILE->first_strings.insert({"while"});
    IF->first_strings.insert({"if"});
    PRIMITIVE_TYPE->first_strings.insert({"int", "float"});
    DECLARATION->first_strings.insert({"int", "float"});
    STATEMENT->first_strings.insert({"int", "float", "if", "while", "id"});
    STATEMENT_LIST->first_strings.insert({"int", "float", "if", "while", "id"});
    METHOD_BODY->first_strings.insert({"int", "float", "if", "while", "id"});

    // set follow
    METHOD_BODY->follow_strings.insert({"$"});
    STATEMENT_LIST->follow_strings.insert({"$", "int", "float", "if", "while", "id"});
    STATEMENT->follow_strings.insert({"$", "int", "float", "if", "while", "id", "}"});
    DECLARATION->follow_strings.insert({"$", "int", "float", "if", "while", "id", "}"});
    PRIMITIVE_TYPE->follow_strings.insert({"id"});
    IF->follow_strings.insert({"$", "int", "float", "if", "while", "id", "}"});
    WHILE->follow_strings.insert({"$", "int", "float", "if", "while", "id", "}"});
    ASSIGNMENT->follow_strings.insert({"$", "int", "float", "if", "while", "id", "}"});
    EXPRESSION->follow_strings.insert({";", ")"});
    SIMPLE_EXPRESSION->follow_strings.insert({";", ")", "addop", "relop"});
    TERM->follow_strings.insert({";", ")", "addop", "relop", "mulop"});
    FACTOR->follow_strings.insert({";", ")", "addop", "relop", "mulop"});
    SIGN->follow_strings.insert({"id", "num", "("});

    vector<GrammarElement *> rules = {METHOD_BODY_E, STATEMENT_LIST_E, STATEMENT_E,
                                      DECLARATION_E, IF_E, WHILE_E, ASSIGNMENT_E,
                                      PRIMITIVE_TYPE_E, EXPRESSION_E, SIMPLE_EXPRESSION_E,
                                      TERM_E, SIGN_E, FACTOR_E};

    GrammarTable grammarTable;
    grammarTable.set_start("METHOD_BODY");

    grammarTable.add_entry("METHOD_BODY", "int", {"STATEMENT_LIST"});
    grammarTable.add_entry("METHOD_BODY", "float", {"STATEMENT_LIST"});
    grammarTable.add_entry("METHOD_BODY", "if", {"STATEMENT_LIST"});
    grammarTable.add_entry("METHOD_BODY", "while", {"STATEMENT_LIST"});
    grammarTable.add_entry("METHOD_BODY", "id", {"STATEMENT_LIST"});
    grammarTable.add_synch("METHOD_BODY", "$");

    grammarTable.add_entry("STATEMENT_LIST", "int", {"STATEMENT_LIST"});
    grammarTable.add_entry("STATEMENT_LIST", "float", {"STATEMENT_LIST"});
    grammarTable.add_entry("STATEMENT_LIST", "if", {"STATEMENT_LIST"});
    grammarTable.add_entry("STATEMENT_LIST", "while", {"STATEMENT_LIST"});
    grammarTable.add_entry("STATEMENT_LIST", "id", {"STATEMENT_LIST"});
    grammarTable.add_synch("STATEMENT_LIST", "$");

    GrammarTableBuilder grammarTableBuilder;
    vector<string> errors;
    auto result = grammarTableBuilder.build_grammar_table(&rules, &errors);
    compareGrammarTable(&grammarTable, result);}

bool test_sheet_four_problem_two() {
    vector<GrammarElement*> elements;
    unordered_set<GrammarExpression*> expressions;
    build_sheet_four_pro_two(&elements, &expressions, true, true);
    GrammarTableBuilder grammarTableBuilder;
    vector<string> errors;
    auto result = grammarTableBuilder.build_grammar_table(&elements, &errors);

    // build valid table
    GrammarTable grammarTable;

    grammarTable.set_start("E");

    grammarTable.add_entry("E", "(", {"T", "E'"});
    grammarTable.add_synch("E", ")");
    grammarTable.add_synch("E", "$");
    grammarTable.add_entry("E", "a", {"T", "E'"});
    grammarTable.add_entry("E", "b", {"T", "E'"});
    grammarTable.add_entry("E", "Em", {"T", "E'"});

    grammarTable.add_entry("E'", ")", {});
    grammarTable.add_entry("E'", "$", {});
    grammarTable.add_entry("E'", "+", {"+", "E"});

    grammarTable.add_entry("T", "(", {"F", "T'"});
    grammarTable.add_synch("T", ")");
    grammarTable.add_synch("T", "+");
    grammarTable.add_synch("T", "$");
    grammarTable.add_entry("T", "a", {"F", "T'"});
    grammarTable.add_entry("T", "b", {"F", "T'"});
    grammarTable.add_entry("T", "Em", {"F", "T'"});

    grammarTable.add_entry("T'", "(", {"T"});
    grammarTable.add_entry("T'", ")", {});
    grammarTable.add_entry("T'", "a", {"T"});
    grammarTable.add_entry("T'", "b", {"T"});
    grammarTable.add_entry("T'", "Em", {"T"});
    grammarTable.add_entry("T'", "+", {});
    grammarTable.add_entry("T'", "$", {});

    grammarTable.add_entry("F", "(", {"P", "F'"});
    grammarTable.add_synch("F", ")");
    grammarTable.add_synch("F", "+");
    grammarTable.add_synch("F", "$");
    grammarTable.add_entry("F", "a", {"P", "F'"});
    grammarTable.add_entry("F", "b", {"P", "F'"});
    grammarTable.add_entry("F", "Em", {"P", "F'"});

    grammarTable.add_entry("F'", "(", {});
    grammarTable.add_entry("F'", ")", {});
    grammarTable.add_entry("F'", "a", {});
    grammarTable.add_entry("F'", "b", {});
    grammarTable.add_entry("F'", "+", {});
    grammarTable.add_entry("F'", "Em", {});
    grammarTable.add_entry("F'", "$", {});
    grammarTable.add_entry("F'", "*", {"*", "F"});

    grammarTable.add_entry("P", "(", {"(", "E", ")"});
    grammarTable.add_synch("P", ")");
    grammarTable.add_synch("P", "+");
    grammarTable.add_synch("P", "*");
    grammarTable.add_synch("P", "$");
    grammarTable.add_entry("P", "a", {"a"});
    grammarTable.add_entry("P", "b", {"b"});
    grammarTable.add_entry("P", "Em", {"Em"});

    bool valid = compareGrammarTable(result, &grammarTable);

    return valid;
}

bool test_lecture_example_2_invalid() {
    vector<GrammarElement*> elements;
    unordered_set<GrammarExpression*> expressions;
    build_lecture_example_2(&elements, &expressions, true, true);
    GrammarTableBuilder grammarTableBuilder;
    vector<string> errors;
    auto result = grammarTableBuilder.build_grammar_table(&elements, &errors);

    GrammarTable grammarTable;
    grammarTable.set_start("S");

    grammarTable.add_entry("S", "a", {"a"});
    grammarTable.add_entry("S", "i", {"i", "C", "t", "S", "E"});
    grammarTable.add_entry("E", "e", {"e", "S"});
    grammarTable.add_entry("E", "$", {});
    grammarTable.add_entry("C", "b", {"b"});

    grammarTable.add_synch("S", "e");
    grammarTable.add_synch("S", "$");
    grammarTable.add_synch("C", "t");

    vector<string> expectedErrors = {"Ambiguous grammar. Key(E e). has multiple values."};

    bool valid = compareGrammarTable(result, &grammarTable);
    valid &= compareErrorVector(&expectedErrors, &errors);

    return valid;
}

bool test_lecture_example_3() {
    vector<GrammarElement*> elements;
    unordered_set<GrammarExpression*> expressions;
    build_lecture_example_3(&elements, &expressions, true, true);
    GrammarTableBuilder grammarTableBuilder;
    vector<string> errors;
    auto result = grammarTableBuilder.build_grammar_table(&elements, &errors);

    GrammarTable grammarTable;
    grammarTable.set_start("S");

    grammarTable.add_entry("S", "a", {"A", "b", "S"});
    grammarTable.add_entry("S", "c", {"A", "b", "S"});
    grammarTable.add_entry("S", "e", {"e"});
    grammarTable.add_entry("S", "$", {});
    grammarTable.add_entry("A", "a", {"a"});
    grammarTable.add_entry("A", "c", {"c", "A", "d"});
    grammarTable.add_synch("A", "b");
    grammarTable.add_synch("A", "d");


    vector<string> expectedErrors = {};

    bool valid = compareGrammarTable(result, &grammarTable);
    valid &= compareErrorVector(&expectedErrors, &errors);

    return valid;
}

bool compareGrammarTable(GrammarTable* t1, GrammarTable* t2) {
    bool valid = true;
    // check start
    if (t1->get_start() != t2->get_start()) {
        valid = false;
        cout << "Error comparing grammar table builder first. Expected: (" << t2->get_start()
             <<"). Actual: ("<< t1->get_start()<<")." << endl;
    }

    // check table
    if (t1->get_table_elements_count() != t2->get_table_elements_count()) {
        valid = false;
        cout << "Error in constructing table, table size not matched. Expected: (" << t2->get_table_elements_count()
             <<"). Actual: ("<< t1->get_table_elements_count()<<")." << endl;
    }

    if (!t1->compare_table(t2)) {
        valid = false;
        cout << "Error in comparing table" << endl;
    }

    // check synch
    if (t1->get_sync_elements_count() != t2->get_sync_elements_count()) {
        valid = false;
        cout << "Error in constructing sync, sync size not matched.Expected: (" << t2->get_sync_elements_count()
             <<"). Actual: ("<< t1->get_sync_elements_count()<<")." << endl;
    }

    if (!t1->compare_sync(t2)) {
        valid = false;
        cout << "Error in comparing sync table" << endl;
    }

    return valid;
}

/**.
 * @param e1 expected error vector
 * @param e2 actual error vector
 */
bool compareErrorVector(vector<string>* e1, vector<string>* e2) {
    bool valid = true;
    if (e1->size() != e2->size()) {
        cout << "Error vector count not matched.Expected(" << e1->size() << "), Actual("
                            << e2->size() << ").\n";
        cout << "Error vector values\n";
        for (int i = 0; i < e2->size() && valid; i++) {
            string s2 = (*e2)[i];
            cout << "Element[" << i << "] = " << s2 << ".\n";
        }

        valid = false;
    }

    for (int i = 0; i < e1->size() && valid; i++) {
        string s1 = (*e1)[i];
        string s2 = (*e2)[i];
        if (s1 != s2) {
            cout << "Expected error not matched. Expected(" << s1 << "), Actual(" << s2 <<").\n" ;
            valid = false;
        }
    }

    return valid;
}
