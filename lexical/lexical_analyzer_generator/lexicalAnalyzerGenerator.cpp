/*
 * lexicalAnalyzerGenerator.cpp
 *
 *  Created on: Mar 21, 2018
 *      Author: amrnasr
 */
#include "lexicalAnalyzerGenerator.h"
#include <fstream>

#include "../../utils/Utils.h"

using namespace std;

void LexicalAnalyzerGenerator::generate_lexical_analyzer(string file_name, bool print) {
	ifstream inFile;
	inFile.open(file_name);
	if (!inFile) {
	    cout << "Unable to open file " << file_name << endl;
	}
	vector<NfaToken> tokens;
	vector<string> priority;
	set<char> alpha;
	vector<string> errors = this->grammarParser.parse_lexical_file(&tokens, &priority, &inFile, &alpha);
	inFile.close();
	if (!errors.empty()) {
		cout << "Couldn't build lexical analyzer! File format error :" << endl;
		for (unsigned i = 0; i < errors.size(); i++) {
			cout << errors[i] << endl;
		}
	}
	vector<Nfa *> nfas;
	this->builder.get_separated_nfas(&nfas, &tokens);
	Node * startNode = this->combiner.getCombinedNfa(&nfas);
	DfaNode * dfaStartNode = this->converter.getNonMinimizedDFA(startNode, &priority, &alpha);
	vector<DfaNode *> finalMachine;
	this->minimzer.getMinimizedDFA(&finalMachine, dfaStartNode, &priority);
	TransitionTable table = this->tableBuilder.buildTransitionTable(finalMachine, &alpha);
	streambuf *buf;
	ofstream of, of2;
	string fileName = handle_file_name_extension(file_name, "trnstb");
	of.open(fileName);
	of2.open(add_prefix_to_file(fileName, "H_"));
	if (!of || !of2) {
		cout << "Couldn't write in output file \"" + handle_file_name_extension(file_name, "trnstb") + "\"" << endl;
	} else {
		buf = of.rdbuf();
		ostream outFile(buf);
		streambuf *cbuf;
		cbuf = cout.rdbuf();
		ostream cons (cbuf);
		streambuf *f2buf;
		f2buf = of2.rdbuf();
		ostream outFileH(f2buf);
		if (print) {
			this->tableWriter.writeTransitionTableInHumanReadableFormat(table, &cons);
		}
		this->tableWriter.writeTransitionTableInHumanReadableFormat(table, &outFileH);
		this->tableWriter.writeTransitionTableInReadableForamt(table, &outFile);
	}
	vector<DfaNode *> rem_nodes = table.getNodes();
	for (auto i = rem_nodes.begin(); i != rem_nodes.end(); i++) {
		delete (*i);
	}
}
