//
// Created by programajor on 3/16/18.
//

#include <algorithm>
#include <stack>
#include "NfaBuilder.h"
#include "../models/Edge.h"

Nfa * NfaBuilder::construct_eps_nfa() {
    return construct_letter_nfa(EPS);
}

Nfa * NfaBuilder::construct_letter_nfa(char c) {
    auto start = new Node(!ACCEPT_STATE);
    auto end = new Node(ACCEPT_STATE);
    auto edge = new Edge(c, c, end);
    start->addEdge(edge);
    auto nfa = new Nfa();
    nfa->start = start;
    nfa->end = end;
    return nfa;
}

Nfa * NfaBuilder::construct_range_nfa(char cStart, char cEnd) {
    auto start = new Node(!ACCEPT_STATE);
    auto end = new Node(ACCEPT_STATE);
    auto edge = new Edge(cStart, cEnd, end);
    start->addEdge(edge);
    auto nfa = new Nfa();
    nfa->start = start;
    nfa->end = end;
    return nfa;
}

Nfa * NfaBuilder::construct_or_nfa(Nfa * a, Nfa * b) {
    Node* oldAStart = a->start;
    Node* oldAEnd = a->end;

    Node* oldBStart = b->start;
    Node* oldBEnd = b->end;

    // remove old acceptance states
    oldAEnd->setAcceptState(false);
    oldBEnd->setAcceptState(false);

    auto newStart = new Node(!ACCEPT_STATE);
    auto newEnd = new Node(ACCEPT_STATE);
    newStart->addEdge(new Edge(EPS, EPS, oldAStart));
    newStart->addEdge(new Edge(EPS, EPS, oldBStart));

    oldAEnd->addEdge(new Edge(EPS, EPS, newEnd));
    oldBEnd->addEdge(new Edge(EPS, EPS, newEnd));

    auto nfa = new Nfa();
    nfa->start = newStart;
    nfa->end = newEnd;

    delete a;
    delete b;

    return nfa;
}

Nfa* NfaBuilder::combine_nfa(Nfa *a, Nfa *b) {
	Node* oldAStart = a->start;
	Node* oldBStart = b->start;

	auto newStart = new Node(!ACCEPT_STATE);
	newStart->addEdge(new Edge(EPS, EPS, oldAStart));
	newStart->addEdge(new Edge(EPS, EPS, oldBStart));

	auto nfa = new Nfa();
	nfa->start = newStart;

	delete a;
	delete b;

	return nfa;
}

Nfa * NfaBuilder::construct_and_nfa(Nfa * a, Nfa * b) {
    Node* oldAStart = a->start;
    Node* oldAEnd = a->end;

    Node* oldBStart = b->start;
    Node* oldBEnd = b->end;

    // remove old acceptance states
    oldAEnd->setAcceptState(false);
    oldBEnd->setAcceptState(false);

    auto newStart = new Node(!ACCEPT_STATE);
    auto newEnd = new Node(ACCEPT_STATE);

    newStart->addEdge(new Edge(EPS, EPS, oldAStart));
    oldAEnd->addEdge(new Edge(EPS, EPS, oldBStart));
    oldBEnd->addEdge(new Edge(EPS, EPS, newEnd));

    auto nfa = new Nfa();
    nfa->start = newStart;
    nfa->end = newEnd;

    delete a;
    delete b;

    return nfa;
}

Nfa * NfaBuilder::construct_closure_nfa(Nfa * a) {
    Nfa * nfa = construct_positive_closure_nfa(a); // only need to add edge between start and end
    nfa->start->addEdge(new Edge(EPS, EPS, nfa->end));
    return nfa;
}

Nfa * NfaBuilder::construct_positive_closure_nfa(Nfa * a) {
    Node* oldStart = a->start;
    Node* oldEnd = a->end;
    oldEnd->setAcceptState(false);
    auto oldEndToStart = new Edge(EPS, EPS, oldStart);
    oldEnd->addEdge(oldEndToStart); // add backward edge

    auto newStart = new Node(!ACCEPT_STATE);
    auto newEnd = new Node(ACCEPT_STATE);
    newStart->addEdge(new Edge(EPS, EPS, oldStart));
    oldEnd->addEdge(new Edge(EPS, EPS, newEnd));

    auto nfa = new Nfa();
    nfa->start = newStart;
    nfa->end = newEnd;
    return nfa;
}

void NfaBuilder::get_separated_nfas(vector<Nfa *> *nfas,vector<NfaToken> *nfa_tokens) {
    for (NfaToken& nfaToken : (*nfa_tokens)) {
        nfas->push_back(build_graph(&nfaToken));
    }
}

Nfa * NfaBuilder::build_graph(NfaToken * nfa_token) {
    stack<Nfa *> nfaStack;
    for (MiniToken& miniToken : nfa_token->tokens){
        if (miniToken.type == OPERATION) {
            if (miniToken.tok == "|") { // or
                Nfa * b = nfaStack.top();
                nfaStack.pop();
                Nfa * a = nfaStack.top();
				nfaStack.pop();
                nfaStack.push(construct_or_nfa(a, b));
            } else if (miniToken.tok == "@") { // and
                Nfa * b = nfaStack.top();
                nfaStack.pop();
                Nfa * a = nfaStack.top();
                nfaStack.pop();
                nfaStack.push(construct_and_nfa(a, b));
            } else if (miniToken.tok == "*") { // closure
                Nfa * a = nfaStack.top();
                nfaStack.pop();
                nfaStack.push(construct_closure_nfa(a));
            } else if (miniToken.tok == "+") { // positive closure
                Nfa * a = nfaStack.top();
                nfaStack.pop();
                nfaStack.push(construct_positive_closure_nfa(a));
            }
        } else { // add to stack - operand -
            nfaStack.push(get_nfa(&miniToken));
        }
    }

    Nfa * finalNfa = nfaStack.top();
    finalNfa->end->setName(nfa_token->tokenName);
    return finalNfa;
}

Nfa * NfaBuilder::get_nfa (MiniToken *miniToken) {
    string tok = miniToken->tok;
    Nfa * result = nullptr;

    switch (miniToken->type) {
        case CHAR_GROUP: {
            result = construct_range_nfa(miniToken->tok[0], miniToken->tok[miniToken->tok.size() - 1]);
        } break;
        case EPSILON: {
            result = construct_eps_nfa();
        } break;
        case WORD: {
            bool first = true;
            Nfa * prev = nullptr;
            for (char c : tok) {
                if (first) {
                    first = false;
                    prev = construct_letter_nfa(c);
                } else {
                    Nfa * a = prev;
                    Nfa * b = construct_letter_nfa(c);
                    prev = construct_and_nfa(a, b);
                }
            }
            result = prev;

        } break;
        case OPERATION: {
        	result = nullptr;
        }
        	break;
        case PARENTHESES: {
        	result = nullptr;
        }
        	break;
    }

    return result;
}
