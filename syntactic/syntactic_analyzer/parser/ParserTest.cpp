/*
 * ParserTest.cpp
 *
 *  Created on: Apr 18, 2018
 *      Author: amrnasr
 */

#include <iostream>
#include "../../../test_headers/p2_tests.h"
#include "../../grammar_table/model/GrammarTable.h"
#include "Parser.h"
#include "../../syntactic_analyzer_generator/models/GrammarElement.h"

bool compareVectors(vector<string>* v1, vector<string>* v2);
bool test_1();
bool test_2();
bool test_3();
bool test_4();

void test_parser() {
    bool valid = true;
    valid &= test_1();
    valid &= test_2();
    valid &= test_3();
    valid &= test_4();

    if (valid) {
        cout << "Parser tests passed ..\n";
    }
}


/**.
 *      a        b         $
 * S    S->aBa
 * B    B->eps  B->bB
 */
bool test_1() {
    // setup Grammar Table
    GrammarTable grammarTable;
    grammarTable.add_entry("S", "a", {"a", "B", "a"});
    grammarTable.add_entry("B", "a", {});
    grammarTable.add_entry("B", "b", {"b", "B"});
    grammarTable.set_start("S");
    vector<string> terminals = {"a", "b"};
    vector<string> nonTerminals = {"S", "B"};
    grammarTable.set_non_terminals(nonTerminals);
    grammarTable.set_terminals(terminals);

    Parser parser;
    parser.set_grammar_table(grammarTable);
    parser.init_parser();
    Token* token1 = new Token(REAL_TOKEN, "", "a");
    Token* token2 = new Token(REAL_TOKEN, "", "b");
    Token* token3 = new Token(REAL_TOKEN, "", "b");
    Token* token4 = new Token(REAL_TOKEN, "", "a");
//    Token* token5 = new Token(REAL_TOKEN, "", "$");
    parser.derive_token(*token1);
    parser.derive_token(*token2);
    parser.derive_token(*token3);
    parser.derive_token(*token4);
//    parser.derive_token(*token5);

    vector<vector<string>> derivations;
    vector<string> errors;
    parser.finish_derivation(&errors, &derivations);
    vector<vector<string>> expectedDerivations = {{"S"},
                                          {"a", "B", "a"},
                                          {"a", "b", "B", "a"},
                                          {"a" ,"b", "b", "B", "a"},
                                          {"a", "b", "b", "a"}};

    bool valid = true;
    vector<string> expectedErrors = {};

    if (derivations.size() != expectedDerivations.size()) {
        cout << "Parser Error:\n";
        cout << "Derivation vector count not matched.Expected(" << expectedDerivations.size() << "), Actual("
             << derivations.size() << ").\n";
        valid = false;
    }

    for (int i = 0; i < derivations.size() && valid; i++) {
        valid &= compareVectors(&expectedDerivations[i], &derivations[i]);
    }

    if (errors.size() != expectedErrors.size()) {
        cout << "Error vector(Parser) count not matched.Expected(" << expectedErrors.size() << "), Actual("
             << errors.size() << ").\n";
        valid = false;
    }

    compareVectors(&expectedErrors, &errors);

    return valid;
}

bool test_2() {
    // setup Grammar Table
    GrammarTable grammarTable;
    grammarTable.add_entry("S", "a", {"A", "b", "S"});
    grammarTable.add_entry("S", "c", {"A", "b", "S"});
    grammarTable.add_entry("S", "e", {"e"});
    grammarTable.add_entry("S", "$", {});
    grammarTable.add_entry("A", "a", {"a"});
    grammarTable.add_entry("A", "c", {"c", "A", "d"});

    grammarTable.add_synch("A", "b");
    grammarTable.add_synch("A", "d");

    grammarTable.set_start("S");

    vector<string> terminals = {"a", "b", "c", "d", "e", "$"};
    vector<string> nonTerminals = {"S", "A"};
    grammarTable.set_non_terminals(nonTerminals);
    grammarTable.set_terminals(terminals);


    Parser parser;
    parser.set_grammar_table(grammarTable);
    parser.init_parser();
    Token* token1 = new Token(REAL_TOKEN, "", "a");
    Token* token2 = new Token(REAL_TOKEN, "", "a");
    Token* token3 = new Token(REAL_TOKEN, "", "b");
//    Token* token4 = new Token(REAL_TOKEN, "", "$");
    parser.derive_token(*token1);
    parser.derive_token(*token2);
    parser.derive_token(*token3);
//    parser.derive_token(*token4);

    vector<vector<string>> derivations;
    vector<string> errors;
    parser.finish_derivation(&errors, &derivations);
    vector<vector<string>> expectedDerivations = {{"S"},
                                                  {"A", "b", "S"},
                                                  {"a", "b", "S"},
                                                  {"a" ,"b", "A", "b", "S"},
                                                  {"a" ,"b", "a", "b", "S"},
                                                  {"a" ,"b", "a", "b"}};

    vector<string> expectedErrors = {"Error: missing b, inserted"};

    bool valid = true;
    if (derivations.size() != expectedDerivations.size()) {
        cout << "Derivation vector count not matched.Expected(" << expectedDerivations.size() << "), Actual("
             << derivations.size() << ").\n";
        valid = false;
    }

    for (int i = 0; i < derivations.size() && valid; i++) {
        valid &= compareVectors(&expectedDerivations[i], &derivations[i]);
    }

    if (errors.size() != expectedErrors.size()) {
        cout << "Error vector(Parser) count not matched.Expected(" << expectedErrors.size() << "), Actual("
             << errors.size() << ").\n";
        valid = false;
    }

    compareVectors(&expectedErrors, &errors);

    return valid;
}

/**.
 *      a       b       c       d       e       $
 * S   s->AbS         S->AbS           S->e    S->eps
 * A   A->a    synch  A->cAd   synch
 * @return
 */
bool test_3() {
    // setup Grammar Table
    GrammarTable grammarTable;
    grammarTable.add_entry("S", "a", {"A", "b", "S"});
    grammarTable.add_entry("S", "c", {"A", "b", "S"});
    grammarTable.add_entry("S", "e", {"e"});
    grammarTable.add_entry("S", "$", {});
    grammarTable.add_entry("A", "a", {"a"});
    grammarTable.add_entry("A", "c", {"c", "A", "d"});

    grammarTable.add_synch("A", "b");
    grammarTable.add_synch("A", "d");

    grammarTable.set_start("S");

    vector<string> terminals = {"a", "b", "c", "d", "e", "$"};
    vector<string> nonTerminals = {"S", "A"};
    grammarTable.set_non_terminals(nonTerminals);
    grammarTable.set_terminals(terminals);


    Parser parser;
    parser.set_grammar_table(grammarTable);
    parser.init_parser();
    Token* token1 = new Token(REAL_TOKEN, "", "c");
    Token* token2 = new Token(REAL_TOKEN, "", "e");
    Token* token3 = new Token(REAL_TOKEN, "", "a");
    Token* token4 = new Token(REAL_TOKEN, "", "d");
    Token* token5 = new Token(REAL_TOKEN, "", "b");
//    Token* token6 = new Token(REAL_TOKEN, "", "$");
    parser.derive_token(*token1);
    parser.derive_token(*token2);
    parser.derive_token(*token3);
    parser.derive_token(*token4);
    parser.derive_token(*token5);
//    parser.derive_token(*token6);

    vector<vector<string>> derivations;
    vector<string> errors;
    parser.finish_derivation(&errors, &derivations);
    vector<vector<string>> expectedDerivations = {{"S"},
                                                  {"A", "b", "S"},
                                                  {"c", "A", "d", "b", "S"},
                                                  {"c" ,"a", "d", "b", "S"},
                                                  {"c" ,"a", "d", "b"}};

    vector<string> expectedErrors = {"Error:(illegal A) – discard e"};

    bool valid = true;
    if (derivations.size() != expectedDerivations.size()) {
        cout << "Derivation vector count not matched.Expected(" << expectedDerivations.size() << "), Actual("
             << derivations.size() << ").\n";
        valid = false;
    }

    for (int i = 0; i < derivations.size() && valid; i++) {
        valid &= compareVectors(&expectedDerivations[i], &derivations[i]);
    }

    if (errors.size() != expectedErrors.size()) {
        cout << "Error vector(Parser) count not matched.Expected(" << expectedErrors.size() << "), Actual("
             << errors.size() << ").\n";
        valid = false;
    }

    compareVectors(&expectedErrors, &errors);

    return valid;

}

bool test_4() {
    // setup Grammar Table
    GrammarTable grammarTable;

    vector<string> terminals = {"a", "$"};
    vector<string> nonTerminals = {"A", "B"};
    grammarTable.set_non_terminals(nonTerminals);
    grammarTable.set_terminals(terminals);

    grammarTable.add_entry("A", "a", {"B"});
    grammarTable.add_entry("B", "$", {});

    grammarTable.set_start("A");

    Parser parser;
    parser.set_grammar_table(grammarTable);
    parser.init_parser();

    Token* token1 = new Token(REAL_TOKEN, "", "a");
//    Token* token2 = new Token(REAL_TOKEN, "", "$");
    parser.derive_token(*token1);
//    parser.derive_token(*token2);

    vector<vector<string>> derivations;
    vector<string> errors;
    parser.finish_derivation(&errors, &derivations);

}

/**.
 * @param v1 expected vector
 * @param v2 actual vector
 */
bool compareVectors(vector<string>* v1, vector<string>* v2) {
    bool valid = true;
    if (v1->size() != v2->size()) {
        cout << "Parser Error:\n";
        cout << "Derivation vector count not matched.Expected(" << v1->size() << "), Actual("
             << v2->size() << ").\n";
        cout << "Vector values\n";
        for (int i = 0; i < v2->size(); i++) {
            string s2 = (*v2)[i];
            cout << "Element[" << i << "] = " << s2 << "\n";
        }

        valid = false;
    }

    for (int i = 0; i < v1->size() && valid; i++) {
        string s1 = (*v1)[i];
        string s2 = (*v2)[i];
        if (s1 != s2) {
            cout << "Expected derivation not matched. Expected(" << s1 << "), Actual(" << s2 <<").\n" ;
            valid = false;
        }
    }

    return valid;
}
