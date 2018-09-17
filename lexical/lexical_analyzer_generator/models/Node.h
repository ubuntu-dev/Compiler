//
// Created by programajor on 3/16/18.
//

#ifndef COMPILERS_NODE_H
#define COMPILERS_NODE_H

#include <string>
#include <vector>
#include <set>
#include "Edge.h"

#define ACCEPT_STATE true
#define EPS '\0'

using namespace std;
class Edge;
class Node {
    private:
        string name;
        vector<Edge *> edges;
        bool acceptedState;
 	public:
		// constructors
		explicit Node(bool accept);
		Node(string stateName, bool accept);
    	// end of constructors
		bool isAcceptedState();
    	void setAcceptState(bool newState);
    	string getName();
    	void setName(string name);
    	vector<Edge *> getEdges();
    	void addEdge(Edge * e);
		static void delete_graph(Node * node);
};


#endif //COMPILERS_NODE_H
