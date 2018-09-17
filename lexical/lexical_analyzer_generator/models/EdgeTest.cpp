/*
 * EdgeTest.cpp
 *
 *  Created on: Mar 19, 2018
 *      Author: amrnasr
 */

#include "Edge.h"
#include <iostream>
#include "../../../test_headers/p1_tests.h"

using namespace std;

void test_edge(void) {
	// Test 1 : basic edge functions.
	Edge e('a','z',NULL);
	bool error = false;
	if (!e.valid_transition('a')) {
		cout << "valid transition wrong result..." << endl;
		error = true;
	}
	if (!e.valid_transition('z')) {
		cout << "valid transition wrong result..." << endl;
		error = true;
	}
	if (e.valid_transition('A')) {
		cout << "valid transition wrong result..." << endl;
		error = true;
	}
	if (!e.valid_transition('f')) {
		cout << "valid transition wrong result..." << endl;
		error = true;
	}
	if (e.getAllowedRange() != 26) {
		cout << "Wrong count of range..." << endl;
		error = true;
	}
	e.disallow_character('f');
	if (e.getAllowedRange() != 25) {
		cout << "Wrong count of range..." << endl;
		error = true;
	}
	if (e.valid_transition('f')) {
		cout << "valid transition wrong result..." << endl;
		error = true;
	}
	e.disallow_character('a');
	if (e.valid_transition('f')) {
		cout << "valid transition wrong result..." << endl;
		error = true;
	}
	if (e.valid_transition('a')) {
		cout << "valid transition wrong result..." << endl;
		error = true;
	}
	if (!e.valid_transition('z')) {
		cout << "valid transition wrong result..." << endl;
		error = true;
	}
	if (e.is_eps_transition()) {
		cout << "Not epsilon transition wrong result..." << endl;
		error = true;
	}
	if (e.getAllowedRange() != 24) {
		cout << "Wrong count of range..." << endl;
		error = true;
	}
	// Test 2 : edge transitions and epsilon edge.
	Node a("a", true);
	Edge x('\0','\0', &a);
	if (!x.is_eps_transition()) {
		cout << "epsilon transition wrong result..." << endl;
		error = true;
	}
	if (x.valid_transition('a')) {
		cout << "valid transition wrong result..." << endl;
		error = true;
	}
	if (x.do_transition('\0') != &a) {
		cout << "do transition wrong result..." << endl;
		error = true;
	}
	if (e.do_transition('\0') != 0) {
		cout << "do transition wrong result..." << endl;
		error = true;
	}
	if (!error) {
		cout << "Edge Success..." << endl;
	}
}
