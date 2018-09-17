//
// Created by programajor on 3/23/18.
//

#ifndef COMPILERS_TRANSOTIONTABLE_H
#define COMPILERS_TRANSOTIONTABLE_H


#include "../model/DfaNode.h"

class TransitionTable {
private:
    vector<DfaNode *> nodes;
    vector<string> inputs;
    vector<vector<DfaNode*>> transitions;

public:
    TransitionTable(vector<DfaNode *> nodes, vector<string> inputs,
                                            vector<vector<DfaNode *>> transitions);
    vector<DfaNode *> getNodes();
    vector<string> getInputs();
    vector<vector<DfaNode*>> getTransitions();
};


#endif //COMPILERS_TRANSOTIONTABLE_H
