/*
 * token.h
 *
 *  Created on: Mar 23, 2018
 *      Author: amrnasr
 */

#ifndef LEXICAL_ANALYZER_MODELS_TOKEN_H_
#define LEXICAL_ANALYZER_MODELS_TOKEN_H_

#include <string>

using namespace std;

enum TOKEN_TYPE {REAL_TOKEN, ERROR_TOKEN};

class Token {
	public:
		TOKEN_TYPE type;
		string lexme;
		string token_class;
		Token(TOKEN_TYPE tp, string token, string tokClass);
};


#endif /* LEXICAL_ANALYZER_MODELS_TOKEN_H_ */
