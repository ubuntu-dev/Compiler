//
// Created by marc on 3/24/18.
//

#ifndef COMPILERS_TOKENS_GENERATOR_H
#define COMPILERS_TOKENS_GENERATOR_H


#include "../LexicalAnalyzer.h"

class TokensGenerator {
    private:
        LexicalAnalyzer lexicalAnalyzer;
        void fillTokensVector (vector<Token>*);
    public:
        void generateTokens (string transitionTableFilePath, string sourceProgramFilePath);
};


#endif //COMPILERS_TOKENS_GENERATOR_H
