/*
 * Parser.h
 *
 *  Created on: Apr 17, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_SYNTACTIC_ANALYZER_PARSER_PARSER_H_
#define SYNTACTIC_SYNTACTIC_ANALYZER_PARSER_PARSER_H_

#include <string>
#include <stack>
#include <vector>
#include "../../grammar_table/model/GrammarTable.h"
#include "../../../models/lexical/token.h"

class Parser {
	private:
		GrammarTable table;
		vector<string> rules; // used as a stack
		vector<string> errors;
		vector<vector<string>> derivations;
		vector<string> matched_tokens;
		unsigned int current_derived_index;
		void copy_vector(vector<string>* src, vector<string>* destination);
		void add_new_rule(vector<string>* derivation);
		void add_matched_tokens(vector<string>* derivation);
		void add_current_rules(vector<string>* derivation);
	public:
		void set_grammar_table(GrammarTable gTable);
		/**.
		 * Inititalize the stack, push the sign dollar and first rule.
		 */
		void init_parser();

		void derive_token(Token token);
		/**.
		 * @param rerrors strong copy of errors.
		 * @param rderiv strong copy of derivations.
		 */
		void finish_derivation(vector<string> *rerrors, vector<vector<string>> * rderiv);
};



#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_PARSER_PARSER_H_ */
