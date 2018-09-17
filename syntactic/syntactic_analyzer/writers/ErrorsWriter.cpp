/*
 * ErrorsWriter.cpp
 *
 *  Created on: Apr 27, 2018
 *      Author: amrnasr
 */


#include "ErrorsWriter.h"

void write_errors(vector<string> *errors, ostream * outStream) {
	for (unsigned i = 0; i < errors->size(); i++) {
		(*outStream) << (*errors)[i] << endl;
	}
}
