/*
 * SymbolTableWriter.cpp
 *
 *  Created on: Mar 23, 2018
 *      Author: amrnasr
 */

#include "SymbolTableWriter.h"
#include <iostream>
#include <iomanip>

using namespace std;

const char separator    = ' ';
const int classWidth     = 30;
const int tokenlex      = 50;

void print_line(Token token, ostream * outStream);

void write_symbol_table(vector<Token> tokens, ostream * outStream) {
	for (unsigned i = 0; i < tokens.size(); i++) {
		print_line(tokens[i], outStream);
	}
}

void print_line(Token token, ostream * outStream) {
	if (token.type == REAL_TOKEN) {
		(*outStream) << left << setw(classWidth) << setfill(separator) << token.token_class;
		(*outStream) << "| ";
		(*outStream) << left << setw(tokenlex) << setfill(separator) << token.lexme;
	} else {
		(*outStream) << left << setw(classWidth) << setfill(separator) << "**ERROR**Undefined token";
		(*outStream) << "| ";
		(*outStream) << left << setw(tokenlex) << setfill(separator) << token.lexme;
	}
	(*outStream) << endl;
}

