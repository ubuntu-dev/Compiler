/*
 * TestGraphBuilder.cpp
 *
 *  Created on: Apr 23, 2018
 *      Author: amrnasr
 */

#include "TestGraph.h"
#include <unordered_map>

void build_lecture_example_1(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions,
		bool set_first, bool set_follow) {
		NonTerminal *e = new NonTerminal("E", NON_TERMINAL);
		NonTerminal *e1 = new NonTerminal("E'", NON_TERMINAL);
		NonTerminal *t = new NonTerminal("T", NON_TERMINAL);
		NonTerminal *t1 = new NonTerminal("T'", NON_TERMINAL);
		NonTerminal *f = new NonTerminal("F", NON_TERMINAL);
		GrammarElement *plus = new GrammarElement("+", TERMINAL);
		GrammarElement *mul = new GrammarElement("*", TERMINAL);
		GrammarElement *leftp = new GrammarElement("(", TERMINAL);
		GrammarElement *rightp = new GrammarElement(")", TERMINAL);
		GrammarElement *id = new GrammarElement("id", TERMINAL);
		// Add them to elements
		elements->push_back(e);
		elements->push_back(t);
		elements->push_back(e1);
		elements->push_back(plus);
		elements->push_back(f);
		elements->push_back(t1);
		elements->push_back(mul);
		elements->push_back(leftp);
		elements->push_back(rightp);
		elements->push_back(id);
		// Non terminals that go to eps.
		e1->eps = true;
		t1->eps = true;
		// Set expressions and add them to list.
		GrammarExpression *ex1 = new GrammarExpression(e);
		GrammarExpression *ex2 = new GrammarExpression(e1);
		GrammarExpression *ex3 = new GrammarExpression(t);
		GrammarExpression *ex4 = new GrammarExpression(t1);
		GrammarExpression *ex5 = new GrammarExpression(f);
		GrammarExpression *ex6 = new GrammarExpression(f);
		expressions->insert(ex1);
		expressions->insert(ex2);
		expressions->insert(ex3);
		expressions->insert(ex4);
		expressions->insert(ex5);
		expressions->insert(ex6);
		// Define expressions.
		ex1->expression.push_back(t);ex1->expression.push_back(e1);
		ex2->expression.push_back(plus);ex2->expression.push_back(t);ex2->expression.push_back(e1);
		ex3->expression.push_back(f);ex3->expression.push_back(t1);
		ex4->expression.push_back(mul);ex4->expression.push_back(f);ex4->expression.push_back(t1);
		ex5->expression.push_back(leftp);ex5->expression.push_back(e);ex5->expression.push_back(rightp);
		ex6->expression.push_back(id);
		// Add links to and from expressions.
		e->leads_to.push_back(ex1);
		e1->leads_to.push_back(ex2);
		t->leads_to.push_back(ex3);
		t1->leads_to.push_back(ex4);
		f->leads_to.push_back(ex5);
		f->leads_to.push_back(ex6);
		e->referenced_in.push_back(ex5);
		e1->referenced_in.push_back(ex1);
		e1->referenced_in.push_back(ex2);
		t->referenced_in.push_back(ex1);
		t->referenced_in.push_back(ex2);
		t1->referenced_in.push_back(ex3);
		t1->referenced_in.push_back(ex4);
		f->referenced_in.push_back(ex3);
		f->referenced_in.push_back(ex4);
		// Set first values.
		if (set_first) {
			unordered_set<string> s1 = {"(", "id"}, s2 = {"*"}, s3 = {"+"};
			e->first_strings = s1;
			e1->first_strings = s3;
			t->first_strings = s1;
			t1->first_strings = s2;
			f->first_strings = s1;
			ex1->first_strings = s1;
			ex2->first_strings = s3;
			ex3->first_strings = s1;
			ex4->first_strings = s2;
			ex5->first_strings = {"("};
			ex6->first_strings = {"id"};
		}
		if (set_follow) {
			e->follow_strings = {"$", ")"};
			e1->follow_strings = {"$", ")"};
			t->follow_strings = {"+", ")", "$"};
			t1->follow_strings = {"+", ")", "$"};
			f->follow_strings = {"+", "*", ")", "$"};
		}
}

void build_lecture_example_2(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions,
		bool set_first, bool set_follow) {
	NonTerminal * S = new NonTerminal("S", NON_TERMINAL);
	NonTerminal * E = new NonTerminal("E", NON_TERMINAL);
	NonTerminal * C = new NonTerminal("C", NON_TERMINAL);
	GrammarElement * i = new GrammarElement("i", TERMINAL);
	GrammarElement * t = new GrammarElement("t", TERMINAL);
	GrammarElement * a = new GrammarElement("a", TERMINAL);
	GrammarElement * e = new GrammarElement("e", TERMINAL);
	GrammarElement * b = new GrammarElement("b", TERMINAL);
	elements->push_back(S);elements->push_back(E);elements->push_back(C);elements->push_back(i);elements->push_back(t);
	elements->push_back(a);elements->push_back(e);elements->push_back(b);
	E->eps = true;

	GrammarExpression * ex1 = new GrammarExpression(S);
	GrammarExpression * ex2 = new GrammarExpression(S);
	GrammarExpression * ex3 = new GrammarExpression(E);
	GrammarExpression * ex4 = new GrammarExpression(C);
	expressions->insert(ex1);expressions->insert(ex2);expressions->insert(ex3);expressions->insert(ex4);

	ex1->expression.push_back(i);ex1->expression.push_back(C);ex1->expression.push_back(t);ex1->expression.push_back(S);
	ex1->expression.push_back(E);
	S->leads_to.push_back(ex1);S->referenced_in.push_back(ex1);C->referenced_in.push_back(ex1);E->referenced_in.push_back(ex1);

	ex2->expression.push_back(a);
	S->leads_to.push_back(ex2);

	ex3->expression.push_back(e);ex3->expression.push_back(S);
	E->leads_to.push_back(ex3);S->referenced_in.push_back(ex3);

	ex4->expression.push_back(b);
	C->leads_to.push_back(ex4);

	if (set_first) {
		S->first_strings = {"i", "a"};
		E->first_strings = {"e"};
		C->first_strings = {"b"};
		ex1->first_strings = {"i"};
		ex2->first_strings = {"a"};
		ex3->first_strings = {"e"};
		ex4->first_strings = {"b"};
	}
	if (set_follow) {
		S->follow_strings = {"$", "e"};
		E->follow_strings = {"$", "e"};
		C->follow_strings = {"t"};
	}
}

void build_lecture_example_3(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions,
		bool set_first, bool set_follow) {
	NonTerminal * S = new NonTerminal("S", NON_TERMINAL);
	NonTerminal * A = new NonTerminal("A", NON_TERMINAL);
	GrammarElement * c = new GrammarElement("c", TERMINAL);
	GrammarElement * d = new GrammarElement("d", TERMINAL);
	GrammarElement * a = new GrammarElement("a", TERMINAL);
	GrammarElement * e = new GrammarElement("e", TERMINAL);
	GrammarElement * b = new GrammarElement("b", TERMINAL);
	elements->push_back(S);elements->push_back(A);elements->push_back(c);elements->push_back(d);
	elements->push_back(a);elements->push_back(e);elements->push_back(b);
	S->eps = true;

	GrammarExpression * ex1 = new GrammarExpression(S);
	GrammarExpression * ex2 = new GrammarExpression(S);
	GrammarExpression * ex3 = new GrammarExpression(A);
	GrammarExpression * ex4 = new GrammarExpression(A);
	expressions->insert(ex1);expressions->insert(ex2);expressions->insert(ex3);expressions->insert(ex4);

	ex1->expression.push_back(A);ex1->expression.push_back(b);ex1->expression.push_back(S);
	S->leads_to.push_back(ex1);S->referenced_in.push_back(ex1);A->referenced_in.push_back(ex1);

	ex2->expression.push_back(e);
	S->leads_to.push_back(ex2);

	ex3->expression.push_back(a);
	A->leads_to.push_back(ex3);

	ex4->expression.push_back(c);
	ex4->expression.push_back(A);
	ex4->expression.push_back(d);
	A->leads_to.push_back(ex4);
	A->referenced_in.push_back(ex4);

	if (set_first) {
		S->first_strings = {"a", "c", "e"};
		A->first_strings = {"a", "c"};
		ex1->first_strings = {"a", "c"};
		ex2->first_strings = {"e"};
		ex3->first_strings = {"a"};
		ex4->first_strings = {"c"};
	}
	if (set_follow) {
		S->follow_strings = {"$"};
		A->follow_strings = {"b", "d"};
	}
}

void build_sheet_four_pro_two(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions,
		bool set_first, bool set_follow) {
	NonTerminal * e = new NonTerminal("E", NON_TERMINAL);
	NonTerminal * e1 = new NonTerminal("E'", NON_TERMINAL);
	NonTerminal * t = new NonTerminal("T", NON_TERMINAL);
	NonTerminal * t1 = new NonTerminal("T'", NON_TERMINAL);
	NonTerminal * f = new NonTerminal("F", NON_TERMINAL);
	NonTerminal * f1 = new NonTerminal("F'", NON_TERMINAL);
	NonTerminal * p = new NonTerminal("P", NON_TERMINAL);
	e1->eps = true;
	t1->eps = true;
	f1->eps = true;
	GrammarElement * plus = new GrammarElement("+", TERMINAL);
	GrammarElement * mul = new GrammarElement("*", TERMINAL);
	GrammarElement * leftp = new GrammarElement("(", TERMINAL);
	GrammarElement * rightp = new GrammarElement(")", TERMINAL);
	GrammarElement * a = new GrammarElement("a", TERMINAL);
	GrammarElement * b = new GrammarElement("b", TERMINAL);
	GrammarElement * em = new GrammarElement("Em", TERMINAL);

	elements->push_back(e);elements->push_back(e1);elements->push_back(t);elements->push_back(t1);elements->push_back(f);
	elements->push_back(f1);elements->push_back(p);elements->push_back(plus);elements->push_back(mul);elements->push_back(em);
	elements->push_back(leftp);elements->push_back(rightp);elements->push_back(a);elements->push_back(b);

	GrammarExpression * ex1 = new GrammarExpression(e);
	GrammarExpression * ex2 = new GrammarExpression(e1);
	GrammarExpression * ex3 = new GrammarExpression(t);
	GrammarExpression * ex4 = new GrammarExpression(t1);
	GrammarExpression * ex5 = new GrammarExpression(f);
	GrammarExpression * ex6 = new GrammarExpression(f1);
	GrammarExpression * ex7 = new GrammarExpression(p);
	GrammarExpression * ex8 = new GrammarExpression(p);
	GrammarExpression * ex9 = new GrammarExpression(p);
	GrammarExpression * ex10 = new GrammarExpression(p);

	expressions->insert(ex1);expressions->insert(ex2);expressions->insert(ex3);expressions->insert(ex4);
	expressions->insert(ex5);expressions->insert(ex6);expressions->insert(ex7);expressions->insert(ex8);
	expressions->insert(ex9);expressions->insert(ex10);

	ex1->expression.push_back(t);ex1->expression.push_back(e1);
	t->referenced_in.push_back(ex1);e1->referenced_in.push_back(ex1);
	e->leads_to.push_back(ex1);

	ex2->expression.push_back(plus);ex2->expression.push_back(e);
	e->referenced_in.push_back(ex2);e1->leads_to.push_back(ex2);

	ex3->expression.push_back(f);ex3->expression.push_back(t1);
	t->leads_to.push_back(ex3);f->referenced_in.push_back(ex3);t1->referenced_in.push_back(ex3);

	ex4->expression.push_back(t);
	t1->leads_to.push_back(ex4);t->referenced_in.push_back(ex4);

	ex5->expression.push_back(p);ex5->expression.push_back(f1);
	f->leads_to.push_back(ex5);p->referenced_in.push_back(ex5);f1->referenced_in.push_back(ex5);

	ex6->expression.push_back(mul);ex6->expression.push_back(f);
	f1->leads_to.push_back(ex6);f->referenced_in.push_back(ex6);

	ex7->expression.push_back(leftp);ex7->expression.push_back(e);ex7->expression.push_back(rightp);
	p->leads_to.push_back(ex7);e->referenced_in.push_back(ex7);

	ex8->expression.push_back(a);
	p->leads_to.push_back(ex8);

	ex9->expression.push_back(b);
	p->leads_to.push_back(ex9);

	ex10->expression.push_back(em);
	p->leads_to.push_back(ex10);

	if (set_first) {
		e->first_strings = {"(", "a", "b", "Em"};
		e1->first_strings = {"+"};
		t->first_strings = {"(", "a", "b", "Em"};
		t1->first_strings = {"(", "a","b","Em"};
		f->first_strings = {"(","a","b","Em"};
		f1->first_strings = {"*"};
		p->first_strings = {"(", "a", "b", "Em"};
		ex1->first_strings = t->first_strings;
		ex2->first_strings = {"+"};
		ex3->first_strings = f->first_strings;
		ex4->first_strings = t->first_strings;
		ex5->first_strings = p->first_strings;
		ex6->first_strings = {"*"};
		ex7->first_strings = {"("};
		ex8->first_strings = {"a"};
		ex9->first_strings = {"b"};
		ex10->first_strings = {"Em"};
	}
	if (set_follow) {
		e->follow_strings = {")", "$"};
		e1->follow_strings = {")", "$"};
		t->follow_strings = {"+", ")", "$"};
		t1->follow_strings = {"+", ")", "$"};
		f->follow_strings = {"a", "b", "Em", "(", "+", ")", "$"};
		f1->follow_strings = {"a", "b", "Em", "(", "+", ")", "$"};
		p->follow_strings = {"*", "a", "b", "Em", "(","+", ")", "$"};
	}
}

void build_pdf(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions,
		bool set_first, bool set_follow) {

}

bool compare_non_terminals(NonTerminal * t, NonTerminal * c, vector<string> * errors) {
	bool no_error = true;
	if (t->getName() != c->getName()) {
		errors->push_back("Error : Expected rule : \"" + c->getName() + "\" Found : \"" + t->getName() + "\"");
		no_error = false;
	}
	if (t->eps != c->eps) {
		errors->push_back("Error in rule \"" + c->getName() + "\" : Expected eps : "
				+ (c->eps?"True":"False") + " Found : " + (t->eps?"True":"False"));
		no_error = false;
	}
	if (t->first_strings != c->first_strings) {
		string first1 = "{ ", first2 = "{ ";
		unsigned i = 0;
		for (auto it = t->first_strings.begin(); it != t->first_strings.end(); it++) {
			first1 += "\"";
			first1 += *it;
			first1 += "\"";
			if (i != t->first_strings.size() - 1) {
				first1 += " , ";
			}
			i++;
		}
		first1 += " }";
		i = 0;
		for (auto it = c->first_strings.begin(); it != c->first_strings.end(); it++) {
			first2 += "\"";
			first2 += *it;
			first2 += "\"";
			if (i != c->first_strings.size() - 1) {
				first2 += " , ";
			}
			i++;
		}
		first2 += " }";
		errors->push_back("Error in rule \"" + c->getName() + "\" : \nExpected first : " + first2 + "\nFound : " + first1);
		no_error = false;
	}
	if (t->follow_strings != c->follow_strings) {
		string fol1 = "{ ", fol2 = "{ ";
		unsigned i = 0;
		for (auto it = t->follow_strings.begin(); it != t->follow_strings.end(); it++) {
			fol1 += "\"";
			fol1 += *it;
			fol1 += "\"";
			if (i != t->follow_strings.size() - 1) {
				fol1 += " , ";
			}
			i++;
		}
		fol1 += " }";
		i = 0;
		for (auto it = c->follow_strings.begin(); it != c->follow_strings.end(); it++) {
			fol2 += "\"";
			fol2 += *it;
			fol2 += "\"";
			if (i != c->follow_strings.size() - 1) {
				fol2 += " , ";
			}
			i++;
		}
		fol2 += " }";
		errors->push_back("Error in rule \"" + c->getName() + "\" : \nExpected Follow : " + fol2 + "\nFound : " + fol1);
		no_error = false;
	}
	return no_error;
}

bool compare_exp(GrammarExpression * e, GrammarExpression * c, vector<string> * errors) {
	bool no_error = true;
	if (e->getName() != c->getName()) {
		errors->push_back("Error : Expected expression : \"" + e->getName() + "\" Found : \"" + c->getName() + "\"");
		no_error = false;
	}
	if (e->eps != c->eps) {
		errors->push_back("Error in expression \"" + c->getName() + "\" : Expected eps : "
				+ (c->eps?"True":"False") + " Found : " + (e->eps?"True":"False"));
		no_error = false;
	}
	if (e->first_strings != c->first_strings) {
		string first1 = "{ ", first2 = "{ ";
		unsigned i = 0;
		for (auto it = e->first_strings.begin(); it != e->first_strings.end(); it++) {
			first1 += "\"";
			first1 += *it;
			first1 += "\"";
			if (i != e->first_strings.size() - 1) {
				first1 += " , ";
			}
			i++;
		}
		first1 += " }";
		i = 0;
		for (auto it = c->first_strings.begin(); it != c->first_strings.end(); it++) {
			first2 += "\"";
			first2 += *it;
			first2 += "\"";
			if (i != c->first_strings.size() - 1) {
				first2 += " , ";
			}
			i++;
		}
		first2 += " }";
		errors->push_back("Error in expression \"" + c->getName() + "\" : \nExpected first : " + first2 + "\nFound : " + first1);
		no_error = false;
	}
	return no_error;
}

void destroy_graph(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions) {
	for (unsigned i = 0; i < elements->size(); i++) {
		delete (*elements)[i];
	}
	for (auto it = expressions->begin(); it != expressions->end(); it++) {
		delete (*it);
	}
}

int test_graph_results(vector<GrammarElement *> * elements, unordered_set<GrammarExpression *> *expressions,
		vector<GrammarElement *> * c_elements, unordered_set<GrammarExpression *> *c_expressions, vector<string> * errors) {
	int errcnt = 0;
	if (elements->size() != c_elements->size()) {
		errors->push_back("Error : Expected number of grammar elements : " + to_string(c_elements->size()) + " found : " + to_string(elements->size()));
		errcnt++;
		return errcnt;
	}
	if (expressions->size() != c_expressions->size()) {
		errors->push_back("Error : Expected number of expressions : " + to_string(c_expressions->size()) + " found : " + to_string(expressions->size()));
		errcnt++;
		return errcnt;
	}
	unordered_map<string, GrammarExpression *> expmap;
	for (unsigned i = 0; i < elements->size(); i++) {
		if ((*elements)[i]->getType() == NON_TERMINAL && (*c_elements)[i]->getType() == NON_TERMINAL) {
			if (!compare_non_terminals(static_cast<NonTerminal *>((*elements)[i]),
					static_cast<NonTerminal *>((*c_elements)[i]), errors)) {
				errcnt++;
			}
		} else if ((*elements)[i]->getType() == TERMINAL && (*c_elements)[i]->getType() == TERMINAL) {
			if ((*elements)[i]->getName() != (*c_elements)[i]->getName()) {
				errors->push_back("Error : Expected Terminal : \"" + (*elements)[i]->getName() + "\" Found : \"" +
						(*c_elements)[i]->getName() +"\"");
				errcnt++;
			}
		} else {
			errors->push_back("Error : Mismatch between the types of the grammar elements in index " + i);
			errcnt++;
		}
	}
	for (auto it = expressions->begin(); it != expressions->end(); it++) {
		expmap.insert(pair<string, GrammarExpression *>((*it)->getName(), (*it)));
	}
	for (auto it = c_expressions->begin(); it != c_expressions->end(); it++) {
		if (!compare_exp(expmap[(*it)->getName()], *it, errors)) {
			errcnt++;
		}
	}
	return errcnt;
}

void print_errors(vector<string>  * errors) {
	for (unsigned i = 0; i < errors->size(); i++) {
		cout << (*errors)[i] << endl;
	}
	cout << "----------------------------------------------------------------------" << endl;
}
