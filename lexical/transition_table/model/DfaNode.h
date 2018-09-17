//
// Created by programajor on 3/21/18.
//

#ifndef COMPILERS_DFANODE_H
#define COMPILERS_DFANODE_H

using namespace std;
#include "../../lexical_analyzer_generator/models/Node.h"
#include "../../lexical_analyzer_generator/minimizer/DfaMinimizer.h"

class PartitionSet;
class DfaEdge;
class DfaNode {
private:
    string name;
    string printingName;
    vector<DfaEdge *> edges;
    bool acceptedState;
    PartitionSet * parentSet;
    bool start;
public:
    bool isAcceptedState();
    void setAcceptState(bool accept);

    bool isStart();
    void setStart(bool isStart);

    void setParentSet(PartitionSet * parentSet);
    PartitionSet *getParentSet();

    string getName();
    void setName(string name);

    string getPrintingName();
    void sePrintingtName(string printingName);

    vector<DfaEdge *> getEdges();
    void addEdge(DfaEdge * e);

    DfaNode(string stateName, bool accept);

    bool valid_transition(char c);
    DfaNode* do_transition(char c);
    ~DfaNode();
    vector<DfaEdge *> *getRealEdges();
};

#endif //COMPILERS_DFANODE_H
