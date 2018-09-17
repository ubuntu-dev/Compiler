/*
 * NonTerminal.cpp
 *
 *  Created on: Apr 21, 2018
 *      Author: amrnasr
 */

#include "NonTerminal.h"

NonTerminal::NonTerminal(const string &name, ElementType type): GrammarElement(name, type){
	this->eps = false;
}
