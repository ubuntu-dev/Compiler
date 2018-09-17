//
// Created by programajor on 4/26/18.
//

#include "../../../test_headers/p2_tests.h"
#include <iostream>
#include "../model/GrammarTable.h"
#include "../../syntactic_analyzer_generator/models/GrammarElement.h"
#include "../../syntactic_analyzer_generator/models/NonTerminal.h"
#include "../../syntactic_analyzer_generator/calculator_test_utils/TestGraph.h"
#include "../../syntactic_analyzer_generator/table_builder/GrammarTableBuilder.h"
#include "../writer/GrammarTableWriter.h"
#include "GrammarTableReader.h"

bool compareGrammarTable(GrammarTable* t1, GrammarTable* t2);
bool test_sheet_four_problem_two_writer_reader();
bool compareErrorVector(vector<string>* e1, vector<string>* e2);
bool test_lecture_example_3_writer_reader();

void test_grammar_table_writer_reader() {
    bool valid = true;
    valid &= test_sheet_four_problem_two_writer_reader();
    valid &= test_lecture_example_3_writer_reader();

    if (valid) {
        cout << "Grammar Table Writer Reader test pass..." << endl;
    }
}

bool test_sheet_four_problem_two_writer_reader() {
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

    GrammarTableWriter writer;

    std::streambuf * buf;
    std::ofstream of;
    of.open("grammarTableWriterTest1.txt");
    buf = of.rdbuf();
    std::ostream out(buf);

    writer.writeGrammarTableInReadableForamt(&grammarTable, &out);

    GrammarTableReader reader;

    std::ifstream of2;
    of2.open("grammarTableWriterTest1.txt");

    GrammarTable* grammarTable1 = reader.readGrammarTable(&of2);
    bool valid = compareGrammarTable(grammarTable1, &grammarTable);

    if(remove("grammarTableWriterTest1.txt") != 0) {
        cout << "File not generated : Grammar Table Writer failed" << endl;
    } else {
        cout << "Grammar Table Reader Writer Test 1 file removal success..." << endl;
    }

    return valid;
}

bool test_lecture_example_3_writer_reader() {
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

    GrammarTableWriter writer;

    std::streambuf * buf;
    std::ofstream of;
    of.open("grammarTableWriterTest2.txt");
    buf = of.rdbuf();
    std::ostream out(buf);

    writer.writeGrammarTableInReadableForamt(&grammarTable, &out);

    GrammarTableReader reader;

    std::ifstream of2;
    of2.open("grammarTableWriterTest2.txt");

    GrammarTable* grammarTable1 = reader.readGrammarTable(&of2);
    bool valid = compareGrammarTable(grammarTable1, &grammarTable);

    if(remove("grammarTableWriterTest2.txt") != 0) {
        cout << "File not generated : Grammar Table Writer failed" << endl;
    } else {
        cout << "Grammar Table Reader Writer Test 2 file removal success..." << endl;
    }

    return valid;
}