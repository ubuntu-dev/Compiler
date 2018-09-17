/*
 * generatorMain.cpp
 *
 *  Created on: Mar 24, 2018
 *      Author: amrnasr
 */

#include "lexicalAnalyzerGenerator.h"

int main() {
	LexicalAnalyzerGenerator generator;
	cout << "Please enter the file/path of the rules file you want to generate..." << endl;
	string file_name;
	cin >> file_name;
	generator.generate_lexical_analyzer(file_name);
    return 0;
}

