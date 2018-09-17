//
// Created by programajor on 3/21/18.
//

#include "../../../test_headers/p1_tests.h"
#include "NfaDfaConverter.h"
#include <iostream>

using namespace std;

void test_nfa_dfa_converter() {
    Node * n1 = new Node("1", false);
    Node * n2 = new Node("2", false);
    Node * n3 = new Node("if", true);
    Node * n4 = new Node("4", false);
    Node * n5 = new Node("5", false);
    Node * n6 = new Node("6", false);
    Node * n7 = new Node("7", false);
    Node * n8 = new Node("then", true);
    Node * n9 = new Node("9", false);
    Node * n10 = new Node("10", false);
    Node * n11 = new Node("11", false);
    Node * n12 = new Node("12", false);
    Node * n13 = new Node("else", true);
    Node * n14 = new Node("14", false);
    Node * n15 = new Node("15", false);
    Node * n16 = new Node("16", false);
    Node * n17 = new Node("17", false);
    Node * n18 = new Node("18", false);
    Node * n19 = new Node("19", false);
    Node * n20 = new Node("relop", true);
    Node * n21 = new Node("21", false);
    Node * n22 = new Node("22", false);
    Node * n23 = new Node("id", true);
    Node * n24 = new Node("24", false);
    Node * n25 = new Node("num", true);

    Edge * e1 = new Edge('\0', '\0', n1);
    Edge * e2 = new Edge('\0', '\0', n4);
    Edge * e3 = new Edge('\0', '\0', n9);
    Edge * e4 = new Edge('\0', '\0', n14);
    Edge * e5 = new Edge('\0', '\0', n17);
    Edge * e6 = new Edge('\0', '\0', n18);
    Edge * e7 = new Edge('\0', '\0', n21);
    Edge * e8 = new Edge('\0', '\0', n22);
    Edge * e9 = new Edge('\0', '\0', n24);

    n17->addEdge(e4);
    n17->addEdge(e6);
    n17->addEdge(e7);

    n16->addEdge(e1);
    n16->addEdge(e2);
    n16->addEdge(e3);
    n16->addEdge(e5);
    n16->addEdge(e8);
    n16->addEdge(e9);

    Edge * e10 = new Edge('i', 'i', n2);
    Edge * e11 = new Edge('f', 'f', n3);

    n1->addEdge(e10);
    n2->addEdge(e11);

    Edge * e12 = new Edge('t', 't', n5);
    Edge * e13 = new Edge('h', 'h', n6);
    Edge * e14 = new Edge('e', 'e', n7);
    Edge * e15 = new Edge('n', 'n', n8);

    n4->addEdge(e12);
    n5->addEdge(e13);
    n6->addEdge(e14);
    n7->addEdge(e15);

    Edge * e29 = new Edge('e', 'e', n10);
    Edge * e30 = new Edge('l', 'l', n11);
    Edge * e31 = new Edge('s', 's', n12);
    Edge * e32 = new Edge('e', 'e', n13);

    n9->addEdge(e29);
    n10->addEdge(e30);
    n11->addEdge(e31);
    n12->addEdge(e32);

    Edge * e16 = new Edge('<', '<', n15);
    Edge * e17 = new Edge('=', '=', n20);
    Edge * e18 = new Edge('>', '>', n20);
    Edge * e19 = new Edge('>', '>', n19);
    Edge * e20 = new Edge('=', '=', n20);
    Edge * e21 = new Edge('=', '=', n20);

    n14->addEdge(e16);
    n15->addEdge(e17);
    n15->addEdge(e18);
    n18->addEdge(e19);
    n19->addEdge(e20);
    n21->addEdge(e21);

    Edge * e22 = new Edge('a', 'z', n23);
    Edge * e23 = new Edge('A', 'Z', n23);
    Edge * e24 = new Edge('a', 'z', n23);
    Edge * e25 = new Edge('A', 'Z', n23);
    Edge * e26 = new Edge('0', '9', n23);
    Edge * e27 = new Edge('0', '9', n25);
    Edge * e28 = new Edge('0', '9', n25);

    n22->addEdge(e22);
    n22->addEdge(e23);
    n23->addEdge(e24);
    n23->addEdge(e25);
    n23->addEdge(e26);
    n24->addEdge(e27);
    n25->addEdge(e28);
    set<char> alpha;
    NfaDfaConverter converter;
    vector<string> correctPriority = {
    		"if", "then", "else", "relop", "id", "num"
    };
    DfaNode* node = converter.getNonMinimizedDFA(n16, &correctPriority, &alpha);
    node->getEdges();
    cout << "Converter Sucess..." << endl;
}


