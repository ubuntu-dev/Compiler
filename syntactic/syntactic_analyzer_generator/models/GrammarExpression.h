/*
 * GrammarExpression.h
 *
 *  Created on: Apr 17, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_GRAMMAREXPRESSION_H_
#define SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_GRAMMAREXPRESSION_H_

#include "GrammarElement.h"
#include "NonTerminal.h"
#include <vector>
#include <unordered_set>
#include <iostream>

using namespace std;

class NonTerminal;

class GrammarExpression {
	public:
	GrammarExpression(GrammarElement *element);
	std::vector<GrammarElement *> expression;
	NonTerminal * belongs_to;
	bool eps;
	std::unordered_set<string> first_strings;
	void print_expression(void);
	string getName(void);
};

#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_GRAMMAREXPRESSION_H_ */
