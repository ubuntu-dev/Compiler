/*
 * tokenizer.cpp
 *
 *  Created on: Mar 23, 2018
 *      Author: amrnasr
 */
#include "tokenizer.h"

bool Tokenizer::hasNext() {
	return !this->tokens.empty();
}

Token Tokenizer::nextToken() {
	Token tok = this->tokens.front();
	this->tokens.pop();
	return tok;
}

void Tokenizer::tokenize(string str) {
	DfaNode * lastAccepted = nullptr;
	DfaNode * curNode = this->machine;
	string lastAcceptedBuffer = "";
	string errorBuffer = "";
	string currentBuffer = "";
	unsigned lastAcceptanceEnd = 0;
	for (unsigned i = 0; i < str.length(); i++) {
		char c = str.at(i);
		if (curNode->valid_transition(c)) {
			curNode = curNode->do_transition(c);
			currentBuffer += c;
			if (curNode->isAcceptedState()) {
				lastAcceptanceEnd = i;
				lastAccepted = curNode;
				lastAcceptedBuffer = currentBuffer;
			}
		} else {
			if (lastAccepted != nullptr) {
				if (!errorBuffer.empty()) {
					this->tokens.push(Token(ERROR_TOKEN, errorBuffer, ""));
					errorBuffer = "";
				}
				this->tokens.push(Token(REAL_TOKEN, lastAcceptedBuffer, lastAccepted->getName()));
			} else {
				if (currentBuffer.empty()) {
					errorBuffer += c;
					lastAcceptanceEnd = i;
				} else {
					errorBuffer += currentBuffer.at(0);
				}
			}
			i = lastAcceptanceEnd;
			lastAccepted = nullptr;
			currentBuffer = "";
			lastAcceptedBuffer = "";
			curNode = this->machine;
		}
	}

	if (!errorBuffer.empty()) {
		this->tokens.push(Token(ERROR_TOKEN, errorBuffer, ""));
	}
	if (lastAccepted != nullptr) {
		this->tokens.push(Token(REAL_TOKEN, lastAcceptedBuffer, lastAccepted->getName()));
	}
}

void Tokenizer::reset() {
	queue<Token>().swap(this->tokens);
}

Tokenizer::Tokenizer(DfaNode * start) {
	this->machine = start;
}

Tokenizer::Tokenizer() = default;

void Tokenizer::setStart(DfaNode * newStart) {
	this->machine = newStart;
	this->reset();
}
