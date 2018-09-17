/*
 * StringUtils.h
 *
 *  Created on: Mar 23, 2018
 *      Author: amrnasr
 */

#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

#include <vector>
#include <string>

using namespace std;

vector<string> split_spaces(string str);
string handle_file_name_extension(string file_name, string ext);
string add_prefix_to_file(string filename, string prefix);
bool compare_streams(ifstream * if1, ifstream * if2, string filename);

#endif /* UTILS_UTILS_H_ */
