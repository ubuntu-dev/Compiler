//
// Created by programajor on 3/16/18.
//

#ifndef COMPILERS_NFABUILDER_H
#define COMPILERS_NFABUILDER_H


#include "../models/Nfa.h"
#include "../models/NfaToken.h"
#include <vector>
#include <iostream>

using namespace std;

class NfaBuilder {
	private:
		Nfa* construct_eps_nfa();
		Nfa* construct_letter_nfa(char c);
		Nfa* construct_range_nfa(char start, char end);
		Nfa* construct_and_nfa(Nfa * a, Nfa * b);
		Nfa* construct_closure_nfa(Nfa * a);
		Nfa* construct_positive_closure_nfa(Nfa * a);
        Nfa* build_graph(NfaToken * nfa_token);
		Nfa* get_nfa (MiniToken * miniToken);
		Nfa* construct_or_nfa(Nfa *a, Nfa *b);
	public:
        /**
         * takes list of regular expression names and their corresponding post-fix rules.
         * @param regExpNames List of regular names (LHS)
         * @param regExp 	  List of regular expressions in post-fix format (RHS).
         * Example lists:
         * regExpNames : {"id", "digit"}
         * regExp : { "a-z A-Z |", "0-9"}
         * @return a list of separated NFAs created from the grammar file in param nfas.
         */
		void get_separated_nfas(vector<Nfa *> * nfas,vector<NfaToken> *nfa_tokens);
		Nfa* combine_nfa(Nfa *a, Nfa *b);
};


#endif //COMPILERS_NFABUILDER_H
