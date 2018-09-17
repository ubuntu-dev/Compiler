//
// Created by programajor on 3/21/18.
//

#include "DfaNodeWrapper.h"

DfaNode * DfaNodeWrapper::getDfaNode() {
    return this->node;
}

void DfaNodeWrapper::setNfaEdges(vector<Edge *> *edges) {
    this->nfaEdges = *edges;
}

vector<Edge *> DfaNodeWrapper::getNfaEdges() {
    return this->nfaEdges;
}

void DfaNodeWrapper::addDfaEdge(DfaEdge *edge) {
    this->node->addEdge(edge);
}

void DfaNodeWrapper::setSupportingNfaNodes(set<Node *> *nodes) {
    this->supportingNodes = *nodes;
}

set<Node *> DfaNodeWrapper::getSupportedNfaNodes() {
    return this->supportingNodes;
}

void DfaNodeWrapper::setDfaNode(DfaNode *dfaNode) {
    this->node = dfaNode;
}

void DfaNodeWrapper::setStart(bool isStart) {
    this->node->setStart(isStart);
}
