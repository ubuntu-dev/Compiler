/*
 * Nfa.h
 *
 *  Created on: Mar 19, 2018
 *      Author: amrnasr
 */

#ifndef MODELS_NFA_H_
#define MODELS_NFA_H_

#include "Node.h"

class Nfa {
	public:
		Node *start;
		Node *end;
		void print_nfa();
};

#endif /* MODELS_NFA_H_ */
