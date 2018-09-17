/*
 * GrammarTableReader.h
 *
 *  Created on: Apr 17, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_GRAMMAR_TABLE_READER_GRAMMARTABLEREADER_H_
#define SYNTACTIC_GRAMMAR_TABLE_READER_GRAMMARTABLEREADER_H_

#include <fstream>
#include "../model/GrammarTable.h"

class GrammarTableReader {
	public:
    	GrammarTable *readGrammarTable(ifstream* stream);
};



#endif /* SYNTACTIC_GRAMMAR_TABLE_READER_GRAMMARTABLEREADER_H_ */
