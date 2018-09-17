/*
 * FollowCalculatorTest.cpp
 *
 *  Created on: Apr 18, 2018
 *      Author: amrnasr
 */

#include "../../../test_headers/p2_tests.h"
#include "FollowCalculator.h"
#include "../models/NonTerminal.h"
#include <iostream>
#include "../calculator_test_utils/TestGraph.h"

void test_follow_calculator() {
	FollowCalculator cal;
	bool no_error = true;
	vector<GrammarElement *> ele, cele;
	unordered_set<GrammarExpression *> exp, cexp;
	vector<string> errors;
	// First test.
	build_lecture_example_1(&ele, &exp, true, false);
	build_lecture_example_1(&cele, &cexp, true, true);
	cal.set_follow_sets(&ele, &exp);
	if(test_graph_results(&ele, &exp, &cele, &cexp, &errors) > 0) {
		no_error = false;
		cout << "Follow : Lecture Example 1 Failed : " << endl;
		print_errors(&errors);
	}
	destroy_graph(&ele, &exp);
	destroy_graph(&cele, &cexp);
	ele.clear();
	exp.clear();
	cele.clear();
	cexp.clear();
	errors.clear();
	// Second test.
	build_lecture_example_2(&ele, &exp, true, false);
	build_lecture_example_2(&cele, &cexp, true, true);
	cal.set_follow_sets(&ele, &exp);
	if(test_graph_results(&ele, &exp, &cele, &cexp, &errors) > 0) {
		no_error = false;
		cout << "Follow : Lecture Example 2 Failed : " << endl;
		print_errors(&errors);
	}
	destroy_graph(&ele, &exp);
	destroy_graph(&cele, &cexp);
	ele.clear();
	exp.clear();
	cele.clear();
	cexp.clear();
	errors.clear();
	// Third test.
	build_lecture_example_3(&ele, &exp, true, false);
	build_lecture_example_3(&cele, &cexp, true, true);
	cal.set_follow_sets(&ele, &exp);
	if(test_graph_results(&ele, &exp, &cele, &cexp, &errors) > 0) {
		no_error = false;
		cout << "Follow : Lecture Example 3 Failed : " << endl;
		print_errors(&errors);
	}
	destroy_graph(&ele, &exp);
	destroy_graph(&cele, &cexp);
	ele.clear();
	exp.clear();
	cele.clear();
	cexp.clear();
	errors.clear();
	// Fourth Test.
	build_sheet_four_pro_two(&ele, &exp, true, false);
	build_sheet_four_pro_two(&cele, &cexp, true, true);
	cal.set_follow_sets(&ele, &exp);
	if(test_graph_results(&ele, &exp, &cele, &cexp, &errors) > 0) {
		no_error = false;
		cout << "Follow : Sheet 4 Problem 2 Failed : " << endl;
		print_errors(&errors);
	}
	destroy_graph(&ele, &exp);
	destroy_graph(&cele, &cexp);
	ele.clear();
	exp.clear();
	cele.clear();
	cexp.clear();
	errors.clear();
	// Fifth test.
	build_pdf(&ele, &exp, true, false);
	build_pdf(&cele, &cexp, true, true);
	cal.set_follow_sets(&ele, &exp);
	if(test_graph_results(&ele, &exp, &cele, &cexp, &errors) > 0) {
		no_error = false;
		cout << "Follow : Pdf Failed : " << endl;
		print_errors(&errors);
	}
	destroy_graph(&ele, &exp);
	destroy_graph(&cele, &cexp);
	ele.clear();
	exp.clear();
	cele.clear();
	cexp.clear();
	errors.clear();
	// Print final result.
	if (!no_error) {
		cout << "Follow Calculator Failed Test..." << endl;
	} else {
		cout << "Follow Calculator Success..." << endl;
	}
}
