/*
 * DerivationsWriter.h
 *
 *  Created on: Apr 17, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_SYNTACTIC_ANALYZER_WRITERS_DERIVATIONSWRITER_H_
#define SYNTACTIC_SYNTACTIC_ANALYZER_WRITERS_DERIVATIONSWRITER_H_

#include <ostream>
#include <vector>

using namespace std;

void write_derivations(vector<vector<string>> *derivations, ostream * outStream);



#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_WRITERS_DERIVATIONSWRITER_H_ */
