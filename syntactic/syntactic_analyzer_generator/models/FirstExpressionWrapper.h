/*
 * FirstExpressionWrapper.h
 *
 *  Created on: Apr 18, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_FIRSTEXPRESSIONWRAPPER_H_
#define SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_FIRSTEXPRESSIONWRAPPER_H_

#include "GrammarExpression.h"
#include "FirstElementWrapper.h"
#include <string>
#include <vector>
#include <set>

using namespace std;

class FirstElementWrapper;

class FirstExpressionWrapper {
	public:
		GrammarExpression * core;
		set<FirstElementWrapper *> first_elements;
		set<string> first_strings;
};



#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_FIRSTEXPRESSIONWRAPPER_H_ */
