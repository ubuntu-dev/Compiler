/*
 * FirstCalculatorTest->cpp
 *
 *  Created on: Apr 18, 2018
 *      Author: amrnasr
 */

#include "../../../test_headers/p2_tests.h"
#include "FirstCalculator.h"
#include "../models/NonTerminal.h"
#include <iostream>

#include "../calculator_test_utils/TestGraph.h"

void test_first_calculator() {
	FirstCalculator cal;
	bool no_error = true;
	vector<GrammarElement *> ele, cele;
	unordered_set<GrammarExpression *> exp, cexp;
	vector<string> errors;
	// First test.
	build_lecture_example_1(&ele, &exp, false, false);
	build_lecture_example_1(&cele, &cexp, true, false);
	cal.set_first_sets(&ele, &exp);
	if(test_graph_results(&ele, &exp, &cele, &cexp, &errors) > 0) {
		no_error = false;
		cout << "First : Lecture Example 1 Failed : " << endl;
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
	build_lecture_example_2(&ele, &exp, false, false);
	build_lecture_example_2(&cele, &cexp, true, false);
	cal.set_first_sets(&ele, &exp);
	if(test_graph_results(&ele, &exp, &cele, &cexp, &errors) > 0) {
		no_error = false;
		cout << "First : Lecture Example 2 Failed : " << endl;
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
	build_lecture_example_3(&ele, &exp, false, false);
	build_lecture_example_3(&cele, &cexp, true, false);
	cal.set_first_sets(&ele, &exp);
	if(test_graph_results(&ele, &exp, &cele, &cexp, &errors) > 0) {
		no_error = false;
		cout << "First : Lecture Example 3 Failed : " << endl;
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
	build_sheet_four_pro_two(&ele, &exp, false, false);
	build_sheet_four_pro_two(&cele, &cexp, true, false);
	cal.set_first_sets(&ele, &exp);
	if(test_graph_results(&ele, &exp, &cele, &cexp, &errors) > 0) {
		no_error = false;
		cout << "First : Sheet 4 Problem 2 Failed : " << endl;
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
	build_pdf(&ele, &exp, false, false);
	build_pdf(&cele, &cexp, true, false);
	cal.set_first_sets(&ele, &exp);
	if(test_graph_results(&ele, &exp, &cele, &cexp, &errors) > 0) {
		no_error = false;
		cout << "First : Pdf Example Failed : " << endl;
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
		cout << "First Calculator Failed Test..." << endl;
	} else {
		cout << "First Calculator Success..." << endl;
	}
}
