/*
 * lexicalAnalyzerGeneratorTest.cpp
 *
 *  Created on: Mar 24, 2018
 *      Author: amrnasr
 */

#include "../../test_headers/p1_tests.h"
#include <vector>
#include <string>
#include <iostream>
#include "lexicalAnalyzerGenerator.h"
#include <fstream>
#include "../../utils/Utils.h"

using namespace std;



const vector<string> tests = {"rules"};

void test_analyzer_generator() {
	bool error = false;
	LexicalAnalyzerGenerator generator;
	cout << "Lexical analyzer generator ";
	for (unsigned i = 0; i < tests.size(); i++) {
		generator.generate_lexical_analyzer("test_files/lexical_top_level/tests/" + tests[i] + ".txt", false);
		ifstream if1, if2, cf1, cf2;
		string if1name = "test_files/lexical_top_level/tests/" + tests[i] + ".trnstb";
		string if2name = "test_files/lexical_top_level/tests/H_" + tests[i] + ".trnstb";
		if1.open(if1name);
		if2.open(if2name);
		cf1.open("test_files/lexical_top_level/answers/" + tests[i] + ".trnstb");
		cf2.open("test_files/lexical_top_level/answers/H_" + tests[i] + ".trnstb");
		if (!cf1 || !cf2) {
			cout << "Error : couldn't open correct answers files" << endl;
			if (if1) {
				remove(if1name.c_str());
			}
			if (if2) {
				remove(if2name.c_str());
			}
			error = true;
			break;
		} else {
			if (!if1 && !if2) {
				cout << "Error : couldn't find generated file " << if1name << " " << if2name << endl;
				error = true;
				break;
			}
			if (!if1) {
				cout << "Error : couldn't find generated file " << if2name << endl;
				error = true;
				remove(if2name.c_str());
				break;
			}
			if (!if2) {
				cout << "Error : couldn't find generated file " << if1name  << endl;
				error = true;
				remove(if1name.c_str());
				break;
			}
			if ((!compare_streams(&if1, &cf1, tests[i])) || !(compare_streams(&if2, &cf2, tests[i]))) {
				error = true;
				break;
			}
			remove(if1name.c_str());
			remove(if2name.c_str());
		}
	}
	if (!error) {
		cout << "success..." << endl;
	}
}
