/*
 * GrammerParserTest.cpp
 *
 *  Created on: Mar 19, 2018
 *      Author: amrnasr
 */

#include "../../../test_headers/p1_tests.h"
#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <vector>
#include "../models/NfaToken.h"
#include "LexicalFileParser.h"

using namespace std;

bool equal_token(NfaToken a, NfaToken b);
void print_token(NfaToken a);
static const vector<NfaToken> correctTokens = {
		NfaToken (REGULAR_EXPRESSION, "id", vector<MiniToken> ({
				MiniToken (CHAR_GROUP, "a-z"),
				MiniToken (CHAR_GROUP, "A-Z"),
				MiniToken (OPERATION, "|"),
				MiniToken (CHAR_GROUP, "a-z"),
				MiniToken (CHAR_GROUP, "A-Z"),
				MiniToken (OPERATION, "|"),
				MiniToken (CHAR_GROUP, "0-9"),
				MiniToken (OPERATION, "|"),
				MiniToken (OPERATION, "*"),
				MiniToken (OPERATION, "@")
		})),
		NfaToken (KEYWORD, "boolean", vector<MiniToken> ({MiniToken (WORD, "boolean")})),
		NfaToken (KEYWORD, "int", vector<MiniToken> ({MiniToken (WORD, "int")})),
		NfaToken (KEYWORD, "float", vector<MiniToken> ({MiniToken (WORD, "float")})),
		NfaToken (REGULAR_EXPRESSION, "num", vector<MiniToken> ({
				MiniToken (CHAR_GROUP, "0-9"),
				MiniToken (OPERATION, "+"),
				MiniToken (CHAR_GROUP, "0-9"),
				MiniToken (OPERATION, "+"),
				MiniToken (WORD, "."),
				MiniToken (OPERATION, "@"),
				MiniToken (CHAR_GROUP, "0-9"),
				MiniToken (OPERATION, "+"),
				MiniToken (OPERATION, "@"),
				MiniToken (EPSILON, "\\L"),
				MiniToken (WORD, "E"),
				MiniToken (CHAR_GROUP, "0-9"),
				MiniToken (OPERATION, "+"),
				MiniToken (OPERATION, "@"),
				MiniToken (OPERATION, "|"),
				MiniToken (OPERATION, "@"),
				MiniToken (OPERATION, "|"),
		})),
		NfaToken (REGULAR_EXPRESSION, "relop", vector<MiniToken> ({
				MiniToken (WORD, "=="),
				MiniToken (WORD, "!="),
				MiniToken (OPERATION, "|"),
				MiniToken (WORD, ">"),
				MiniToken (OPERATION, "|"),
				MiniToken (WORD, ">="),
				MiniToken (OPERATION, "|"),
				MiniToken (WORD, "<"),
				MiniToken (OPERATION, "|"),
				MiniToken (WORD, "<="),
				MiniToken (OPERATION, "|")
		})),
		NfaToken (REGULAR_EXPRESSION, "assign", vector<MiniToken> ({MiniToken (WORD, "=")})),
		NfaToken (KEYWORD, "if", vector<MiniToken> ({MiniToken (WORD, "if")})),
		NfaToken (KEYWORD, "else", vector<MiniToken> ({MiniToken (WORD, "else")})),
		NfaToken (KEYWORD, "while", vector<MiniToken> ({MiniToken (WORD, "while")})),
		NfaToken (PUNCTUATION, ";", vector<MiniToken> ({MiniToken (WORD, ";")})),
		NfaToken (PUNCTUATION, ",", vector<MiniToken> ({MiniToken (WORD, ",")})),
		NfaToken (PUNCTUATION, "(", vector<MiniToken> ({MiniToken (WORD, "(")})),
		NfaToken (PUNCTUATION, ")", vector<MiniToken> ({MiniToken (WORD, ")")})),
		NfaToken (PUNCTUATION, "{", vector<MiniToken> ({MiniToken (WORD, "{")})),
		NfaToken (PUNCTUATION, "}", vector<MiniToken> ({MiniToken (WORD, "}")})),
		NfaToken (REGULAR_EXPRESSION, "addop", vector<MiniToken> ({
			MiniToken (WORD, "+"),
			MiniToken (WORD, "-"),
			MiniToken (OPERATION, "|"),
		})),
		NfaToken (REGULAR_EXPRESSION, "mulop", vector<MiniToken> ({
			MiniToken (WORD, "*"),
			MiniToken (WORD, "/"),
			MiniToken (OPERATION, "|"),
		}))
};

static const vector<string> correctPriority = {
		";", ",", "(", ")", "{", "}", "boolean", "int", "float", "if" , "else", "while", "id", "num",
		"relop", "assign", "addop", "mulop"
};

void test_grammar_parser(void) {
	LexicalFileParser gp;
	vector<NfaToken> regTokens;
	vector<string> priorites;
	set<char> alpha;
	bool error = false;
	ifstream infile;
	infile.open("./test_files/grammar_parser/correct_rules.txt");
	if (!infile) {
		cout << "GRAMMAR PARSER TEST : COULDN\"T OPEN WANTED FILE" << endl;
		return;
	}
	if (!gp.parse_lexical_file(&regTokens, &priorites, &infile, &alpha).empty()) {
		cout << "ERROR DETECTED IN RIGHT PROGRAM!!" << endl;
		error = true;
	}
	unsigned i = 0;
	for (auto it = regTokens.begin(); it != regTokens.end(); ++it) {
	    NfaToken tok = (*it);
	    if (!equal_token(tok, correctTokens[i])) {
	    	error = true;
	    	cout << "WRONG. Found : " << endl;
	    	print_token(tok);
	    	cout << "Expected : " << endl;
	    	print_token(correctTokens[i]);
	    	cout << "..............................................................." << endl;
	    }
	    if (priorites[i] != correctPriority[i]) {
	    	error = true;
			cout << "WRONG. Found Priority: " << priorites[i] << endl;
			cout << "Expected Priority: " << correctPriority[i] << endl;
			cout << "..............................................................." << endl;
	    }
	    i++;
	}
	infile.close();
	for (unsigned n = 1; n < 5; n++) {
		infile.open("./test_files/grammar_parser/wrong_rules"+ to_string(n) + ".txt");
		if (!infile) {
			cout << "GRAMMAR PARSER TEST : COULDN\"T OPEN WANTED FILE" << endl;
			return;
		}
		vector<string> errors = gp.parse_lexical_file(&regTokens, &priorites, &infile, &alpha);
		if (errors.empty()) {
			cout << "NO ERROR DETECTED IN WRONG PROGRAM!!" << endl;
			error = true;
		} else if ((n == 1 && errors.size() != 3) ||(errors.size() != 2 && n != 1)) {
			cout << "Wrong number of errors detected !" << endl;
			error = true;
			cout << "Wrong rules " << n << endl;
			for (unsigned i = 0; i < errors.size(); i++) {
				cout << errors[i] << endl;
			}
			cout << ".........................................................................." << endl;
		}
		infile.close();
	}
	if (!error) {
		cout << "Grammar Parser Success..." << endl;
	} else {
		cout << "Grammar Parser Failed..." << endl;
	}
}

bool equal_token(NfaToken a, NfaToken b) {
	bool res = a.tokenName == b.tokenName && a.type == b.type && a.tokens.size() == b.tokens.size();
	unsigned i = 0;
	while (res && i < a.tokens.size()) {
		res = res && (a.tokens[i].tok == b.tokens[i].tok && a.tokens[i].type == b.tokens[i].type);
		i++;
	}
	return res;
}

void print_token(NfaToken a) {
	cout << "Token Name : \"" << a.tokenName << "\"\n";
	cout << "Token Type : " << a.type << endl;
	unsigned i = 0;
	cout << "Tokens :" << endl;
	while (i < a.tokens.size()) {
		cout << "(\"" <<a.tokens[i].tok << "\" , "<<a.tokens[i].type << ") ";
		i++;
	}
	cout << endl;
}
