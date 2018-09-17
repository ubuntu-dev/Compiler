//
// Created by programajor on 3/23/18.
//

#include <iostream>
#include "TableReader.h"

TransitionTable* TableReader::readTransitionTable(ifstream *stream) {
    vector<DfaNode * > fin_nodes;
    vector<string> fin_input;
    vector<vector<DfaNode * >> fin_transitions;

    if (stream->is_open()) {
    	unsigned node_number;
    	if (!(*stream >> node_number) || node_number <1) {
    		cout << "ERROR: In Line 1" << endl;
			return nullptr;
    	}
    	vector<bool> acceptance(node_number);
    	for (unsigned i = 0; i < node_number; i++) {
    		int accept;
    		if (!(*stream >> accept) || accept > 1 || accept < 0) {
    			cout << "Couldn't read correct acceptance mode..." << endl;
				return nullptr;
    		} else {
    			acceptance[i] = accept == 1;
    		}
    	}
    	vector<bool> starting(node_number);
		for (unsigned i = 0; i < node_number; i++) {
			int str;
			if (!(*stream >> str) || str > 1 || str < 0) {
				cout << "Couldn't read correct start mode..." << endl;
				return nullptr;
			} else {
				starting[i] = str == 1;
			}
		}
    	vector<string> realNames(node_number);
    	for (unsigned i = 0; i < node_number; i++) {
			string name;
			if (!(*stream >> name) || name.empty()) {
				cout << "Couldn't read correct name for node..." << endl;
				return nullptr;
			} else {
				realNames[i] = name;
			}
		}
    	unsigned input_number;
		if (!(*stream >> input_number) || input_number <1) {
			cout << "ERROR in input number..." << endl;
			return nullptr;
		}
		vector<string> inputs(input_number);
		for (unsigned i = 0; i < input_number; i++) {
			string input;
			if (!(*stream >> input) || input.empty()) {
				cout << "Couldn't read correct name for input..." << endl;
				return nullptr;
			} else {
				inputs[i] = input;
			}
		}
		vector<string> fakeNames (node_number);
		for (unsigned i = 0; i < node_number - 1; ++i) {
			fakeNames[i] = "n" + to_string(i + 1);
		}
		fakeNames[node_number - 1] = "phi";
		vector<vector<string>> transNames (node_number, vector<string>(input_number));
		for (unsigned i = 0; i < node_number; i++) {
			for (unsigned j = 0; j < input_number; j++) {
				string fakeTrans;
				if (!(*stream >> fakeTrans) || fakeTrans.empty()) {
					cout << "Couldn't read correct name as target for transition..." << endl;
					return nullptr;
				} else {
					transNames[i][j] = fakeTrans;
				}
			}
		}
		vector<DfaNode *> nodes (node_number);
		for (unsigned i = 0; i < node_number; i++) {
			nodes[i] = new DfaNode(realNames[i], acceptance[i]);
			nodes[i]->sePrintingtName(fakeNames[i]);
			nodes[i]->setStart(starting[i]);
		}
		vector<vector<DfaNode *>> transitions (node_number);
		for (unsigned i = 0; i < node_number; i++) {
			for (unsigned j = 0; j < input_number; j++) {
				DfaNode * temp = getNodeFromPrintingName(transNames[i][j], nodes);
				if (temp == nullptr) {
					cout << "Error : Invalid transition" << endl;
					for (unsigned i = 0; i < node_number; i++) {
						delete nodes[i];
					}
					return nullptr;
				} else {
					transitions[i].push_back(temp);
				}
			}
		}
		fin_nodes = nodes;
		fin_input = inputs;
		fin_transitions = transitions;
    }
    return new TransitionTable(fin_nodes, fin_input, fin_transitions);
}


DfaNode *TableReader::getNodeFromPrintingName(string name, vector<DfaNode *> nodes) {
    for (unsigned i = 0; i < nodes.size(); ++i) {
        DfaNode* curr = nodes[i];
        if (curr->getPrintingName() == name) {
            return curr;
        }
    }
    return nullptr;
}
