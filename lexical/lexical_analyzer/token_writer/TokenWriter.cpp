/*
 * TokenWriter.cpp
 *
 *  Created on: Mar 23, 2018
 *      Author: amrnasr
 */

#include "TokenWriter.h"

void write_tokens(vector<Token> tokens, ostream * outStream) {
	for (unsigned i = 0; i < tokens.size(); i++) {
		if (tokens[i].type == REAL_TOKEN) {
			(*outStream) << tokens[i].token_class;
		} else {
			(*outStream) << "**ERROR : UNDEFINED TOKEN \"" << tokens[i].lexme << "\"";
		}
		(*outStream) << endl;
	}
}


