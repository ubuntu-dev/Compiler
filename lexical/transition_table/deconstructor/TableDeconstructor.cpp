//
// Created by programajor on 3/23/18.
//

#include "TableDeconstructor.h"
#include "../model/DfaEdge.h"

vector<DfaNode *> TableDeconstructor::deconstructGraph(TransitionTable table) {
    vector<DfaNode * > nodes = table.getNodes();
    vector<string> input = table.getInputs();
    vector<vector<DfaNode * >> transitions = table.getTransitions();

    DfaNode* phi = nodes[nodes.size() - 1];
    for (int i = 0; i < input.size(); ++i) {
        string singleInput = input[i];
        for (int j = 0; j < singleInput.length(); j += 3) {
            for (int k = 0; k < transitions.size(); ++k) {
                DfaNode* start = nodes[k];
                DfaNode* target = transitions[k][i];
                char s = singleInput[j];
                char t = singleInput[j + 2];
                if (target != phi && start != phi) {
                    DfaEdge* edge = new DfaEdge(s, t, start, target);
                    start->addEdge(edge);
                }
            }
        }
    }
    return nodes;
}
