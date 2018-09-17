/*
 * DfaMinimizerTest.cpp
 *
 *  Created on: Mar 20, 2018
 *      Author: michael
 */
#include "../../../test_headers/p1_tests.h"
#include <vector>
#include <iostream>
#include <string>
#include "../minimizer/DfaMinimizer.h"
#include "../../transition_table/model/DfaEdge.h"
using namespace std;


void minimizer_test_3() {
	DfaNode * x = new DfaNode("X",false);
	DfaNode * y = new DfaNode("Y",false);
	DfaNode * z = new DfaNode("Z",true);
	DfaNode * w = new DfaNode("W",false);
	DfaNode * t = new DfaNode("T",false);
	DfaNode * u = new DfaNode("U",true);
	DfaNode * v = new DfaNode("V",true);
	DfaNode * phi = new DfaNode("", true);
	vector<string> pri = {
	    		"Z","U","V",""
	    };
	DfaEdge * xy = new DfaEdge('0', '0', x, y);
	DfaEdge * xz = new DfaEdge('1', '1', x, z);
	DfaEdge * yy = new DfaEdge('0', '0', y, y);
	DfaEdge * yw = new DfaEdge('1', '1', y, w);
	DfaEdge * zt = new DfaEdge('0', '0', z, t);
	DfaEdge * zu = new DfaEdge('1', '1', z, u);
	DfaEdge * wt = new DfaEdge('0', '0', w, t);
	DfaEdge * wv = new DfaEdge('1', '1', w, v);
	DfaEdge * ty = new DfaEdge('0', '0', t, y);
	DfaEdge * tz = new DfaEdge('1', '1', t, z);
	DfaEdge * uphi = new DfaEdge('0', '0', u, phi);
	DfaEdge * ut = new DfaEdge('1', '1', u, t);
	DfaEdge * vy = new DfaEdge('0', '0', v, y);
	DfaEdge * vy_1 = new DfaEdge('1', '1', v, y);
	DfaEdge * phiphi = new DfaEdge('0', '0', phi, phi);
	DfaEdge * phiphi_1 = new DfaEdge('1', '1', phi, phi);
	x->addEdge(xz);
	x->addEdge(xy);
	t->addEdge(ty);
	t->addEdge(tz);
	w->addEdge(wv);
	w->addEdge(wt);
	z->addEdge(zt);
	z->addEdge(zu);
	y->addEdge(yy);
	y->addEdge(yw);
	phi->addEdge(phiphi);
	phi->addEdge(phiphi_1);
	v->addEdge(vy_1);
	v->addEdge(vy);
	u->addEdge(uphi);
	u->addEdge(ut);

	DfaMinimizer g;
	vector<DfaNode*> result;
	g.getMinimizedDFA(&result, x, &pri);
	if ((result[0]->getEdges()[0]->get_target_node()->getName()) != "Y"){
		cout << "error4" << endl;
	}
	if ((result[0]->getEdges()[1]->get_target_node()->getName()) != "Z"){
			cout << "error5" << endl;
	}
	if ((result[0]->getEdges()[1]->get_target_node(
			)->getEdges()[1]->get_target_node()->getName()) != "U"){
				cout << "error5" << endl;
	}
	if ((result[0]->getEdges()[0]->get_target_node(
				)->getEdges()[1]->get_target_node()->getName()) != "W"){
					cout << "error5" << endl;
	}

	if ((result[0]->getEdges()[0]->get_target_node(
					)->getEdges()[1]->get_target_node()->getEdges()[1]->
					get_target_node()->getName()) != "V"){
						cout << "error5" << endl;
	}

	if ((result[0]->getEdges()[0]->get_target_node(
						)->getEdges()[1]->get_target_node()->getEdges()[1]->
						get_target_node()->getEdges()[0]->get_target_node()->getName()) != "Y" &&
			(result[0]->getEdges()[0]->get_target_node(
				)->getEdges()[1]->get_target_node()->getEdges()[1]->
				get_target_node()->getEdges()[1]->get_target_node()->getName()) != "Y"){
							cout << "error5" << endl;
		}

	if ((z->getEdges()[0]->get_target_node()) != result[0]){
				cout << "error hna" << endl;
	}
	cout << "Minimizer Success..." << endl;
}


void minimizer_test_2() {
	DfaNode * x = new DfaNode("X",false);
	DfaNode * y = new DfaNode("Y",false);
	DfaNode * z = new DfaNode("Z",true);
	DfaNode * w = new DfaNode("W",false);
	DfaNode * t = new DfaNode("T",false);
	vector<string> pri = {
	    		"Z"
	    };
	DfaEdge * xy = new DfaEdge('0', '0', x, y);
	DfaEdge * xz = new DfaEdge('1', '1', x, z);
	DfaEdge * yx = new DfaEdge('0', '0', y, x);
	DfaEdge * yz = new DfaEdge('1', '1', y, z);
	DfaEdge * zx = new DfaEdge('0', '0', z, x);
	DfaEdge * zw = new DfaEdge('1', '1', z, w);
	DfaEdge * wt = new DfaEdge('0', '0', w, t);
	DfaEdge * wz = new DfaEdge('1', '1', w, z);
	DfaEdge * tt = new DfaEdge('0', '0', t, t);
	DfaEdge * tz = new DfaEdge('1', '1', t, z);
	x->addEdge(xy);
	t->addEdge(tz);
	t->addEdge(tt);
	w->addEdge(wz);
	w->addEdge(wt);
	z->addEdge(zw);
	z->addEdge(zx);
	y->addEdge(yx);
	y->addEdge(yz);
	x->addEdge(xz);
	DfaMinimizer g;
	vector<DfaNode*> result;
	g.getMinimizedDFA(&result, x,&pri);
	if ((result[0]->getEdges()[0]->get_target_node()) != result[0]){
		cout << "error1" << endl;
	}
	if ((result[0]->getEdges()[1]->get_target_node()->getName()) != "Z"){
			cout << "error2" << endl;
	}
	if ((z->getEdges()[0]->get_target_node()) != result[0]
			|| (z->getEdges()[1]->get_target_node()) != result[0]){
				cout << "error3" << endl;
	}
	minimizer_test_3();
}


void test_minimizer(void) {
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
	DfaNode * e = new DfaNode("\0", false);
	DfaEdge * xy = new DfaEdge('0', '0', x, y);
	DfaEdge * xe = new DfaEdge('1', '1', x, e);
	DfaEdge * yz = new DfaEdge('0', '0', y, z);
	DfaEdge * yw = new DfaEdge('1', '1', y, w);
	DfaEdge * zt = new DfaEdge('0', '0', z, t);
	DfaEdge * zz = new DfaEdge('1', '1', z, z);
	DfaEdge * wu = new DfaEdge('0', '0', w, u);
	DfaEdge * wz = new DfaEdge('1', '1', w, z);
	DfaEdge * te = new DfaEdge('0', '0', t, e);
	DfaEdge * tv = new DfaEdge('1', '1', t, v);
	DfaEdge * uq = new DfaEdge('0', '0', u, q);
	DfaEdge * uv = new DfaEdge('1', '1', u, v);
	DfaEdge * vu = new DfaEdge('0', '0', v, u);
	DfaEdge * vz = new DfaEdge('1', '1', v, z);
	DfaEdge * qt = new DfaEdge('0', '0', q, t);
	DfaEdge * qw = new DfaEdge('1', '1', q, w);
	DfaEdge * ee = new DfaEdge('0', '0', e, e);
	DfaEdge * ee1 = new DfaEdge('1', '1', e, e);
	e->addEdge(ee);
	e->addEdge(ee1);
	q->addEdge(qw);
	q->addEdge(qt);
	v->addEdge(vz);
	v->addEdge(vu);
	u->addEdge(uv);
	u->addEdge(uq);
	t->addEdge(te);
	t->addEdge(tv);
	w->addEdge(wz);
	w->addEdge(wu);
	z->addEdge(zz);
	z->addEdge(zt);
	y->addEdge(yw);
	y->addEdge(yz);
	x->addEdge(xy);
	x->addEdge(xe);
	DfaMinimizer g;
	PartitionSet cl(1);
	vector<DfaNode*> result;
	g.getMinimizedDFA(&result, x,&pri);

	minimizer_test_2();

}

