/*
 * LexicalAnalyzer.cpp
 *
 *  Created on: Mar 23, 2018
 *      Author: amrnasr
 */
#include "LexicalAnalyzer.h"
#include "../transition_table/reader/TableReader.h"
#include "../transition_table/deconstructor/TableDeconstructor.h"

Token LexicalAnalyzer::next_token() {
	return this->tokenizer.nextToken();
}

bool LexicalAnalyzer::has_next() {
	return this->tokenizer.hasNext();
}

bool LexicalAnalyzer::analyze_program(string file_name) {
	queue<string> words;
	this->tokenizer.reset();
	if(!read_source_file(&words, file_name)) {
		return false;
	}
	while(!words.empty()) {
		this->tokenizer.tokenize(words.front());
		words.pop();
	}
	return true;
}

bool LexicalAnalyzer::read_transition_table(string file_name) {
	TableReader reader;
	ifstream infile;
	infile.open(file_name);
	if (!infile) {
		return false;
	}
	TransitionTable * table = reader.readTransitionTable(&infile);
	if (table == nullptr) {
		return false;
	}
	TableDeconstructor converter;
	this->tokenizer.setStart(converter.deconstructGraph(*table)[0]);
	delete table;
	return true;
}
