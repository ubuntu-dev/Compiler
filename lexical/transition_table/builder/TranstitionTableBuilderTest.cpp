//
// Created by programajor on 3/23/18.
//

#include "../../../test_headers/p1_tests.h"
#include "../../lexical_analyzer_generator/minimizer/DfaMinimizer.h"
#include "../model/DfaEdge.h"
#include "../model/TransitionTable.h"
#include "TableBuilder.h"
#include <iostream>

void test_transition_table_builder() {
    // sheet 2 1-c
    DfaNode * x = new DfaNode("X",false);
    DfaNode * y = new DfaNode("Y",true);
    DfaNode * z = new DfaNode("Z",false);
    DfaNode * w = new DfaNode("W",true);
    DfaNode * t = new DfaNode("T",true);
    DfaNode * u = new DfaNode("U",true);
    DfaNode * v = new DfaNode("V",true);
    DfaNode * q = new DfaNode("Q",true);
    vector<string> pri = {
        		"Y","W","T","U","V", "Q"
        };
    DfaEdge * xy = new DfaEdge('0', '0', x, y);
    DfaEdge * yz = new DfaEdge('0', '0', y, z);
    DfaEdge * yw = new DfaEdge('1', '1', y, w);
    DfaEdge * zt = new DfaEdge('0', '0', z, t);
    DfaEdge * zz = new DfaEdge('1', '1', z, z);
    DfaEdge * wu = new DfaEdge('0', '0', w, u);
    DfaEdge * wz = new DfaEdge('1', '1', w, z);
    DfaEdge * tv = new DfaEdge('1', '1', t, v);
    DfaEdge * uq = new DfaEdge('0', '0', u, q);
    DfaEdge * uv = new DfaEdge('1', '1', u, v);
    DfaEdge * vu = new DfaEdge('0', '0', v, u);
    DfaEdge * vz = new DfaEdge('1', '1', v, z);
    DfaEdge * qt = new DfaEdge('0', '0', q, t);
    DfaEdge * qw = new DfaEdge('1', '1', q, w);
    q->addEdge(qw);
    q->addEdge(qt);
    v->addEdge(vz);
    v->addEdge(vu);
    u->addEdge(uv);
    u->addEdge(uq);
    t->addEdge(tv);
    w->addEdge(wz);
    w->addEdge(wu);
    z->addEdge(zz);
    z->addEdge(zt);
    y->addEdge(yw);
    y->addEdge(yz);
    x->addEdge(xy);

    DfaMinimizer g;
    vector<DfaNode*> result;
    g.getMinimizedDFA(&result, x, &pri);

    set<char> alphabets;
    alphabets.insert('0');
    alphabets.insert('1');

    TableBuilder builder;
    TransitionTable table = builder.buildTransitionTable(result, &alphabets);

    vector<DfaNode *> nodes = table.getNodes();
    vector<string> input = table.getInputs();
    vector<vector<DfaNode *>> transitions = table.getTransitions();
    cout << "Transition Table build success..." << endl;
}
