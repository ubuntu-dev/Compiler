//
// Created by programajor on 3/23/18.
//

#include <iostream>
#include "TableWriter.h"
#include <iomanip>

void TableWriter::writeTransitionTableInHumanReadableFormat(TransitionTable table, ostream* stream) {
    vector<DfaNode *> nodes = table.getNodes();
    vector<string> input = table.getInputs();
    vector<vector<DfaNode *>> transitions = table.getTransitions();
    for (unsigned i = 0; i < nodes.size() - 1; ++i) {
        nodes[i]->sePrintingtName("n" + std::to_string(i + 1));
    }
    nodes[nodes.size() - 1]->sePrintingtName("phi");

    *stream << left << setw(20) << "states\\input";
    *stream << "|";
    for (unsigned i = 0; i < input.size(); ++i) {
        *stream << setw(12) << input[i];
        *stream << "|";
    }
    *stream << setw(15) << "isAccepted" << "|" << setw(20) << "AcceptanceName" << "|" << setw(7) << "isStart" << "|" << endl;
    for (unsigned i = 0; i < transitions.size(); ++i) {
        *stream << left << setw(20) << nodes[i]->getPrintingName() << "|";
        for (unsigned j = 0; j < input.size(); ++j) {
        	string temp = transitions[i][j]->getPrintingName();
        	if (temp == "phi") {
        		temp = "";
        	}
            *stream << setw(12) << temp << "|";
        }

        if (nodes[i]->isAcceptedState() ) {
            *stream << setw(15) << "YES" << "|"<< setw(20) << nodes[i]->getName()<< "|";
        } else {
            *stream << setw(15) << "NO" << "|" << setw(20) << "NONE" << "|";
        }

        if (nodes[i]->isStart() ) {
            *stream << setw(7) << "YES" << "|";
        } else {
            *stream << setw(7) << "NO" << "|";
        }
        *stream << endl;
    }
}

void TableWriter::writeTransitionTableInReadableForamt(TransitionTable table, ostream* stream) {
    vector<DfaNode *> nodes = table.getNodes();
    vector<string> input = table.getInputs();
    vector<vector<DfaNode *>> transitions = table.getTransitions();
    for (unsigned i = 0; i < nodes.size() - 1; ++i) {
        nodes[i]->sePrintingtName("n" + std::to_string(i + 1));
    }
    nodes[nodes.size() - 1]->sePrintingtName("phi");

    *stream << std::to_string(nodes.size()) + "\n";
    for (unsigned i = 0; i < nodes.size(); ++i) {
        *stream << (nodes[i]->isAcceptedState() ? "1 " : "0 ");
    }
    *stream << "\n";

    for (unsigned i = 0; i < nodes.size(); ++i) {
        *stream << (nodes[i]->isStart() ? "1 " : "0 ");
    }
    *stream << "\n";

    for (unsigned i = 0; i < nodes.size(); ++i) {
        *stream << nodes[i]->getName() + "\n";
    }

    *stream << std::to_string(input.size()) + "\n";
    for (unsigned i = 0; i < input.size(); ++i) {
        *stream << input[i] + "\n";
    }

    for (unsigned i = 0; i < transitions.size(); ++i) {
        for (unsigned j = 0; j < transitions[i].size(); ++j) {
            *stream << transitions[i][j]->getPrintingName() + "\n";
        }
    }
}
