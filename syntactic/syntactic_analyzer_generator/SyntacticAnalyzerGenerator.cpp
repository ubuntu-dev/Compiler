/*
 * SyntacticAnalyzerGenerator.cpp
 *
 *  Created on: Apr 26, 2018
 *      Author: amrnasr
 */


#include "SyntacticAnalyzerGenerator.h"
#include <fstream>
#include "../../utils/Utils.h"

void free_resources(vector<GrammarElement *> * rules, unordered_set<GrammarExpression *> *expressions,
		GrammarTable * table);
void print_rules(vector<GrammarElement *> *rules);
void SyntacticAnalyzerGenerator::generate_syntactic_analyzer(string file_name, bool print) {
	ifstream inFile;
	inFile.open(file_name);
	if (!inFile) {
		cout << "Unable to open file " << file_name << endl;
	}
	vector<GrammarElement *> rules;
	unordered_set<GrammarExpression *> expressions;
	unordered_set<string> terminals, nonterminals;
	GrammarElement * start;
	vector<string> errors = this->grammarParser.parse_grammar_file(&rules, &expressions, &inFile, &terminals,
			&nonterminals, &start);
	inFile.close();
	if (!errors.empty()) {
		cout << "Couldn't build syntactic analyzer! File format error :" << endl;
		for (unsigned i = 0; i < errors.size(); i++) {
			cout << errors[i] << endl;
		}
		free_resources(&rules, &expressions, nullptr);
		return;
	}
	this->firstCalculator.set_first_sets(&rules, &expressions);
	this->followCalculator.set_follow_sets(&rules, &expressions);
	unordered_set<NonTerminal *> changed;
	this->converter.left_factor(&rules, &expressions, &changed);
	if (changed.size() > 0) {
		this->firstCalculator.set_first_sets(&rules, &expressions);
		this->followCalculator.set_follow_sets(&rules, &expressions);
	}
	changed.clear();
	this->converter.remove_left_recursion(&rules,&expressions,&changed);
	if (changed.size() > 0) {
		this->firstCalculator.set_first_sets(&rules, &expressions);
		this->followCalculator.set_follow_sets(&rules, &expressions);
	}
	GrammarTable * table = this->tableBuilder.build_grammar_table(&rules, &errors);
	if (!errors.empty()) {
		cout << "Couldn't build syntactic analyzer! Table error :" << endl;
		for (unsigned i = 0; i < errors.size(); i++) {
			cout << errors[i] << endl;
		}
		free_resources(&rules, &expressions, table);
		return;
	}
	streambuf *buf;
	ofstream of, of2;
	string fileName = handle_file_name_extension(file_name, "grmtb");
	of.open(fileName);
	of2.open(add_prefix_to_file(fileName, "H_"));
	if (!of || !of2) {
		cout << "Couldn't write in output file \"" + handle_file_name_extension(file_name, "grmtb") + "\"" << endl;
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
			this->tableWriter.writeGrammarTableInHumanReadableFormat(table, &cons);
		}
		this->tableWriter.writeGrammarTableInHumanReadableFormat(table, &outFileH);
		this->tableWriter.writeGrammarTableInReadableForamt(table, &outFile);
	}
	free_resources(&rules, &expressions, table);
}

void print_rules(vector<GrammarElement *> *rules) {
	for (auto i = rules->begin(); i != rules->end(); i++) {
		if ((*i)->getType() == NON_TERMINAL) {
			NonTerminal * e =  static_cast<NonTerminal *>(*i);
			cout << e->getName() << endl;
			string fol1 = "{ ", fol2 = "{ ", fol3 = "{", fol4 = "{";
			unsigned j = 0;
			for (auto it = e->follow_strings.begin(); it != e->follow_strings.end(); it++) {
				fol1 += "\"";
				fol1 += *it;
				fol1 += "\"";
				if (j != e->follow_strings.size() - 1) {
					fol1 += " , ";
				}
				j++;
			}
			fol1 += " }";
			j = 0;
			for (auto it = e->first_strings.begin(); it != e->first_strings.end(); it++) {
				fol2 += "\"";
				fol2 += *it;
				fol2 += "\"";
				if (j != e->first_strings.size() - 1) {
					fol2 += " , ";
				}
				j++;
			}
			if (e->eps) {
				fol2 += " , \"eps\"";
			}
			fol2 += " }";
			j = 0;
			for (auto it = e->referenced_in.begin(); it != e->referenced_in.end(); it++) {
				fol3 += "\"";
				fol3 += (*it)->belongs_to->getName();
				fol3 += "\"";
				if (j != e->referenced_in.size() - 1) {
					fol3 += " , ";
				}
				j++;
			}
			fol3 += " }";
			j = 0;
			for (auto it = e->leads_to.begin(); it != e->leads_to.end(); it++) {
				fol4 += "\"";
				fol4 += (*it)->getName();
				fol4 += "\"";
				if (j != e->leads_to.size() - 1) {
					fol4 += " , ";
				}
				j++;
			}
			fol4 += " }";
			cout << "First : " << fol2 << endl;
			cout << "Follow : " << fol1 << endl;
			cout << "Referenced in : " << fol3 << endl;
			cout << "Leads to : " << fol4 << endl;
			cout << endl;
		}
	}
}

void free_resources(vector<GrammarElement *> * rules, unordered_set<GrammarExpression *> *expressions,
		GrammarTable * table) {
	for (auto i = rules->begin(); i != rules->end(); i++) {
			delete (*i);
		}
		for (auto i = expressions->begin(); i != expressions->end(); i++) {
			delete (*i);
		}
		if (table != nullptr) {
			delete table;
		}
}

