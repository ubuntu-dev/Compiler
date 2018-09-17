//
// Created by marc on 3/20/18.
//
#include <list>
#include "NfaBuilder.h"
#include "../../../test_headers/p1_tests.h"
#include <unordered_set>

using namespace std;

void test_nfa_builder() {
	vector<NfaToken> correctTokens = {
	        NfaToken (REGULAR_EXPRESSION, "id", vector<MiniToken> ({
	               MiniToken (CHAR_GROUP, "a-z"),
	               MiniToken (CHAR_GROUP, "A-Z"),
	               MiniToken (OPERATION, "|"),
	               MiniToken (CHAR_GROUP, "a-z"),
	               MiniToken (CHAR_GROUP, "A-Z"),
	               MiniToken (OPERATION, "|"),
	               MiniToken (CHAR_GROUP, "0-9"),
	               MiniToken (OPERATION, "|"),
	               MiniToken (OPERATION, "*"),
	               MiniToken (OPERATION, "@")
	         })),
	        NfaToken (KEYWORD, "boolean", vector<MiniToken> ({MiniToken (WORD, "boolean")})),
	        NfaToken (KEYWORD, "int", vector<MiniToken> ({MiniToken (WORD, "int")})),
	        NfaToken (KEYWORD, "float", vector<MiniToken> ({MiniToken (WORD, "float")})),
	        NfaToken (REGULAR_EXPRESSION, "num", vector<MiniToken> ({
	            MiniToken (CHAR_GROUP, "0-9"),
	            MiniToken (OPERATION, "+"),
	            MiniToken (CHAR_GROUP, "0-9"),
	            MiniToken (OPERATION, "+"),
	            MiniToken (OPERATION, "|"),
	            MiniToken (WORD, "."),
	            MiniToken (OPERATION, "@"),
	            MiniToken (CHAR_GROUP, "0-9"),
	            MiniToken (OPERATION, "+"),
	            MiniToken (OPERATION, "@"),
	            MiniToken (EPSILON, "\\L"),
	            MiniToken (WORD, "E"),
	            MiniToken (CHAR_GROUP, "0-9"),
	            MiniToken (OPERATION, "+"),
	            MiniToken (OPERATION, "@"),
	            MiniToken (OPERATION, "|"),
	            MiniToken (OPERATION, "@")
	                    })),
	        NfaToken (REGULAR_EXPRESSION, "relop", vector<MiniToken> ({
	              MiniToken (WORD, "=="),
	              MiniToken (WORD, "!="),
	              MiniToken (OPERATION, "|"),
	              MiniToken (WORD, ">"),
	              MiniToken (OPERATION, "|"),
	              MiniToken (WORD, ">="),
	              MiniToken (OPERATION, "|"),
	              MiniToken (WORD, "<"),
	              MiniToken (OPERATION, "|"),
	              MiniToken (WORD, "<="),
	              MiniToken (OPERATION, "|")
	                                          })),
	        NfaToken (REGULAR_EXPRESSION, "assign", vector<MiniToken> ({MiniToken (WORD, "=")})),
	        NfaToken (KEYWORD, "if", vector<MiniToken> ({MiniToken (WORD, "if")})),
	        NfaToken (KEYWORD, "else", vector<MiniToken> ({MiniToken (WORD, "else")})),
	        NfaToken (KEYWORD, "while", vector<MiniToken> ({MiniToken (WORD, "while")})),
	        NfaToken (PUNCTUATION, ";", vector<MiniToken> ({MiniToken (WORD, ";")})),
	        NfaToken (PUNCTUATION, ",", vector<MiniToken> ({MiniToken (WORD, ",")})),
	        NfaToken (PUNCTUATION, "(", vector<MiniToken> ({MiniToken (WORD, "(")})),
	        NfaToken (PUNCTUATION, ")", vector<MiniToken> ({MiniToken (WORD, ")")})),
	        NfaToken (PUNCTUATION, "{", vector<MiniToken> ({MiniToken (WORD, "{")})),
	        NfaToken (PUNCTUATION, "}", vector<MiniToken> ({MiniToken (WORD, "}")})),
	        NfaToken (REGULAR_EXPRESSION, "addop", vector<MiniToken> ({
	                  MiniToken (WORD, "+"),
	                  MiniToken (WORD, "-"),
	                  MiniToken (OPERATION, "|"),
	          })),
	        NfaToken (REGULAR_EXPRESSION, "mulop", vector<MiniToken> ({
	                  MiniToken (WORD, "*"),
	                  MiniToken (WORD, "/"),
	                  MiniToken (OPERATION, "|"),
	          }))
	};
	NfaBuilder nfaBuilder;
    vector<NfaToken *> correctTokensPnt;
    for (unsigned i = 0; i < correctTokens.size(); i++) {
    	correctTokensPnt.push_back(&correctTokens[i]);
    }
    vector<Nfa *> nfas;
	nfaBuilder.get_separated_nfas(&nfas, &correctTokens);
    // size of nfas should be 18
    bool error = false;
    if (nfas.size() != 18) {
        error = true;
        cout << "NFAs count not correct" << endl << "WRONG. Found : " << endl;
        cout << nfas.size();
        cout << "Expected : 18" << endl;
    }
    Node start("1", false);
	Node n2 = Node("2", false);
	Node n3 = Node("3", false);
	Node n4 = Node("4", false);
	Node n5 = Node("5", false);
	Node n6 = Node("6", false);
	Node n7 = Node("7", false);
	Node n8 = Node("8", false);
	Node n9 = Node("9", false);
	Node n10 = Node("10", false);
	Node n11 = Node("11", false);
	Node n12 = Node("12", false);
	Node n13 = Node("13", false);
	Node n14 = Node("14", false);
	Node n15 = Node("15", false);
	Node n16 = Node("16", false);
	Node n17 = Node("17", false);
	Node n18 = Node("18", false);
	Node n19 = Node("19", false);
	Node endn = Node("end", true);

	Edge e1(EPS, EPS, &n2);
	Edge e2(EPS, EPS, &n3);
	Edge e3('a', 'z', &n4);
	Edge e4(EPS, EPS, &n7);
	Edge e5(EPS, EPS, &n5);
	Edge e6('A', 'Z', &n6);
	Edge e7(EPS, EPS, &n7);
	Edge e8(EPS, EPS, &n8);

	Edge e9(EPS, EPS, &n9);
	Edge e10(EPS, EPS, &n10);
	Edge e11(EPS, EPS, &n11);
	Edge e12('a', 'z', &n12);
	Edge e13(EPS, EPS, &n13);
	Edge e14(EPS, EPS, &n14);
	Edge e15('A', 'Z', &n15);
	Edge e16(EPS, EPS, &n13);
	Edge e17(EPS, EPS, &n18);
	Edge e18(EPS, EPS, &n16);
	Edge e19('0', '9', &n17);
	Edge e20(EPS, EPS, &n18);
	Edge e21(EPS, EPS, &n9);
	Edge e22(EPS, EPS, &n19);
	Edge e23(EPS, EPS, &n19);
	Edge e24(EPS, EPS, &endn);

	start.addEdge(&e1);
	n2.addEdge(&e2);
	n2.addEdge(&e5);
	n3.addEdge(&e3);
	n4.addEdge(&e4);
	n5.addEdge(&e6);
	n6.addEdge(&e7);
	n7.addEdge(&e8);

	n8.addEdge(&e9);
	n8.addEdge(&e22);
	n9.addEdge(&e10);
	n9.addEdge(&e18);
	n10.addEdge(&e11);
	n10.addEdge(&e14);
	n11.addEdge(&e12);
	n12.addEdge(&e13);
	n13.addEdge(&e17);
	n14.addEdge(&e15);
	n15.addEdge(&e16);

	n16.addEdge(&e19);
	n17.addEdge(&e20);
	n18.addEdge(&e21);
	n18.addEdge(&e23);
	n19.addEdge(&e24);
    Node * node = &start;
    Node * node2 = nfas.front()->start;
    unordered_set<Node*> visited;
    unordered_set<Node*> visited2;
    list<Node*> queue;
    list<Node*> queue2;

    queue2.push_back(node2);
    queue.push_back(node);
    unsigned nc = 0;
    while (!error && !queue.empty()) {
        node = queue.front();
        node2 = queue2.front();
        queue.pop_front();
        queue2.pop_front();
        visited.insert(node);
        visited2.insert(node2);
        if (node->getEdges().size() != node2->getEdges().size()) {
        	cout << "At node " + node->getName() + " Expected : " << node->getEdges().size() << " Found : " << node2->getEdges().size() << endl;
        	error = true;
        } else {
        	for (unsigned i = 0; i < node->getEdges().size(); i++) {
        		Edge *e1 = node->getEdges()[i];
        		Edge *e2 = node2->getEdges()[i];
				if (e1->equals(e2)) {
					Node *n1 = e1->get_target_node();
					Node *n2 = e2->get_target_node();
					if (visited.find(n1) == visited.end()) {
						queue.push_back(n1);
					}
					if (visited2.find(n2) == visited2.end()) {
						queue2.push_back(n2);
					}
				} else {
					cout << i << endl;
					error = true;
				}
			}
        }
        nc++;
    }

    if (!error) {
        cout << "NFA builder Success..." << endl;
    } else {
    	cout << "NFA builder Failed..." << endl;
    }
}

