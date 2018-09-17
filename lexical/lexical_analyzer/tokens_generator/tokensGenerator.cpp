//
// Created by marc on 3/24/18.
//

#include <iostream>
#include <fstream>
#include "tokensGenerator.h"
#include "../symbol_table_writer/SymbolTableWriter.h"
#include "../token_writer/TokenWriter.h"
#include "../../../utils/Utils.h"

using namespace std;

void TokensGenerator::generateTokens(string transitionTableFilePath, string sourceProgramFilePath) {
    bool transitionTableRead = this->lexicalAnalyzer.read_transition_table(transitionTableFilePath);
    if (!transitionTableRead) { // error reading transition table file
        cout << "Error reading transition table file!" << endl;
        return;
    }

    bool sourceProgramRead = this->lexicalAnalyzer.analyze_program(sourceProgramFilePath);
    if (!sourceProgramRead) {
        cout << "Error reading source program file" << endl;
        return;
    }

    vector<Token> tokens;
    this->fillTokensVector(&tokens);
    string sysName = handle_file_name_extension(sourceProgramFilePath, "sym");
    string tokName = handle_file_name_extension(sourceProgramFilePath, "token");
    ofstream symbolStreamFile;
    symbolStreamFile.open(sysName);
    streambuf *buf1 = symbolStreamFile.rdbuf();
    ostream symbolsOut(buf1);

    ofstream tokenStream;
    tokenStream.open(tokName);
    streambuf *buf2 = tokenStream.rdbuf();
    ostream tokensOut(buf2);

    write_symbol_table(tokens, &symbolsOut);
    write_tokens(tokens, &tokensOut);
}

void TokensGenerator::fillTokensVector(vector<Token>* tokens) {
    while (this->lexicalAnalyzer.has_next()) {
        tokens->push_back(this->lexicalAnalyzer.next_token());
    }
}
