//
// Created by programajor on 3/16/18.
//

#ifndef COMPILERS_NFACOMBINER_H
#define COMPILERS_NFACOMBINER_H


#include "../models/Node.h"
#include "../models/Nfa.h"
#include <vector>

using namespace std;

class NFACombiner {
    public:

        /**
         * takes separated NFAs from the builder and combines them into one NFA.
         * @param separatedStateAcceptors the separated NFAs from the builder
         * @return a combined NFA for all the separated NFAs.
         */
        Node *getCombinedNfa(vector<Nfa *> *separatedStateAcceptors);
};


#endif //COMPILERS_NFACOMBINER_H
