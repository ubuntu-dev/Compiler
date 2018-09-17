//
// Created by programajor on 3/23/18.
//

#ifndef COMPILERS_TABLEBUILDER_H
#define COMPILERS_TABLEBUILDER_H

#include "../model/TransitionTable.h"
#include "../model/DfaNode.h"

class TableBuilder {
public:
    TransitionTable buildTransitionTable(vector<DfaNode *> nodes, set <char> *alphabets);

    void minimizeTable(vector<vector<DfaNode *>> *nodes, set<char> *alphabets, vector<string> *pVector,
                           vector<vector<DfaNode *>> *pVector1);

    string mergeInputs(string s1, string s2);
};


#endif //COMPILERS_TABLEBUILDER_H
