//
// Created by programajor on 4/18/18.
//

#include "GrammarElement.h"

GrammarElement::GrammarElement(string name, ElementType type) {
    this->name = name;
    this->type = type;
}

string GrammarElement::getName() {
    return this->name;
}

ElementType GrammarElement::getType() {
    return this->type;
}

void GrammarElement::setName(string name) {
    this->name = name;
}

void GrammarElement::setType(ElementType type) {
    this->type = type;
}
