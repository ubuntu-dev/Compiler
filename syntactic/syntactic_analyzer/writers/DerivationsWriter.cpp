/*
 * DerivationsWriter.cpp
 *
 *  Created on: Apr 27, 2018
 *      Author: amrnasr
 */

#include "DerivationsWriter.h"

void write_derivations(vector<vector<string>> *derivations, ostream * outStream) {
	for (unsigned i = 0; i < derivations->size(); i++) {
		for (unsigned j = 0; j < (*derivations)[i].size(); j++) {
			(*outStream) << (*derivations)[i][j];
			if (j != (*derivations)[i].size() - 1) {
				(*outStream) << " ";
			}
		}
		(*outStream) << endl;
	}
}


