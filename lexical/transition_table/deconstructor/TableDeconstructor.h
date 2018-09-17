//
// Created by programajor on 3/23/18.
//

#ifndef COMPILERS_TABLEDECONSTRUCTOR_H
#define COMPILERS_TABLEDECONSTRUCTOR_H


#include "../model/DfaNode.h"
#include "../model/TransitionTable.h"

class TableDeconstructor {
public:
    vector<DfaNode *> deconstructGraph(TransitionTable table);
};


#endif //COMPILERS_TABLEDECONSTRUCTOR_H
