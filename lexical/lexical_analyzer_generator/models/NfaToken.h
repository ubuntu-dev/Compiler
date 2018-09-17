/*
 * NfaToken.h
 *
 *  Created on: Mar 19, 2018
 *      Author: amrnasr
 */

#ifndef MODELS_NFATOKEN_H_
#define MODELS_NFATOKEN_H_

#include <string>
#include <vector>

using namespace std;

enum MiniType {OPERATION, CHAR_GROUP, WORD, EPSILON, PARENTHESES};
enum TokenType{PUNCTUATION, KEYWORD, REGULAR_EXPRESSION};

class MiniToken {
public:
    MiniType type;
    string tok;
    MiniToken(MiniType tp, string token);
};

class NfaToken {
public:
    string tokenName;
    vector<MiniToken> tokens;
    TokenType type;
    NfaToken(TokenType tp, string tkName);
    NfaToken(TokenType tp, string tkName, vector<MiniToken> list_tok);
};


#endif /* MODELS_NFATOKEN_H_ */
