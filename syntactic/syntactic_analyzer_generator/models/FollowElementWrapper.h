/*
 * FollowElementWrapper.h
 *
 *  Created on: Apr 18, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_FOLLOWELEMENTWRAPPER_H_
#define SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_FOLLOWELEMENTWRAPPER_H_

#include "GrammarElement.h"
#include <unordered_set>
#include <string>
#include "NonTerminal.h"

using namespace std;

class FollowElementWrapper {
	public:
		NonTerminal * core;
		unordered_set<FollowElementWrapper *> follow_elements;
		unordered_set<string> follow_strings;
};



#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_FOLLOWELEMENTWRAPPER_H_ */
