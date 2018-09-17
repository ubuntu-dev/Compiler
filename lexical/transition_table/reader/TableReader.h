//
// Created by programajor on 3/23/18.
//

#ifndef COMPILERS_TABLEREADER_H
#define COMPILERS_TABLEREADER_H

#include <fstream>
#include "../model/TransitionTable.h"

class TableReader {
public:
    TransitionTable * readTransitionTable(ifstream* stream);

    DfaNode *getNodeFromPrintingName(string name, vector<DfaNode *> nodes);
};


#endif //COMPILERS_TABLEREADER_H
