/*
 * LexicalAnalyzer.h
 *
 *  Created on: Mar 23, 2018
 *      Author: amrnasr
 */

#ifndef LEXICAL_ANALYZER_LEXICALANALYZER_H_
#define LEXICAL_ANALYZER_LEXICALANALYZER_H_

#include "source_reader/SourceReader.h"
#include "tokenizer/tokenizer.h"

class LexicalAnalyzer {
	private:
		Tokenizer tokenizer;
	public:
		Token next_token();
		bool has_next();
		bool analyze_program(string file_name);
		bool read_transition_table(string file_name);
};



#endif /* LEXICAL_ANALYZER_LEXICALANALYZER_H_ */
