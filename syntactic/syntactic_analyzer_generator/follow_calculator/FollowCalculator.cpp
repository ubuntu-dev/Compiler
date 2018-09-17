/*
 * FollowCalculator.cpp
 *
 *  Created on: Apr 18, 2018
 *      Author: amrnasr
 */

#include "FollowCalculator.h"
#include "../models/NonTerminal.h"
#include "../models/FollowElementWrapper.h"
#include <unordered_map>
#include <vector>

void FollowCalculator::set_follow_sets(vector<GrammarElement *> *rules , unordered_set<GrammarExpression *> * expressions) {
	unordered_map<NonTerminal *, FollowElementWrapper *> eleWrappers;
	vector<FollowElementWrapper *> createdEleWrappers;
	for (unsigned i = 0; i < rules->size(); i++) {
		if ((*rules)[i]->getType() == NON_TERMINAL) {
			FollowElementWrapper *wrapper = new FollowElementWrapper();
			NonTerminal * e = static_cast<NonTerminal *>((*rules)[i]);
			e->follow_strings.clear();
			wrapper->core = e;
			eleWrappers.insert(pair<NonTerminal *, FollowElementWrapper *>(e, wrapper));
			createdEleWrappers.push_back(wrapper);
		}
	}
	if (createdEleWrappers.size() == 0) {
		return;
	}
	createdEleWrappers.at(0)->follow_strings.insert("$");
	bool still_working = true, found = false;
	while(still_working) {
		still_working = false;
		for (auto it = createdEleWrappers.begin(); it != createdEleWrappers.end(); it++) {
			FollowElementWrapper * wrapper = *it;
			for (unsigned i = 0; i < wrapper->core->referenced_in.size(); i++) {
				GrammarExpression * exp = wrapper->core->referenced_in[i];
				FollowElementWrapper *big = eleWrappers[static_cast<NonTerminal *>(exp->belongs_to)];
				found  = false;
				for (unsigned j = 0; j < exp->expression.size(); j++) {
					GrammarElement *e = exp->expression[j];
					if (found) {
						if (e->getType() == TERMINAL) {
							wrapper->follow_strings.insert(e->getName());
							found = false;
						} else {
							NonTerminal * ex = static_cast<NonTerminal *>(e);
							wrapper->follow_strings.insert(ex->first_strings.begin(), ex->first_strings.end());
							if (!ex->eps && ex != wrapper->core) {
								found = false;
							}
						}
					} else if (e->getType() == NON_TERMINAL) {
						found = wrapper->core == static_cast<NonTerminal *>(e);
					}
				}
				if (found) {
					wrapper->follow_elements.insert(big);
				}
			}
		}
		for (auto it = createdEleWrappers.begin(); it != createdEleWrappers.end(); it++) {
			FollowElementWrapper * wrapper = *it;
			for (auto itr = wrapper->follow_elements.begin(); itr != wrapper->follow_elements.end(); itr++) {
				FollowElementWrapper * wrp = *itr;
				for (auto itra = wrp->follow_strings.begin(); itra != wrp->follow_strings.end(); itra++) {
					still_working = still_working || wrapper->follow_strings.insert((*itra)).second;
				}
			}
			wrapper->follow_elements.clear();
		}
	}
	for (auto it = createdEleWrappers.begin(); it != createdEleWrappers.end(); it++) {
		FollowElementWrapper * wrapper = *it;
		wrapper->core->follow_strings.insert(wrapper->follow_strings.begin(), wrapper->follow_strings.end());
		delete wrapper;
	}

}
