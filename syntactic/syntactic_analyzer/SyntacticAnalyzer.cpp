/*
 * SyntacticAnalyzer.cpp
 *
 *  Created on: Apr 26, 2018
 *      Author: amrnasr
 */


#include "SyntacticAnalyzer.h"

bool SyntacticAnalyzer::analyze_program(string file_name, vector<string> *errors, vector<vector<string>> *derivations) {
	if (!this->lexAnalyzer.analyze_program(file_name)) {
		return false;
	}
	this->parser.init_parser();
	while (this->lexAnalyzer.has_next()) {
		this->parser.derive_token(this->lexAnalyzer.next_token());
	}
	this->parser.finish_derivation(errors, derivations);
	return true;
}

bool SyntacticAnalyzer::read_transition_table(string file_name) {
	return this->lexAnalyzer.read_transition_table(file_name);
}

bool SyntacticAnalyzer::read_grammar_table(string file_name) {
	ifstream infile;
	infile.open(file_name);
	if (!infile) {
		return false;
	}
	GrammarTable * table = this->tableReader.readGrammarTable(&infile);
	if (table == nullptr) {
		return false;
	}
	this->parser.set_grammar_table(*table);
	delete table;
	return true;
}

