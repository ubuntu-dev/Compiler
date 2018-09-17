/*
 * GrammarTableBuilder.h
 *
 *  Created on: Apr 17, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_TABLE_BUILDER_GRAMMARTABLEBUILDER_H_
#define SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_TABLE_BUILDER_GRAMMARTABLEBUILDER_H_

#include "../../grammar_table/model/GrammarTable.h"
#include "../models/GrammarElement.h"
#include "../models/GrammarExpression.h"
#include <vector>

using namespace std;

class GrammarTableBuilder {
	private:
		void set_expression_vector(vector<string>* expression_vector
				, GrammarExpression* grammarExpression);
		void build_terminals_nonTerminals(GrammarTable* table, vector<GrammarElement *> * rules);
	public:
		GrammarTable* build_grammar_table(vector<GrammarElement *> * rules,
		vector<string> * errors);
};

#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_TABLE_BUILDER_GRAMMARTABLEBUILDER_H_ */
