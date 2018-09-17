/*
 * NfaToken.cpp
 *
 *  Created on: Mar 19, 2018
 *      Author: amrnasr
 */
#include "NfaToken.h"

MiniToken::MiniToken(MiniType tp, string token) {
	this->tok = token;
	this->type = tp;
}

NfaToken::NfaToken(TokenType tp, string tkName) {
	this->tokenName = tkName;
	this->type = tp;
}

NfaToken::NfaToken(TokenType tp, string tkName, vector<MiniToken> listTok) {
	this->tokenName = tkName;
	this->type = tp;
	this->tokens = listTok;
}
