/*
 * analyzerMain.cpp
 *
 *  Created on: Mar 24, 2018
 *      Author: amrnasr
 */

#include "tokens_generator/tokensGenerator.h"
#include <iostream>

using namespace std;

inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

int main () {
	TokensGenerator generator;
	cout << "Please enter the full filename/path of the transition table file you want to use..." << endl;
	string tb_name;
	cin >> tb_name;
	if (!ends_with(tb_name, ".trnstb")) {
		tb_name = tb_name + ".trnstb";
	}
	cout << "Please enter the full filename/path of the source program you want to analyze..." << endl;
	string src_name;
	cin >> src_name;
	generator.generateTokens(tb_name, src_name);
	return 0;
}

