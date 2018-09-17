/*
 * GrammarElement.h
 *
 *  Created on: Apr 17, 2018
 *      Author: amrnasr
 */

#ifndef SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_GRAMMARELEMENT_H_
#define SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_GRAMMARELEMENT_H_

#include <string>
#include <vector>

using namespace std;


enum ElementType {TERMINAL, NON_TERMINAL};

class GrammarElement {

    public:
    GrammarElement(string name, ElementType type);
    string getName();
    ElementType getType();
    void setName(string name);
    void setType(ElementType type);

    private:
    string name;
    ElementType type;
};


#endif /* SYNTACTIC_SYNTACTIC_ANALYZER_GENERATOR_MODELS_GRAMMARELEMENT_H_ */
