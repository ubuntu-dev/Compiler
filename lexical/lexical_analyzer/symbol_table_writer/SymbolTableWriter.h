/*
 * SymbolTableWriter.h
 *
 *  Created on: Mar 23, 2018
 *      Author: amrnasr
 */

#ifndef LEXICAL_ANALYZER_SYMBOL_TABLE_WRITER_SYMBOLTABLEWRITER_H_
#define LEXICAL_ANALYZER_SYMBOL_TABLE_WRITER_SYMBOLTABLEWRITER_H_

#include <ostream>
#include <vector>
#include "../../../models/lexical/token.h"

using namespace std;

void write_symbol_table(vector<Token> tokens, ostream * outStream);


#endif /* LEXICAL_ANALYZER_SYMBOL_TABLE_WRITER_SYMBOLTABLEWRITER_H_ */
