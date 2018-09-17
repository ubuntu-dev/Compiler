/*
 * Nfa.cpp
 *
 *  Created on: Mar 21, 2018
 *      Author: amrnasr
 */
#include "Nfa.h"
#include <unordered_map>
#include <list>
#include <iostream>
using namespace std;

void Nfa::print_nfa() {
	unordered_map<Node *, unsigned> visited;
	list<Node *> oni_queue;
	oni_queue.push_back(this->start);
	unsigned cn = 0;
	visited[start] = cn;
	cn++;
	while (!oni_queue.empty()) {
		Node * nod = oni_queue.front();
		oni_queue.pop_front();
		for (unsigned j = 0; j < nod->getEdges().size(); j++) {
			Edge *e = nod->getEdges()[j];
			Node * target_node = e->get_target_node();
			if (visited.find(e->get_target_node()) == visited.end()) {
				visited[target_node] = cn;
				cn++;
				oni_queue.push_back(target_node);
			}
			if (e->is_eps_transition()) {
				cout << "n" << visited[nod] << " ----->" << "n" << visited[target_node] << endl;
			} else {
				cout << "n" << visited[nod] << " --" << e->get_first_allowed_char() << "-" << e->get_last_allowed_char() << "--> n" << visited[target_node] << endl;
			}
		}
	}
	cout << "START : n" << visited[start] << " END : n" << visited[this->end] << endl;
}



