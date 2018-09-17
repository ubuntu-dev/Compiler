/*
 * GrammarTableTest.cpp
 *
 *  Created on: Apr 18, 2018
 *      Author: amrnasr
 */

#include <iostream>
#include "../../test_headers/p2_tests.h"
#include "model/GrammarTable.h"

void test_grammar_table(void) {
    auto grammarTable = new GrammarTable;
    vector<string> s;
    bool valid = true;
    s.emplace_back("Hello World");
    vector<string> terminals = {"a", "b"};
    vector<string> nonTerminals = {"A"};

    grammarTable->set_terminals(terminals);
    grammarTable->set_non_terminals(nonTerminals);

    grammarTable->add_entry("A", "a", s);
    if (!grammarTable->has_entry("A", "a")) {
        cout << "Error at checking for existing value." << endl;
        valid = false;
    }

    vector<string> ret = grammarTable->get_entry("A", "a");
    if (ret.size() != s.size() || ret[0] != s[0]) {
        cout << "Error at retrieving value." << endl;
        valid = false;
    }

    if (!grammarTable->get_entry("invalid", "wrong").empty()) {
        cout << "Error at retrieving invalid value." << endl;
        valid = false;
    }

    grammarTable->add_synch("A", "b");
    if (!grammarTable->is_synch("A", "b")) {
        cout << "Error at checking for synch value." << endl;
        valid = false;
    }

    if (grammarTable->is_terminal("A")) {
        cout << "Error checking invalid terminal value." << endl;
        valid = false;
    }

    if (!grammarTable->is_non_terminal("A")) {
        cout << "Error checking valid non non terminal value." << endl;
        valid = false;
    }

    if (!grammarTable->is_terminal("a")) {
        cout << "Error checking invalid terminal value." << endl;
        valid = false;
    }

    if (grammarTable->is_non_terminal("a")) {
        cout << "Error checking invalid non terminal value." << endl;
        valid = false;
    }


    grammarTable->set_start("A");
    if (grammarTable->get_start() != "A") {
        cout << "Error checking start terminal." << endl;
        valid = false;
    }

    if (valid) {
        cout << "Grammar Table test pass.." << endl;
    }
}


void test_grammar_table_writer(void) {

}

void test_grammar_table_reader(void) {

}
