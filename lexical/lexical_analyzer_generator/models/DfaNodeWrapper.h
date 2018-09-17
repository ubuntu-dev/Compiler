//
// Created by programajor on 3/21/18.
//

#ifndef COMPILERS_NODEWRAPPER_H
#define COMPILERS_NODEWRAPPER_H


#include "Edge.h"
#include "../../transition_table/model/DfaNode.h"

class DfaNodeWrapper {
private:
    vector<Edge*> nfaEdges;
    DfaNode* node;
    set<Node *> supportingNodes;

public:
    void setNfaEdges(vector <Edge*> *edges);
    vector <Edge*> getNfaEdges();

    void addDfaEdge(DfaEdge* edge);

    void setDfaNode(DfaNode* dfaNode);
    DfaNode* getDfaNode();

    void setSupportingNfaNodes(set<Node *> *nodes);
    set<Node*> getSupportedNfaNodes();

    void setStart(bool isStart);
};


#endif //COMPILERS_NODEWRAPPER_H
