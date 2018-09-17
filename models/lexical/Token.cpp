/*
 * Token.cpp
 *
 *  Created on: Mar 23, 2018
 *      Author: amrnasr
 */

#include "token.h"

Token::Token(TOKEN_TYPE tp, string token, string tokClass) {
	this->type = tp;
	this->token_class = tokClass;
	this->lexme = token;
}

