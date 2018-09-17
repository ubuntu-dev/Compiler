/*
 * SyntacticAnalyzerGenerator.h
 *
 *  Created on: Apr 17, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_SYNTACTICANALYZERGENERATOR_H_
#define SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_SYNTACTICANALYZERGENERATOR_H_

#include "file_parser/GrammarFileParser.h"
#include "table_builder/GrammarTableBuilder.h"
#include "../grammar_table/writer/GrammarTableWriter.h"
#include "ll_converter/LlConverter.h"
#include "first_calculator/FirstCalculator.h"
#include "follow_calculator/FollowCalculator.h"

class SyntacticAnalyzerGenerator {
	private:
		GrammarFileParser grammarParser;
		FirstCalculator firstCalculator;
		FollowCalculator followCalculator;
		LlConverter converter;
		GrammarTableBuilder tableBuilder;
		GrammarTableWriter tableWriter;
	public:
		void generate_syntactic_analyzer(string file_name, bool print = true);
};


#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_SYNTACTICANALYZERGENERATOR_H_ */
