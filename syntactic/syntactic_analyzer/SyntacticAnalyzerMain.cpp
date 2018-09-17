/*
 * SyntacticAnalyzerMain.cpp
 *
 *  Created on: Apr 27, 2018
 *      Author: amrnasr
 */


#include <iostream>
#include "SyntacticAnalyzer.h"
#include "../../utils/Utils.h"
#include "writers/DerivationsWriter.h"
#include "writers/ErrorsWriter.h"

using namespace std;

inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

int main () {
	SyntacticAnalyzer generator;
	cout << "Please enter the full filename/path of the transition table file you want to use..." << endl;
	string tb_name;
	cin >> tb_name;
	if (!ends_with(tb_name, ".trnstb")) {
		tb_name = tb_name + ".trnstb";
	}
	cout << "Please enter the full filename/path of the grammar table file you want to use..." << endl;
	string grm_tb_name;
	cin >> grm_tb_name;
	if (!ends_with(grm_tb_name, ".grmtb")) {
		grm_tb_name = grm_tb_name + ".grmtb";
	}
	cout << "Please enter the full filename/path of the source program you want to analyze..." << endl;
	string src_name;
	cin >> src_name;
	bool transitionTableRead = generator.read_transition_table(tb_name);
	if (!transitionTableRead) { // error reading transition table file
		cout << "Error reading transition table file!" << endl;
		return 0;
	}
	bool grammarTableRead = generator.read_grammar_table(grm_tb_name);
	if (!grammarTableRead) { // error reading grammar table file
		cout << "Error reading grammar table file!" << endl;
		return 0;
	}
	vector<string> errors;
	vector<vector<string>> derivations;
	bool sourceProgramRead = generator.analyze_program(src_name, &errors, &derivations);
	if (!sourceProgramRead) {
		cout << "Error reading source program file" << endl;
		return 0;
	}

	string errName = handle_file_name_extension(src_name, "err");
	string derName = handle_file_name_extension(src_name, "der");
	ofstream errStreamFile;
	errStreamFile.open(errName);
	if (!errStreamFile) {
		cout << "Error opening errors output file" << endl;
		return 0;
	}
	streambuf *buf1 = errStreamFile.rdbuf();
	ostream errOut(buf1);

	ofstream derStream;
	derStream.open(derName);
	if (!derStream) {
		cout << "Error opening derivations output file" << endl;
		return 0;
	}
	streambuf *buf2 = derStream.rdbuf();
	ostream derOut(buf2);
	write_errors(&errors, &errOut);
	write_derivations(&derivations, &derOut);
	return 0;
}
