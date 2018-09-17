//
// Created by programajor on 3/16/18.
//

#include "Node.h"
#include <list>
#include <unordered_set>

bool Node::isAcceptedState() {
	return this->acceptedState;
}

string Node::getName() {
	return this->name;
}

void Node::setName(string name) {
	this->name = name;
}

vector<Edge *> Node::getEdges() {
	return this->edges;
}


void Node::addEdge(Edge * e) {
	this->edges.push_back(e);
}

Node::Node(string stateName, bool accept) {
	this->acceptedState = accept;
	this->name = stateName;
}


Node::Node(bool accept) {
	this->acceptedState = accept;
}

void Node::setAcceptState(bool newState) {
	this->acceptedState = newState;
}

void Node::delete_graph(Node * node) {
	list<Node *> queue;
	unordered_set<Node *> deletedNodes;
	queue.push_back(node);
	deletedNodes.emplace(node);
	while (!queue.empty()) {
		Node * temp = queue.front();
		queue.pop_front();
		for (unsigned i = 0; i < temp->edges.size(); i++) {
			Node * target = temp->edges[i]->get_target_node();
			if (deletedNodes.find(target) == deletedNodes.end()) {
				queue.push_back(target);
				deletedNodes.emplace(target);
			}
			delete temp->edges[i];
		}
		delete temp;
	}
}
