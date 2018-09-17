//
// Created by programajor on 3/16/18.
//

#ifndef COMPILERS_DFAMINIMIZER_H
#define COMPILERS_DFAMINIMIZER_H

#include <vector>
#include <string.h>
#include <utility>
#include "../../transition_table/model/DfaNode.h"


class DfaNode;
class PartitionSet {
	private:
		vector<DfaNode*> elements;
		int number;
		bool finished;
	public:
		vector<DfaNode*> getElements();
		int getNumber();
		bool isFinished();
		void setFinished(bool finish);
		void setNumber(int number);
		PartitionSet(int number);
		bool nodeExists(DfaNode *ele);
		void removeEle(DfaNode *ele);
		void addEle(DfaNode *ele);
};

class DfaMinimizer {

	private:
	    vector<DfaNode*> eles;
		vector<PartitionSet*> partitionSets;
		vector<PartitionSet*>  getSet();
		void addSet(PartitionSet* clo);
		bool removeSet(PartitionSet* clo);
		bool checkSameTrans(DfaNode* ele1, DfaNode* ele2);
		void initSets(DfaNode *nonMinimizedDfa, PartitionSet *setS, vector<PartitionSet *> *setF, vector<string> * priority);
		int getNumOfUnfinishedSet();
		int getNumByNode(DfaNode* node);
		pair<int, DfaNode*> getNodeWithNum(DfaNode *node);
		bool nodeExists(DfaNode *node);
    public:
        /**
         * takes non minimized DFA from the converter and return it minimized.
         * @param nonMinimizedDFA the non minimized DFA from the converter
         * @return a minimized DFA from the given non minimized one.
         */
		void getMinimizedDFA(vector<DfaNode*> * finalMachine, DfaNode *nonMinimizedDFA, vector<string> *priority);

};



#endif //COMPILERS_DFAMINIMIZER_H
