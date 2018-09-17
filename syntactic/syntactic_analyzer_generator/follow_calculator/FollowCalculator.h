/*
 * FollowCalculator.h
 *
 *  Created on: Apr 17, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_FOLLOW_CALCULATOR_FOLLOWCALCULATOR_H_
#define SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_FOLLOW_CALCULATOR_FOLLOWCALCULATOR_H_

#include <vector>
#include <unordered_set>
#include "../models/GrammarElement.h"
#include "../models/GrammarExpression.h"

using namespace std;

class FollowCalculator {
	public:
		void set_follow_sets(vector<GrammarElement *> *rules , unordered_set<GrammarExpression *> * expressions);
};



#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_FOLLOW_CALCULATOR_FOLLOWCALCULATOR_H_ */
