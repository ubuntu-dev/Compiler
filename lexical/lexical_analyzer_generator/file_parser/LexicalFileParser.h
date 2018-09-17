/*
 * GrammarParser.h
 *
 *  Created on: Mar 19, 2018
 *      Author: amrnasr
 */

#ifndef GRAMMAR_PARSER_GRAMMARPARSER_H_
#define GRAMMAR_PARSER_GRAMMARPARSER_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <set>
#include "../models/NfaToken.h"

using namespace std;

class LexicalFileParser {
	private:
		static const regex regDefRegex;
		static const regex regExpRegex;
		static const regex keyWordRegex;
		static const regex punctRegex;
	public:
		vector<string> parse_lexical_file(vector<NfaToken> *tokens , vector<string> * priorites, ifstream * lexical_file_stream, set<char> *alphabet);
};



#endif /* GRAMMAR_PARSER_GRAMMARPARSER_H_ */
