//
// Created by programajor on 3/16/18.
//

#include <set>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
#include <climits>
#include <unordered_set>
#include "NfaDfaConverter.h"
#include <iostream>
#include "../models/DfaNodeWrapper.h"


using namespace std;



DfaNode * NfaDfaConverter::getNonMinimizedDFA(Node *combinedNfa, vector<string> *priorities, set<char> *alphabet) {
	this->stateNameCounter = 1;
	unordered_map<Node *, set<Node *>> prev_found;
	DfaNodeWrapper* start = getDfaStartState(combinedNfa, priorities, &prev_found);

	start->setStart(true);

    set<DfaNodeWrapper*> dfaNodes;
    queue<DfaNodeWrapper*> nonMarkedNodes;

    dfaNodes.insert(start);
    nonMarkedNodes.push(start);
    while (!nonMarkedNodes.empty()) {
        DfaNodeWrapper* node = nonMarkedNodes.front();
        nonMarkedNodes.pop();

        // for every input symbol
        for (auto cur_in = alphabet->begin(); cur_in != alphabet->end(); cur_in++) {
			char cur = (*cur_in);
			set<Node*> nextStates;
			vector<Edge *> tempEdges = node->getNfaEdges();
			char end_c = cur;
        	for (unsigned i = 0; i < tempEdges.size(); i++) {
				Edge * e = tempEdges[i];
        		if (e->is_eps_transition()) {
					continue;
				}
				if (e->valid_transition(cur) && nextStates.find(e->do_transition(cur)) == nextStates.end()) {
					nextStates.insert(e->do_transition(cur));
				}
			}
        	if (nextStates.empty()) {
        		continue;
        	}
        	set<Node*> modifiedState = nextStates;
        	while(nextStates == modifiedState && end_c >= cur) {
        		end_c++;
        		modifiedState.clear();
        		for (unsigned i = 0; i < tempEdges.size(); i++) {
					Edge * e = tempEdges[i];
					if (e->is_eps_transition()) {
						continue;
					}
					if (e->valid_transition(end_c) && modifiedState.find(e->do_transition(end_c)) == modifiedState.end()) {
						modifiedState.insert(e->do_transition(end_c));
					}
				}
        	}
        	end_c--;
        	DfaNodeWrapper* newDfaNode = getEpslonClosureFromSet(&nextStates, priorities, &prev_found);
			DfaNodeWrapper* dfaRepresenter = setContainsState(&dfaNodes, newDfaNode);
			if (dfaRepresenter == NULL) {
				dfaNodes.insert(newDfaNode);
				nonMarkedNodes.push(newDfaNode);
				DfaEdge *edge = new DfaEdge(cur, end_c, node->getDfaNode(), newDfaNode->getDfaNode());
				node->addDfaEdge(edge);
			} else {
				delete newDfaNode;
				DfaEdge *edge = new DfaEdge(cur, end_c, node->getDfaNode(), dfaRepresenter->getDfaNode());
				node->addDfaEdge(edge);
			}
        }
    }
    unordered_set <DfaNode*> visited;
    removeRedundantEdges(start->getDfaNode(), &visited);
    DfaNode * res = start->getDfaNode();
    std::set<DfaNodeWrapper *>::iterator it;
	for (it = dfaNodes.begin(); it != dfaNodes.end(); it++) {
		delete (*it);
	}

	Node::delete_graph(combinedNfa);

    return res;
}

DfaNodeWrapper* NfaDfaConverter::getDfaStartState(Node *combinedNfa, vector<string> *priorities, unordered_map<Node *, set<Node *>> *prev_found) {
    set<Node *> nodes;
    nodes.insert(combinedNfa);
    return getEpslonClosureFromSet(&nodes, priorities, prev_found);
}

DfaNodeWrapper* NfaDfaConverter::getEpslonClosureFromSet(set<Node *> *states, vector<string> *priorities, unordered_map<Node *, set<Node *>> *prev_found) {
    set<Node*> initials;
    std::set<Node *>::iterator it;
    for (it = states->begin(); it != states->end(); it++) {
        Node* node = *it;
        set<Node*> s;
        getEpslonClosure(&s, node, prev_found);
        std::set<Node *>::iterator iter;
        for (iter = s.begin(); iter != s.end(); iter++) {
            initials.insert(*iter);
        }
    }

    bool isAccepted = getIsAccepted(&initials);
    string stateName = getStateName(&initials, priorities);
    vector<Edge *> edges;
    getEdges(&edges, &initials);

    DfaNodeWrapper* wrapper = new DfaNodeWrapper();
    DfaNode* dfaNode = new DfaNode(stateName, isAccepted);
    wrapper->setDfaNode(dfaNode);
    wrapper->setNfaEdges(&edges);
    wrapper->setSupportingNfaNodes(&initials);
    return wrapper;
}

void NfaDfaConverter::getEpslonClosure(set<Node*> * closure, Node *node, unordered_map<Node *, set<Node *>> *prev_found) {
    if (prev_found->find(node) != prev_found->end()) {
    	*closure = prev_found->find(node)->second;
    }
	closure->insert(node);
    vector<Edge *> newEdges;
    stack<Node*> stack;
    stack.push(node);
    for (unsigned i = 0; i < node->getEdges().size(); i++) {
        if (!isFound(&newEdges, node->getEdges()[i])) {
            newEdges.push_back(node->getEdges()[i]);
        }
    }
    while (!stack.empty()) {
        Node* temp = stack.top();
        stack.pop();
        for (unsigned i = 0; i < temp->getEdges().size(); i++) {
            Edge* e = temp->getEdges()[i];
            if (e->is_eps_transition()) {
                Node *newState = e->do_transition('\0');
                closure->insert(newState);
                for (unsigned j = 0; j < newState->getEdges().size(); j++) {
                    if (!isFound(&newEdges, newState->getEdges()[j])) {
                        newEdges.push_back(newState->getEdges()[j]);
                    }
                }
                stack.push(newState);
            }
        }
    }
    prev_found->insert(make_pair(node, *closure));
}

bool NfaDfaConverter::getIsAccepted(set<Node *> *states) {
    bool isAccepted = false;
    std::set<Node *>::iterator it;
    for (it = states->begin(); it != states->end(); it++) {
        Node* node = *it;
        isAccepted |= node->isAcceptedState();
    }
    return isAccepted;
}

string NfaDfaConverter::getStateName(set<Node *> *states, vector<string> *priorities) {
    unsigned priority = INT_MAX;
    string name = "";
    std::set<Node *>::iterator it;
    for (it = states->begin(); it != states->end(); it++) {
        Node* node = *it;
        if (node->isAcceptedState()) {
            for (unsigned i = 0; i < priorities->size(); i++) {
                if (node->getName() == (*priorities)[i] && i < priority) {
                    priority = i;
                    name = node->getName();
                }
            }
        }
    }
    if (name == "") {
        name = to_string(stateNameCounter) + "";
        stateNameCounter++;
    }
    return name;
}

void NfaDfaConverter::getEdges(vector<Edge *> * edges, set<Node *> * states) {
    std::set<Node *>::iterator it;
    for (it = states->begin(); it != states->end(); it++) {
        Node* node = *it;
        for (unsigned i = 0; i < node->getEdges().size(); i++) {
            edges->push_back(node->getEdges()[i]);
        }
    }
}

DfaNodeWrapper* NfaDfaConverter::setContainsState(set<DfaNodeWrapper *> * states, DfaNodeWrapper *node) {
    std::set<DfaNodeWrapper *>::iterator it;
    for (it = states->begin(); it != states->end(); it++) {
        DfaNodeWrapper* curr = *it;
        if (representingSameNfa(node, curr)) {
            return curr;
        }
    }
    return NULL;
}

bool NfaDfaConverter::representingSameNfa(DfaNodeWrapper *n1, DfaNodeWrapper *n2) {
    set<Node*> s1 = n1->getSupportedNfaNodes();
    set<Node*> s2 = n2->getSupportedNfaNodes();

    if (s1.size() != s2.size()) {
        return false;
    }

    std::set<Node *>::iterator it;
    for (it = s1.begin(); it != s1.end(); it++) {
        Node* curr = *it;
        if (s2.find(curr) == s2.end()) {
            return false;
        }
    }
    return true;
}

bool NfaDfaConverter::isFound(vector<Edge *> *vector, Edge *&edge) {
    for (unsigned i = 0; i < vector->size(); ++i) {
        Edge* e = (*vector)[i];
        if (e->get_target_node() == edge->get_target_node() &&
                e->get_first_allowed_char() == edge->get_first_allowed_char() &&
                e->get_last_allowed_char() == edge->get_last_allowed_char()) {
            return true;
        }
    }
    return false;
}

void NfaDfaConverter::removeRedundantEdges(DfaNode *node, unordered_set<DfaNode *> *visited) {
    for (unsigned i = 0; i < node->getEdges().size(); i++) {
        DfaEdge* edge = node->getEdges()[i];
        for (unsigned j = i + 1; j < node->getEdges().size(); j++) {
            DfaEdge* curr = node->getEdges()[j];
            if (edge->get_allowing_range() < curr->get_allowing_range()) {
				curr->disallow_character_sequence(edge->get_first_allowed_char(),
					  edge->get_last_allowed_char());
            } else {
            	edge->disallow_character_sequence(curr->get_first_allowed_char(),
            						  curr->get_last_allowed_char());
            }
        }
    }
    visited->insert(node);
    for (unsigned i = 0; i < node->getEdges().size(); i++) {
        DfaEdge* edge = node->getEdges()[i];
        DfaNode* next = edge->get_target_node();
        if (node != next) {
        	if (visited->find(next) == visited->end()) {
        		removeRedundantEdges(next, visited);
        	}
            edge->set_target_node(next);
        }
    }
}

