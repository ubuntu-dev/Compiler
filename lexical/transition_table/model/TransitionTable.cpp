//
// Created by programajor on 3/23/18.
//

#include "TransitionTable.h"

TransitionTable::TransitionTable(vector<DfaNode *> nodes, vector<string> inputs, vector<vector<DfaNode *>> transitions) {
    this->nodes = nodes;
    this->inputs = inputs;
    this->transitions = transitions;
}

vector<DfaNode *> TransitionTable::getNodes() {
    return this->nodes;
}

vector<string> TransitionTable::getInputs() {
    return this->inputs;
}

vector<vector<DfaNode *>> TransitionTable::getTransitions() {
    return this->transitions;
}
