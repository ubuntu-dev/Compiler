//
// Created by programajor on 3/16/18.
//

#ifndef COMPILERS_NFADFACONVERTER_H
#define COMPILERS_NFADFACONVERTER_H

#include "../models/Node.h"
#include "../../transition_table/model/DfaEdge.h"
#include "../models/DfaNodeWrapper.h"
#include <unordered_set>
#include <unordered_map>

class NfaDfaConverter {

    public:
        /**
         * takes combined NFA from the combiner and converts it to a non minimized DFA.
         * @param combinedNfa the combined NFA from the combiner
         * @return a non minimized DFA from the given NFA.
         */
        DfaNode * getNonMinimizedDFA(Node *combinedNfa, vector<string> *priorities, set<char> * alphabet);

private:
    int stateNameCounter;
    void getEpslonClosure(set<Node*> * nodeSet, Node *node, unordered_map<Node *, set<Node *>> *prev_found);

    string getStateName(set<Node *> *states, vector<string> *priorities);

    bool getIsAccepted(set<Node *> *states);

    void getEdges(vector<Edge *> *edgeSet, set<Node *> *states);

    DfaNodeWrapper * getDfaStartState(Node *combinedNfa, vector<string> *priorities, unordered_map<Node *, set<Node *>> *prev_found);

    DfaNodeWrapper * getEpslonClosureFromSet(set<Node *> *states, vector<string> *priorities, unordered_map<Node *, set<Node *>> *prev_found);

    DfaNodeWrapper* setContainsState(set<DfaNodeWrapper *> *states, DfaNodeWrapper *node);

    bool representingSameNfa(DfaNodeWrapper *n1, DfaNodeWrapper *n2);

    bool isFound(vector<Edge *> *vector, Edge *&edge);

    void removeRedundantEdges(DfaNode *node, unordered_set<DfaNode *> * visited);
};


#endif //COMPILERS_NFADFACONVERTER_H
