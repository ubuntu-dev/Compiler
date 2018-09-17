/*
 * TestGraphBuilder.h
 *
 *  Created on: Apr 23, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_CALCULATOR_TEST_UTILS_TESTGRAPH_H_
#define SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_CALCULATOR_TEST_UTILS_TESTGRAPH_H_

#include <vector>
#include <unordered_set>
#include "../models/GrammarElement.h"
#include "../models/GrammarExpression.h"

using namespace std;

void build_lecture_example_1(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions,
		bool set_first, bool set_follow);

void build_lecture_example_2(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions,
		bool set_first, bool set_follow);

void build_lecture_example_3(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions,
		bool set_first, bool set_follow);

void build_sheet_four_pro_two(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions,
		bool set_first, bool set_follow);

void build_pdf(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions,
		bool set_first, bool set_follow);

bool compare_non_terminals(NonTerminal * t, NonTerminal * c, vector<string> * errors);
bool compare_exp(GrammarExpression * e, GrammarExpression * c, vector<string> * errors);
void destroy_graph(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions);
void print_errors(vector<string> * errors);
int test_graph_results(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions,
		vector<GrammarElement *> * c_elements, unordered_set<GrammarExpression *> *c_expressions, vector<string> * errors);
#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_CALCULATOR_TEST_UTILS_TESTGRAPH_H_ */
