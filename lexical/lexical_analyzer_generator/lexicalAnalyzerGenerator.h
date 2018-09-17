/*
 * lexicalAnalyzerGenerator.h
 *
 *  Created on: Mar 21, 2018
 *      Author: amrnasr
 */

#ifndef LEXICAL_ANALYZER_GENERATOR_LEXICALANALYZERGENERATOR_H_
#define LEXICAL_ANALYZER_GENERATOR_LEXICALANALYZERGENERATOR_H_

#include "builder/NfaBuilder.h"
#include "combiner/NfaCombiner.h"
#include "converter/NfaDfaConverter.h"
#include "minimizer/DfaMinimizer.h"
#include "../transition_table/builder/TableBuilder.h"
#include "../transition_table/writer/TableWriter.h"
#include "file_parser/LexicalFileParser.h"

class LexicalAnalyzerGenerator {
	private:
		LexicalFileParser grammarParser;
		NfaBuilder builder;
		NFACombiner combiner;
		NfaDfaConverter converter;
		DfaMinimizer minimzer;
		TableBuilder tableBuilder;
		TableWriter tableWriter;
	public:
		void generate_lexical_analyzer(string file_name, bool print = true);
};


#endif /* LEXICAL_ANALYZER_GENERATOR_LEXICALANALYZERGENERATOR_H_ */
