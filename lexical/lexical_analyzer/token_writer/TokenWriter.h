/*
 * TokenWriter.h
 *
 *  Created on: Mar 23, 2018
 *      Author: amrnasr
 */

#ifndef LEXICAL_ANALYZER_TOKEN_WRITER_TOKENWRITER_H_
#define LEXICAL_ANALYZER_TOKEN_WRITER_TOKENWRITER_H_

#include <ostream>
#include <vector>
#include "../../../models/lexical/token.h"

void write_tokens(vector<Token> tokens, ostream * outStream);


#endif /* LEXICAL_ANALYZER_TOKEN_WRITER_TOKENWRITER_H_ */
