//
// Created by programajor on 3/16/18.
//

#include "DfaMinimizer.h"
#include "../../transition_table/model/DfaNode.h"
#include <vector>
#include "../../transition_table/model/DfaEdge.h"
#include <utility>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <map>
#include <iterator>
#include <queue>
#include <string>
#include <unordered_set>

void sort_node_edges(DfaNode * node);
bool compare_dfa_edge(DfaEdge *a, DfaEdge *b) {
	if (a->get_first_allowed_char() < b->get_first_allowed_char()) {
		return true;
	} else if (a->get_first_allowed_char() == b->get_first_allowed_char()) {
		if (a->get_last_allowed_char() < b->get_last_allowed_char()) {
			return true;
		} else if (a->get_last_allowed_char() == b->get_last_allowed_char()) {
			return a->get_disallowed_chars().size() <= b->get_disallowed_chars().size();
		} else {
			return false;
		}
	} else {
		return false;
	}
}

void sort_node_edges(DfaNode * node) {
	 sort( node->getRealEdges()->begin(), node->getRealEdges()->end(), compare_dfa_edge);
}

vector<DfaNode*> PartitionSet:: getElements() {
	return this->elements;
}

int PartitionSet:: getNumber() {
	return this->number;
}

void PartitionSet :: setNumber(int number) {
	this->number = number;
}

PartitionSet ::PartitionSet(int number) {
	this->number = number;
	this->finished = false;
}

bool PartitionSet :: nodeExists(DfaNode *ele) {
	for (auto it = this->elements.begin(); it != this->elements.end(); it++) {
		  if ((*it) == ele) {
			  return true;
		  }
	}
	return false;
}

void PartitionSet :: removeEle(DfaNode *ele) {
	for (unsigned i = 0; i < this->elements.size(); i++) {
			  if (this->elements[i] == ele) {
				  delete *(this->elements.begin() + i);
				  this->elements.erase(this->elements.begin() +i);
				  return;
			  }
		}

}

void PartitionSet :: addEle(DfaNode *ele) {
	ele->setParentSet(this);
	this->elements.push_back(ele);
}

bool DfaMinimizer ::nodeExists(DfaNode *ele) {
	for (auto it = this->eles.begin(); it != this->eles.end(); it++) {
		  if ((*it) == ele) {
			  return true;
		  }
	}
	return false;
}

void DfaMinimizer :: getMinimizedDFA(vector<DfaNode*> * finalMachine, DfaNode *nonMinimizedDFA, vector<string> *priority) {
	this->eles.clear();
	this->partitionSets.clear();
	queue<DfaNode*> nodes;
	nodes.push(nonMinimizedDFA);
	this->eles.push_back(nonMinimizedDFA);
	// building list of nodes.
	while (!nodes.empty()) {
		DfaNode * node = nodes.front();
		for (unsigned j = 0; j < node->getEdges().size(); ++j) {
			DfaNode * target = node->getEdges()[j]->get_target_node();
			if (!nodeExists(target)) {
				nodes.push(target);
				this->eles.push_back(target);
			}
		}
		sort_node_edges(node);
		nodes.pop();
	}
	int count = 1;
	PartitionSet *setS = new PartitionSet(count++);
	vector<PartitionSet *> setsF;
	for (unsigned i = 0; i < priority->size(); i++) {
		PartitionSet *setF = new PartitionSet(count++);
		this->partitionSets.push_back(setF);
		setsF.push_back(setF);
	}

	this->partitionSets.push_back(setS);
	initSets(nonMinimizedDFA, setS, &setsF, priority);
	int counter = getNumOfUnfinishedSet();
	int max = 1 + priority->size();
	// partitioning into sets.
	while ( counter > 0) {
		while (max > 0) {
			map<string, PartitionSet*> setMap;
			vector<int> flags;
			for (unsigned i = 0;
					i < this->partitionSets[max - 1]->getElements().size(); i++) {
				string key="";
				for (unsigned j = 0;
						j < this->partitionSets[max - 1]->getElements(
								)[i]->getEdges().size(); j++) {
					key += std::to_string(getNumByNode(this->partitionSets[max - 1]->getElements(
								)[i]->getEdges()[j]->get_target_node()));
				}
				map<string,PartitionSet*>::const_iterator it = (setMap.find(key));
				if ( (it) == setMap.end()) {
					PartitionSet *temp = new PartitionSet(
								this->partitionSets[max -1]->getNumber());
					temp->addEle(this->partitionSets[max -1]->getElements()[i]);
					setMap.insert(pair <string , PartitionSet*> (key, temp));
					flags.push_back(1);
				} else {
					(*it).second->addEle(
							this->partitionSets[max -1]->getElements()[i]);

				}

			}
			if (setMap.size() == 1) {
				(*setMap.begin()).second->setFinished(true);
			}
			map <string, PartitionSet*> :: const_iterator itr;
			for (itr = setMap.begin(); itr != setMap.end(); itr++) {
				if ((*itr).second->getElements().size() == 1) {
					(*itr).second->setFinished(true);
				}
				this->addSet((*itr).second);
			}
			setMap.clear();
			this->removeSet(this->partitionSets[max -1]);
			max--;
		}
		for (unsigned i = 0; i < this->partitionSets.size(); i++) {
			this->partitionSets[i]->setNumber(i+1);
		}
		counter = getNumOfUnfinishedSet();
		max = this->partitionSets.size();

	}
	vector<pair<int, DfaNode*>> qTransition;
	pair<int, DfaNode*> pStart = getNodeWithNum(nonMinimizedDFA);
	// reformulation of sets to one node each.
	for (unsigned i = 0; i < this->partitionSets.size(); i++) {
		qTransition.push_back(
		pair<int, DfaNode*> (this->partitionSets[i]->getNumber(),
				this->partitionSets[i]->getElements()[0]));
	}

	for (unsigned i = 0; i < qTransition.size(); i++) {
		for (unsigned  j = 0; j < qTransition[i].second->getEdges().size(); j++) {
			if (getNumByNode(qTransition[i].second->getEdges(
					)[j]->get_target_node()) == qTransition[i].first) {
						qTransition[i].second->getEdges()[j]->set_target_node(
								qTransition[i].second);
			} else {
				int index = getNumByNode(qTransition[i].second->getEdges(
						)[j]->get_target_node()) - 1;
				qTransition[i].second->getEdges()[j]->set_target_node(
						qTransition[index].second);

			}
		}
	}
	// Delete unused nodes.
	for (unsigned i = 0; i < this->partitionSets.size(); i++) {
		for (unsigned j = 1; j < this->partitionSets[i]->getElements().size(); j++) {
			delete this->partitionSets[i]->getElements()[j];
		}
	}
	// making nodes into list and returning it.
	finalMachine->push_back(qTransition[pStart.first - 1].second);
	for (int i = 0; (unsigned)i < qTransition.size(); i++) {
		if ((pStart.first - 1) != i)
			finalMachine->push_back(qTransition[i].second);
	}
}

void DfaMinimizer :: addSet(PartitionSet* clo) {
	this->partitionSets.push_back(clo);
}

bool DfaMinimizer :: removeSet(PartitionSet* clo) {
	for (auto it = this->partitionSets.begin(); it != this->partitionSets.end(); it++) {
				  if ((*it)->getNumber() == clo->getNumber()) {
					  this->partitionSets.erase(it);
					  return true;
				  }
			}
	return false;
}

bool DfaMinimizer :: checkSameTrans(DfaNode* ele1, DfaNode* ele2) {
	if (ele1->getEdges().size() != ele2->getEdges().size()) {
		return false;
	}
	int flag = 0;
	for (unsigned i = 0; i < ele1->getEdges().size(); ++i) {
		if (ele1->getEdges()[i]->equals(ele2->getEdges()[i])) {
			if (getNumByNode(ele1->getEdges()[i]->get_target_node()) !=
					getNumByNode(ele2->getEdges()[i]->get_target_node())) {
				flag = 1;
			}

		}
	}
	if (flag == 1) {
		return false;
	}
	return true;
}

void DfaMinimizer :: initSets(DfaNode *nonMinimizedDfa, PartitionSet *clS, vector<PartitionSet *> *clF, vector<string> * priority) {
	for (auto it = this->eles.begin(); it!= this->eles.end(); ++it) {
		if ((*it)->isAcceptedState()) {
			for (unsigned i = 0; i < priority->size(); i++) {
				if ((*it)->getName() == priority->at(i)) {
					(*clF)[i]->addEle(*it);
				}
			}
		} else {
			clS->addEle(*it);
		}

	}
}

int  DfaMinimizer :: getNumByNode(DfaNode* node) {
	return node->getParentSet()->getNumber();
}

vector<PartitionSet*> DfaMinimizer ::  getSet(){
	return this->partitionSets;
}

int DfaMinimizer::getNumOfUnfinishedSet() {
	int count = 0;
	for (unsigned i = 0; i < this->partitionSets.size(); i++) {
		if (!this->partitionSets[i]->isFinished()) {
			count++;
		}
	}
	return count;
}


bool PartitionSet:: isFinished() {
	return this->finished;
}

void PartitionSet::setFinished(bool finish) {
  this->finished = finish;
}

pair<int, DfaNode*> DfaMinimizer:: getNodeWithNum(DfaNode * node) {
	int temp = getNumByNode(node);
	pair<int, DfaNode*> p(temp, node);
	return p;
}

