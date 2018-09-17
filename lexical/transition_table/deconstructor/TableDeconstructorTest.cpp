//
// Created by programajor on 3/23/18.
//

#include <fstream>
#include "../../../test_headers/p1_tests.h"
#include "../reader/TableReader.h"
#include "../writer/TableWriter.h"
#include "../builder/TableBuilder.h"
#include "TableDeconstructor.h"
#include "../model/DfaEdge.h"
#include <iostream>

void test_transition_table_deconstructor(void) {
	DfaNode * x = new DfaNode("X",false);
	DfaNode * y = new DfaNode("Y",true);
	DfaNode * z = new DfaNode("Z",false);
	DfaNode * w = new DfaNode("W",true);
	DfaNode * t = new DfaNode("T",true);
	DfaNode * u = new DfaNode("U",true);
	DfaNode * v = new DfaNode("V",true);
	DfaNode * q = new DfaNode("Q",true);
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
	vector<string> pri = {
			"Y","W","T","U","V", "Q"
	};
	g.getMinimizedDFA(&result, x, &pri);

	set<char> alphabets;
	alphabets.insert('0');
	alphabets.insert('1');

	TableBuilder builder;
	TransitionTable table = builder.buildTransitionTable(result, &alphabets);

	vector<DfaNode *> nodes = table.getNodes();
	vector<string> input = table.getInputs();
	vector<vector<DfaNode *>> transitions = table.getTransitions();

	std::streambuf * buf;
	std::ofstream of;
	of.open("file2_tbwt.txt");
	buf = of.rdbuf();
	std::ostream out(buf);

	TableWriter writer;
	writer.writeTransitionTableInReadableForamt(table, &out);
	out.flush();
    std::ifstream of2;
    of2.open("file2_tbwt.txt");

    TableReader reader;
    TransitionTable *table2 = reader.readTransitionTable(&of2);

    TableDeconstructor deconstructor;
    vector<DfaNode*> nodes2 = deconstructor.deconstructGraph(*table2);
    if( remove( "file2_tbwt.txt" ) != 0 ) {
		cout << "File not generated : Table reader failed" << endl;
	} else {
		cout << "Table reader success..." << endl;
	}
}
