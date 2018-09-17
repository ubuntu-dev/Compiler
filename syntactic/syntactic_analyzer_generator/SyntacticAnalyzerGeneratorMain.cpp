/*
 * SyntacticAnalyzerGeneratorMain.cpp
 *
 *  Created on: Apr 27, 2018
 *      Author: amrnasr
 */


#include "SyntacticAnalyzerGenerator.h"

int main() {
	SyntacticAnalyzerGenerator generator;
	cout << "Please enter the file/path of the grammar file you want to generate..." << endl;
	string file_name;
	cin >> file_name;
	generator.generate_syntactic_analyzer(file_name);
    return 0;
}

