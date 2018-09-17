/*
 * NodeTest.cpp
 *
 *  Created on: Mar 19, 2018
 *      Author: amrnasr
 */
#include "../../../test_headers/p1_tests.h"
#include "Edge.h"
#include <iostream>
#include "Node.h"
#include <string>

using namespace std;

void test_node(void) {
	Node a("a", true);
	Node b("b", false);
	bool error = false;
	// Name Test
	if (a.getName() != "a") {
		cout << "Invalid name..." << endl;
		error = true;
	}
	if (b.getName() != "b") {
		cout << "Invalid name..." << endl;
		error = true;
	}
	// Acceptance test
	if (!a.isAcceptedState()) {
		cout << "Invalid acceptance state..." << endl;
		error = true;
	}
	if (b.isAcceptedState()) {
		cout << "Invalid acceptance state..." << endl;
		error = true;
	}
	// Add and get edges.
	Edge e('a','a', &a);
	b.addEdge(&e);
	if (b.getEdges().empty()) {
		cout << "Edge not added..." << endl;
		error = true;
	}
	if (b.getEdges().at(0)->do_transition('a') != &a) {
		cout << "Bad Edge..." << endl;
		error = true;
	}
	if (!error) {
		cout << "Node Success..." << endl;
	}
}



