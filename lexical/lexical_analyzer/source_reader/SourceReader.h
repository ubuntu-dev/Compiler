/*
 * SourceReader.h
 *
 *  Created on: Mar 23, 2018
 *      Author: amrnasr
 */

#ifndef LEXICAL_ANALYZER_SOURCE_READER_SOURCEREADER_H_
#define LEXICAL_ANALYZER_SOURCE_READER_SOURCEREADER_H_

#include <string>
#include <queue>

using namespace std;

bool read_source_file(queue<string> * prg, string file_name);


#endif /* LEXICAL_ANALYZER_SOURCE_READER_SOURCEREADER_H_ */
