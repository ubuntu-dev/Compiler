/*
 * FirstCalculator.cpp
 *
 *  Created on: Apr 18, 2018
 *      Author: amrnasr
 */

#include "FirstCalculator.h"
#include "../models/FirstElementWrapper.h"
#include "../models/FirstExpressionWrapper.h"
#include <unordered_map>
#include <iostream>

void FirstCalculator::set_first_sets(vector<GrammarElement *> *rules , unordered_set<GrammarExpression *> * expressions){
	unordered_map<NonTerminal *, FirstElementWrapper *> eleWrappers;
	unordered_map<GrammarExpression *, FirstExpressionWrapper *> expWrappers;
	vector<FirstElementWrapper *> createdEleWrappers;
	vector<FirstExpressionWrapper *> createdExpWrappers;
	for (unsigned i = 0; i < rules->size(); i++) {
		if ((*rules)[i]->getType() == NON_TERMINAL) {
			FirstElementWrapper *wrapper = new FirstElementWrapper();
			NonTerminal * e = static_cast<NonTerminal *>((*rules)[i]);
			e->first_strings.clear();
			wrapper->core = e;
			eleWrappers.insert(pair<NonTerminal *, FirstElementWrapper *>(e, wrapper));
			createdEleWrappers.push_back(wrapper);
		}
	}
	for (auto it = expressions->begin(); it != expressions->end(); it++) {
		FirstExpressionWrapper *wrapper = new FirstExpressionWrapper();
		(*it)->first_strings.clear();
		wrapper->core = (*it);
		expWrappers.insert(pair<GrammarExpression *, FirstExpressionWrapper *>(*it, wrapper));
		createdExpWrappers.push_back(wrapper);
	}
	bool still_working = true, found_terminal = false;
	while(still_working) {
		still_working = false;
		found_terminal = false;
		for (auto it = createdExpWrappers.begin(); it != createdExpWrappers.end(); it++) {
			FirstExpressionWrapper * wrapper = *it;
			FirstElementWrapper * parent = eleWrappers[static_cast<NonTerminal*>(wrapper->core->belongs_to)];
			for (unsigned i = 0; i < wrapper->core->expression.size(); i++) {
				GrammarElement * e = wrapper->core->expression[i];
				if (e->getType() == TERMINAL) {
					wrapper->first_strings.insert(e->getName());
					parent->first_strings.insert(e->getName());
					found_terminal = true;
					break;
				} else {
					NonTerminal * ex = static_cast<NonTerminal *>(e);
					if (ex != parent->core) {
						FirstElementWrapper * temp = eleWrappers[ex];
						wrapper->first_elements.insert(temp);
						parent->first_elements.insert(temp);
					}
					if (!ex->eps) {
						found_terminal = true;
						break;
					}
				}
			}
			if (!found_terminal) {
				still_working = true;
				wrapper->core->eps = true;
				static_cast<NonTerminal*>(wrapper->core->belongs_to)->eps = true;
			}
		}
		for (auto it = createdEleWrappers.begin(); it != createdEleWrappers.end(); it++) {
			FirstElementWrapper * wrapper = *it;
			for (auto itr = wrapper->first_elements.begin(); itr != wrapper->first_elements.end(); itr++) {
				FirstElementWrapper * wrp = *itr;
				for (auto itra = wrp->first_strings.begin(); itra != wrp->first_strings.end(); itra++) {
					still_working = still_working || wrapper->first_strings.insert((*itra)).second;
				}
			}
			wrapper->first_elements.clear();
		}
		for (auto it = createdExpWrappers.begin(); it != createdExpWrappers.end(); it++) {
			FirstExpressionWrapper * wrapper = *it;
			for (auto itr = wrapper->first_elements.begin(); itr != wrapper->first_elements.end(); itr++) {
				FirstElementWrapper * wrp = *itr;
				for (auto itra = wrp->first_strings.begin(); itra != wrp->first_strings.end(); itra++) {
					still_working = still_working || wrapper->first_strings.insert((*itra)).second;
				}
			}
			wrapper->first_elements.clear();
		}
	}


	// Copy results and delete temporary wrappers.
	for (auto it = createdExpWrappers.begin(); it != createdExpWrappers.end(); it++) {
		FirstExpressionWrapper * wrapper = *it;
		wrapper->core->first_strings.insert(wrapper->first_strings.begin(), wrapper->first_strings.end());
		delete wrapper;
	}
	for (auto it = createdEleWrappers.begin(); it != createdEleWrappers.end(); it++) {
		FirstElementWrapper * wrapper = *it;
		wrapper->core->first_strings.insert(wrapper->first_strings.begin(), wrapper->first_strings.end());
		delete wrapper;
	}
}
