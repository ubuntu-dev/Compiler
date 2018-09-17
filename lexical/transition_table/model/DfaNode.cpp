//
// Created by programajor on 3/21/18.
//

#include "DfaNode.h"
#include "DfaEdge.h"

bool DfaNode::isAcceptedState() {
    return this->acceptedState;
}
void DfaNode::setParentSet(PartitionSet* parentSet) {
	this->parentSet = parentSet;
}

PartitionSet *DfaNode::getParentSet() {
	return this->parentSet;
}

DfaNode :: DfaNode(string stateName, bool accept) {
	this->acceptedState = accept;
	this->name = stateName;
    this->start = false;
}

string DfaNode::getName() {
    return this->name;
}

void DfaNode::setName(string name) {
    this->name = name;
}

vector<DfaEdge *> DfaNode::getEdges() {
    return this->edges;
}

void DfaNode::addEdge(DfaEdge *e) {
    this->edges.push_back(e);
}

bool DfaNode::isStart() {
    return this->start;
}

void DfaNode::setStart(bool isStart) {
    this->start = isStart;
}

bool DfaNode::valid_transition(char c) {
    for (unsigned i = 0; i < edges.size(); i++) {
        DfaEdge* e = edges[i];
        if (e->valid_transition(c)) {
            return true;
        }
    }
    return false;
}

DfaNode *DfaNode::do_transition(char c) {
    for (unsigned i = 0; i < edges.size(); i++) {
        DfaEdge* e = edges[i];
        DfaNode* destination = e->do_transition(c);
        if (destination != nullptr) {
            return destination;
        }
    }
    return nullptr;
}
DfaNode::~DfaNode() {
	for (unsigned i = 0; i < this->edges.size(); i++) {
		delete this->edges[i];
	}
}

string DfaNode::getPrintingName() {
    return this->printingName;
}

void DfaNode::sePrintingtName(string printingName) {
    this->printingName = printingName;
}

vector<DfaEdge *> *DfaNode::getRealEdges() {
	return &this->edges;
}

void DfaNode::setAcceptState(bool accept) {
    this->acceptedState = accept;
}
