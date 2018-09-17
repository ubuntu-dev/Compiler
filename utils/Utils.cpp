/*
 * StringUtils.cpp
 *
 *  Created on: Mar 23, 2018
 *      Author: amrnasr
 */

#include "Utils.h"

#include <sstream>
#include <iostream>
#include <fstream>

vector<string> split_spaces(string str) {
	string buf;
	stringstream ss(str);
	vector<string> tokens;
	while (ss >> buf) {
		tokens.push_back(buf);
	}
	return tokens;
}

string handle_file_name_extension(string file_name, string ext) {
	if (file_name.size() > 3 && file_name.substr(file_name.size() - 4) == ".txt") {
		return (file_name.substr(0, file_name.size() - 4) + "." + ext);
	} else {
		return file_name + "." + ext;
	}
}

string add_prefix_to_file(string filename, string prefix) {
	size_t pos = filename.find_last_of('/');
	if (pos != string::npos) {
		return filename.substr(0, pos + 1) + prefix + filename.substr(pos + 1);
	} else {
		return prefix + filename;
	}
}

bool compare_streams(ifstream * if1, ifstream * if2, string filename) {
	string s1, s2;
	while (*if1 >> s1) {
		if (*if2 >> s2) {
			if (s1 != s2) {
				cout << "Error at "+ filename +" : Found : \"" + s1 + "\" Expected \"" << s2 << "\"" << endl;
				return false;
			}
		} else {
			cout << "Error at " + filename + " : Generated file is longer than the correct one." << endl;
			return false;
		}
	}
	if (*if2 >> s2) {
		cout << "Error at " + filename + " :  Generated file is shorter than the correct one." << endl;
		return false;
	}
	return true;
}
