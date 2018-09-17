/*
 * NonTerminal.h
 *
 *  Created on: Apr 18, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_NONTERMINAL_H_
#define SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_NONTERMINAL_H_

//#include "GrammarElement.h"
#include "GrammarExpression.h"
#include <unordered_set>


using namespace std;

class GrammarExpression;

class NonTerminal : public GrammarElement {
public:
	NonTerminal(const string &name, ElementType type);
	bool eps;
	vector<GrammarExpression *> leads_to;
	vector<GrammarExpression *> referenced_in;
	unordered_set<string> first_strings;
	unordered_set<string> follow_strings;
};


#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_NONTERMINAL_H_ */
