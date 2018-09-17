/*
 * SyntacticAnalyzer.h
 *
 *  Created on: Apr 17, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_SYNTACTIC_ANALYZER_SYNTACTICANALYZER_H_
#define SYNTACTIC_SYNTACTIC_ANALYZER_SYNTACTICANALYZER_H_

#include <string>
#include <stack>
#include <vector>
#include "../grammar_table/reader/GrammarTableReader.h"
#include "../../lexical/lexical_analyzer/LexicalAnalyzer.h"
#include "parser/Parser.h"
#include "writers/DerivationsWriter.h"
#include "writers/ErrorsWriter.h"



using namespace std;

class SyntacticAnalyzer {
	private:
		LexicalAnalyzer lexAnalyzer;
		Parser parser;
		GrammarTableReader tableReader;
	public:
		bool analyze_program(string file_name, vector<string> *errors, vector<vector<string>> *derivations);
		bool read_transition_table(string file_name);
		bool read_grammar_table(string file_name);
};



#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_SYNTACTICANALYZER_H_ */
