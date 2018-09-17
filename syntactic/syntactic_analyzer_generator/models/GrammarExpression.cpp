/* 
 * GrammarExpression.cpp
 * Created on: 4/20/18
 *     Author: marc
 */

#include "GrammarExpression.h"

GrammarExpression::GrammarExpression(GrammarElement* element) {
    this->belongs_to = static_cast<NonTerminal*> (element);
    this->eps = false;
}

void GrammarExpression::print_expression() {
    cout << "Expression : ";
    for (unsigned i = 0; i < expression.size(); i++) {
        cout << expression[i]->getName() << " ";
    }
    cout << endl;
    cout << "First : ";
    for (auto it = first_strings.begin(); it != first_strings.end(); it++) {
        cout << "{\"" << *it << "\"}" << ", ";
    }
    cout << endl;
    cout << "Belongs to : " << belongs_to->getName() << endl;
}

string GrammarExpression::getName() {
	string name = "";
	for (unsigned i = 0; i < this->expression.size(); i++) {
		name += this->expression[i]->getName();
		if (i != this->expression.size() - 1) {
			name += " ";
		}
	}
	return name;
}
