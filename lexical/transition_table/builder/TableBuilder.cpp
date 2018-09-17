//
// Created by programajor on 3/23/18.
//

#include <algorithm>
#include "TableBuilder.h"
#include <iostream>

TransitionTable TableBuilder::buildTransitionTable(vector<DfaNode *> nodes, set<char> *alphabets) {
    DfaNode* phi = new DfaNode("Phi", false);
    phi->sePrintingtName("Phi");
    nodes.push_back(phi);
    vector<vector<DfaNode*>> transitions (nodes.size());
    for (auto j = alphabets->begin(); j != alphabets->end(); ++j) {
    	transitions[transitions.size() - 1].push_back(phi); // under any input phi goes to itself
    }
    for (unsigned i = 0; i < transitions.size() - 1; i++) {
        for (auto j = alphabets->begin(); j != alphabets->end(); j++) {
            char input = (*j);
            if (nodes[i]->valid_transition(input)) {
            	DfaNode * target = nodes[i]->do_transition(input);
            	transitions[i].push_back(target);
            } else {
                transitions[i].push_back(phi);
            }
        }
    }

    vector<string> newInputs;
    vector<vector<DfaNode*>> newTransitions (nodes.size());
    minimizeTable(&transitions, alphabets, &newInputs, &newTransitions);
    return TransitionTable(nodes, newInputs, newTransitions);
}

void TableBuilder::minimizeTable(vector<vector<DfaNode *>> *transtions, set<char> *alphabets,
                                 vector<string> *newInputs, vector<vector<DfaNode *>> *newTransitions) {
    bool depend = false;
    unsigned i_num = 0;
    for (auto i = alphabets->begin(); i != alphabets->end(); i++) {
    	depend = true;
    	char a = (*i);
    	auto j = i;
    	j++;
    	char b;
    	unsigned j_num = i_num + 1;
    	while (depend && j != alphabets->end()) {
    		b = (*j);
    		if (a + (int)(j_num - i_num) != b) {
    			depend = false;
    		} else {
    			for (unsigned k = 0; k < transtions->size(); k++) {
    				if ((*transtions)[k][i_num] != (*transtions)[k][j_num]) {
    					depend = false;
    					break;
    				}
    			}
    		}
    		j_num++;
    		j++;
    	}
    	if (j != alphabets->end()) {
    		j--;
    		j--;
			j_num -= 2;
    	} else {
    		if (depend) {
    			j--;
    			j_num--;
    		} else {
    			j--;
				j--;
				j_num -= 2;
    		}
    	}
    	b = (*j);
    	string newStr = string() + a + "-" + b;
    	newInputs->push_back(newStr);
    	for (unsigned k = 0; k < transtions->size(); k++) {
			(*newTransitions)[k].push_back((*transtions)[k][i_num]);
		}
    	i_num = j_num;
    	i = j;
    	i_num++;
    }
}
