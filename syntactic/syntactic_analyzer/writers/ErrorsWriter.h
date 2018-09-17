/*
 * ErrorsWriter.h
 *
 *  Created on: Apr 17, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_SYNTACTIC_ANALYZER_WRITERS_ERRORSWRITER_H_
#define SYNTACTIC_SYNTACTIC_ANALYZER_WRITERS_ERRORSWRITER_H_

#include <ostream>
#include <vector>

using namespace std;

void write_errors(vector<string> *errors, ostream * outStream);


#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_WRITERS_ERRORSWRITER_H_ */
