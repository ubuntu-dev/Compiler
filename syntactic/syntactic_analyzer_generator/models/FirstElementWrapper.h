/*
 * FirstElementWrapper.h
 *
 *  Created on: Apr 18, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_FIRSTELEMENTWRAPPER_H_
#define SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_FIRSTELEMENTWRAPPER_H_

#include "GrammarElement.h"
#include "FirstExpressionWrapper.h"
#include <string>
#include <vector>
#include <set>
#include "NonTerminal.h"

using namespace std;

class FirstExpressionWrapper;

class FirstElementWrapper {
	public:
		NonTerminal * core;
		set<FirstElementWrapper *> first_elements;
		set<string> first_strings;
};


#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_FIRSTELEMENTWRAPPER_H_ */
