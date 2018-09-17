/*
 * SourceReader.cpp
 *
 *  Created on: Mar 23, 2018
 *      Author: amrnasr
 */

#include "SourceReader.h"
#include <fstream>

#include "../../../utils/Utils.h"

bool read_source_file(queue<string> * prg, string file_name) {
	ifstream ifstr;
	ifstr.open(file_name);
	if (!ifstr) {
		return false;
	}
	string temp;
	while (getline(ifstr, temp)) {
		vector<string> words = split_spaces(temp);
		for (auto it = words.begin(); it != words.end(); it++) {
			prg->push(*it);
		}
	}
	return true;
}
