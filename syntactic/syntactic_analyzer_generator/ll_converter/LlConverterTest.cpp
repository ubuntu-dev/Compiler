/*
 * LlConverterTest.cpp
 *
 *  Created on: Apr 18, 2018
 *      Author: amrnasr
 */
#include "../../../syntactic/syntactic_analyzer_generator/file_parser/GrammarFileParser.h"
#include "LlConverter.h"
#include "../../../syntactic/syntactic_analyzer_generator/models/GrammarExpression.h"
#include "../../../syntactic/syntactic_analyzer_generator/models/GrammarElement.h"
#include "../../../syntactic/syntactic_analyzer_generator/models/NonTerminal.h"
#include "../../../test_headers/p2_tests.h"
#include "../../../syntactic/syntactic_analyzer_generator/first_calculator/FirstCalculator.h"
#include "../../../syntactic/syntactic_analyzer_generator/follow_calculator/FollowCalculator.h"
void test_direct_left_recursion();
void test_indirect_left_recursion();
void test_direct_left_factoring();
void test_indirect_left_factoring();
void test_indirect_left_factoring_2();
void test_ll_converter() {
	test_direct_left_recursion();
	test_indirect_left_recursion();
	test_direct_left_factoring();
	test_indirect_left_factoring();
}

void test_direct_left_recursion() {
	GrammarElement* bterm = new NonTerminal("bterm", NON_TERMINAL);
	GrammarElement* bfactor = new NonTerminal("bfactor", NON_TERMINAL);
	GrammarElement* bexpr = new NonTerminal("bexpr", NON_TERMINAL);
	GrammarElement* oR = new GrammarElement("or", TERMINAL);
	GrammarElement* openBracket = new GrammarElement("(", TERMINAL);
	GrammarElement* closeBracket = new GrammarElement(")", TERMINAL);
	GrammarElement* aND = new GrammarElement("and", TERMINAL);
	GrammarElement* nOT = new GrammarElement("not", TERMINAL);
	GrammarElement* tRUE = new GrammarElement("true", TERMINAL);
	GrammarElement* fALSE = new GrammarElement("false", TERMINAL);
	// first rule
	GrammarExpression* exp11 = new GrammarExpression(bexpr);
	exp11->expression = { bexpr, oR, bterm };
	exp11->first_strings = { "not", "(", "true", "false" };
	GrammarExpression* exp12 = new GrammarExpression(bexpr);
	exp12->expression = { bterm };
	exp12->first_strings = { "not", "(", "true", "false" };
	static_cast<NonTerminal*>(bexpr)->referenced_in = {exp11 };
	static_cast<NonTerminal*>(bexpr)->leads_to = { exp11, exp12 };
	static_cast<NonTerminal*>(bexpr)->first_strings = { "not", "(", "true", "false" };
	static_cast<NonTerminal*>(bexpr)->follow_strings = { "$", ")"};
	// second rule
	GrammarExpression* exp21 = new GrammarExpression(bterm);
	exp21->expression = { bterm, aND, bfactor };
	exp21->first_strings = { "not", "(", "true", "false" };
	GrammarExpression* exp22 = new GrammarExpression(bterm);
	exp22->expression = { bfactor };
	exp22->first_strings = { "not", "(", "true", "false" };
	static_cast<NonTerminal*>(bterm)->referenced_in = { exp11, exp12, exp21 };
	static_cast<NonTerminal*>(bterm)->leads_to = { exp21, exp22 };
	static_cast<NonTerminal*>(bterm)->first_strings = { "not", "(", "true", "false" };
	static_cast<NonTerminal*>(bterm)->follow_strings = { "$", "or", ")"};
	//third rule
	GrammarExpression* exp31 = new GrammarExpression(bfactor);
	exp31->expression = { nOT, bfactor };
	exp31->first_strings = {"not"};
	GrammarExpression* exp32 = new GrammarExpression(bfactor);
	exp32->expression = { openBracket, bexpr, closeBracket };
	exp32->first_strings = {"("};
	GrammarExpression* exp33 = new GrammarExpression(bfactor);
	exp33->expression = { tRUE };
	exp33->first_strings = {"true"};
	GrammarExpression* exp34 = new GrammarExpression(bfactor);
	exp34->expression = { fALSE };
	exp34->first_strings = {"false"};
	static_cast<NonTerminal*>(bfactor)->referenced_in = { exp31, exp21, exp22 };
	static_cast<NonTerminal*>(bfactor)->leads_to = { exp31, exp32, exp33, exp34 };
	static_cast<NonTerminal*>(bfactor)->first_strings = { "not", "(", "true", "false" };
	static_cast<NonTerminal*>(bfactor)->follow_strings = { "$", "or", ")", "and" };

	vector <GrammarElement* > set = {bexpr, bterm, bfactor, nOT, aND, oR, closeBracket, openBracket, tRUE, fALSE };
	unordered_set <GrammarExpression*> set2 = {exp11, exp12, exp21, exp22, exp31, exp32, exp33, exp34};
	unordered_set <NonTerminal*> changed;
	LlConverter converter;
	converter.left_factor(&set, &set2, &changed);
	converter.remove_left_recursion(&set, &set2, &changed);
	// if pass integration test passed

	if (set[0]->getName() == "bexpr") {
		NonTerminal * temp = static_cast<NonTerminal *>(set[0]);
		if (temp->leads_to[0]->expression[0] != set[1]) {
			cout << "Error in Left recursion" << "Expected reference to \" bterm \" " <<endl;
		}
		if (temp->leads_to[0]->expression[1] != set[10]) {
			cout << "Error in Left recursion" << "Expected reference to \" bterm \" " <<endl;
		}
	} else {
		cout << "Error in Referencing sets" << endl;
	}
	cout << "Eliminating direct left recursion success..." << endl;
	delete bexpr;
	delete bterm;
	delete bfactor;
	delete oR;
	delete openBracket;
	delete closeBracket;
	delete aND;
	delete nOT;
	delete tRUE;
	delete fALSE;
}
void test_indirect_left_recursion() {
	NonTerminal* a = new NonTerminal("A", NON_TERMINAL);
	NonTerminal* b = new NonTerminal("B", NON_TERMINAL);
	NonTerminal* c = new NonTerminal("C", NON_TERMINAL);
	NonTerminal* d = new NonTerminal("D", NON_TERMINAL);

	GrammarElement* x = new GrammarElement("x", TERMINAL);
	GrammarElement* y = new GrammarElement("y", TERMINAL);
	GrammarElement* cS = new GrammarElement("c", TERMINAL);
	GrammarElement* dS = new GrammarElement("d", TERMINAL);

	GrammarExpression* exp11 = new GrammarExpression(a);
	exp11->expression = { b, x, y};
	b->referenced_in.push_back(exp11);
	GrammarExpression* exp12 = new GrammarExpression(a);
	exp12->expression = { x };
	GrammarExpression* exp21 = new GrammarExpression(b);
	exp21->expression = { c, d};
	d->referenced_in.push_back(exp21);
	c->referenced_in.push_back(exp21);
	GrammarExpression* exp31 = new GrammarExpression(c);
	exp31->expression = { a };
	a->referenced_in.push_back(exp31);
	GrammarExpression* exp32 = new GrammarExpression(c);
	exp32->expression = { cS };
	GrammarExpression* exp41 = new GrammarExpression(d);
	exp41->expression = { dS };
	a->leads_to = { exp11, exp12};
	b->leads_to = { exp21 };
	c->leads_to = { exp31, exp32 };
	d->leads_to = { exp41 };

	vector <GrammarElement* > set = {a, b, c, d, x, y, cS, dS};
	unordered_set <GrammarExpression*> set2 = {exp11, exp12, exp21, exp31, exp32, exp41};
	unordered_set <NonTerminal*> changed;
	LlConverter converter;
	converter.left_factor(&set, &set2, &changed);
	converter.remove_left_recursion(&set, &set2, &changed);
	NonTerminal * ele =  static_cast<NonTerminal *> (set[8]);
	NonTerminal * ele1 =  static_cast<NonTerminal *> (set[2]);
	if (ele->getName() == "C'" ) {
		if (ele->leads_to.size() == 1) {
			if (ele->eps) {
				if (ele->leads_to[0]->belongs_to == ele) {
					if (ele->leads_to[0]->expression.size() == 4) {
						if (ele->leads_to[0]->expression[3] == ele) {
							if (ele->referenced_in.size() == 3) {
								if (ele->referenced_in[0]->belongs_to == c ||
									ele->referenced_in[0]->belongs_to == c ||
									ele->referenced_in[0]->belongs_to == ele) {
									if (ele->referenced_in[1]->belongs_to == c ||
										ele->referenced_in[1]->belongs_to == c ||
										ele->referenced_in[1]->belongs_to == ele) {
										if (ele->referenced_in[2]->belongs_to == c ||
											ele->referenced_in[2]->belongs_to == c ||
											ele->referenced_in[2]->belongs_to == ele) {
											if ( ele1->leads_to.size() == 2) {
												if (ele1->leads_to[1]->expression[0] == x &&
													ele1->leads_to[1]->expression[1] == ele) {
													if (ele1->leads_to[0]->expression[0] == cS &&
														ele1->leads_to[0]->expression[1] == ele) {
														if (ele1->referenced_in.size() == 1 &&
															ele1->referenced_in[0] == exp21	) {
															cout << "Eliminating indirect left recursion success..." << endl;
														} else {
															cout << "Error in indirect left recursion" << endl;
														}

													} else {
														cout << "Error in indirect left recursion" << endl;
													}
												} else {
													cout << "Error in indirect left recursion" << endl;
												}
											} else {
												cout << "Error in indirect left recursion" << endl;
											}
										} else {
											cout << "Error in indirect left recursion" << endl;
										}
									} else {
										cout << "Error in indirect left recursion" << endl;
									}
								} else {
									cout << "Error in indirect left recursion" << endl;
								}
							} else {
								cout << "Error in indirect left recursion" << endl;
							}
						} else {
							cout << "Error in indirect left recursion" << endl;
						}
					} else {
						cout << "Error in indirect left recursion" << endl;
					}
				} else {
					cout << "Error in indirect left recursion" << endl;
				}
			} else {
				cout << "Error in indirect left recursion" << endl;
			}
		} else {
			cout << "Error in indirect left recursion" << endl;
		}
	} else {
		cout << "Error in indirect left recursion" << endl;
	}
	delete a;
	delete b;
	delete c;
	delete d;
	delete x;
	delete y;
	delete cS;
	delete dS;
}

void test_direct_left_factoring() {
	NonTerminal* a = new NonTerminal("A", NON_TERMINAL);
	NonTerminal* b = new NonTerminal("B", NON_TERMINAL);
	GrammarElement* aS = new GrammarElement("a", TERMINAL);
	GrammarElement* bS = new GrammarElement("b", TERMINAL);
	GrammarElement* cS = new GrammarElement("c", TERMINAL);
	GrammarElement* dS = new GrammarElement("d", TERMINAL);
	GrammarElement* gS = new GrammarElement("g", TERMINAL);
	GrammarElement* eS = new GrammarElement("e", TERMINAL);
	GrammarElement* fS = new GrammarElement("f", TERMINAL);

	GrammarExpression* exp11 = new GrammarExpression(a);
	exp11->expression = { aS, bS, b };
	GrammarExpression* exp12 = new GrammarExpression(a);
	exp12->expression = { aS, b };
	GrammarExpression* exp13 = new GrammarExpression(a);
	exp13->expression = { cS, dS, gS };
	GrammarExpression* exp14 = new GrammarExpression(a);
	exp14->expression = { cS, dS, eS, b };
	GrammarExpression* exp15 = new GrammarExpression(a);
	exp15->expression = { cS, dS, fS, b };
	vector <GrammarElement* > set = {a};
	unordered_set <GrammarExpression*> set2 = {exp11, exp12, exp13, exp14, exp15};
	a->leads_to = { exp11, exp12, exp13, exp14, exp15 };
	b->referenced_in = { exp11, exp12, exp14, exp15 };
	a->first_strings = { "a", "c" };
	unordered_set <NonTerminal*> set3;
	LlConverter converter;
	converter.remove_left_recursion(&set, &set2, &set3);
	converter.left_factor(&set, &set2, &set3);
	NonTerminal * ele0 =  static_cast<NonTerminal *> (set[0]);
	NonTerminal * ele =  static_cast<NonTerminal *> (set[1]);
	NonTerminal * ele2 =  static_cast<NonTerminal *> (set[2]);
	if (set.size() == 3) {
		if (set2.size() == 7) {
			if (ele->getName() == "A_1") {
				if (ele->getType() == NON_TERMINAL) {
					if (ele2->leads_to[0]->expression[0] == bS ||
							ele2->leads_to[0]->expression[0] == b) {
						if (ele2->leads_to[1]->expression[0] == bS ||
							ele2->leads_to[1]->expression[0] == b) {
							if (ele2->leads_to.size() == 2) {
								if (ele2->leads_to[0]->belongs_to == ele2 &&
									ele2->leads_to[0]->belongs_to == ele2) {
									if (ele2->referenced_in[0] == ele0->leads_to[0] ||
										ele2->referenced_in[0] == ele0->leads_to[1]	) {
										if (ele->leads_to.size() == 3) {
											if (ele->leads_to[0]->expression[0] == gS ||
												ele->leads_to[0]->expression[0] == eS ||
												ele->leads_to[0]->expression[0] == fS) {
												if (ele->leads_to[1]->expression[0] == gS ||
													ele->leads_to[1]->expression[0] == eS ||
													ele->leads_to[1]->expression[0] == fS) {
													if (ele->referenced_in[0] == ele0->leads_to[0] ||
														ele->referenced_in[0] == ele0->leads_to[1]) {
														if (ele2->getName() == "A_2") {
															cout << "Direct left factoring Success..." << endl;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	delete a;
	delete b;
	delete aS;
	delete bS;
	delete cS;
	delete dS;
	delete eS;
	delete fS;
	delete gS;
}


void test_indirect_left_factoring(){
	NonTerminal* l = new NonTerminal("L", NON_TERMINAL);
	NonTerminal* s = new NonTerminal("S", NON_TERMINAL);
	NonTerminal* a = new NonTerminal("A", NON_TERMINAL);
	NonTerminal* c = new NonTerminal("C", NON_TERMINAL);
	NonTerminal* e = new NonTerminal("E", NON_TERMINAL);
	GrammarElement* semi_colon = new GrammarElement(";", TERMINAL);
	GrammarElement* openBracket = new GrammarElement("(", TERMINAL);
	GrammarElement* closeBracket = new GrammarElement(")", TERMINAL);
	GrammarElement* id = new GrammarElement("id", TERMINAL);
	GrammarElement* equal = new GrammarElement("=", TERMINAL);
	GrammarElement* num = new GrammarElement("num", TERMINAL);
	GrammarExpression* exp11 = new GrammarExpression(l);
	exp11->expression = { l, semi_colon, s };
	exp11->first_strings = { "id" };
	GrammarExpression* exp12 = new GrammarExpression(l);
	exp12->expression = { s };
	exp12->first_strings = { "id" };
	GrammarExpression* exp21 = new GrammarExpression(s);
	exp21->expression = { a };
	exp21->first_strings = { "id" };
	GrammarExpression* exp22 = new GrammarExpression(s);
	exp22->expression = { c };
	exp22->first_strings = { "id" };
	GrammarExpression* exp31 = new GrammarExpression(a);
	exp31->expression = { id, equal, e };
	exp31->first_strings = { "id" };
	GrammarExpression* exp41 = new GrammarExpression(c);
	exp41->expression = { id, openBracket, e, closeBracket };
	exp41->first_strings = { "id" };
	GrammarExpression* exp51 = new GrammarExpression(e);
	exp51->expression = { id };
	exp51->first_strings = { "id" };
	GrammarExpression* exp52 = new GrammarExpression(e);
	exp52->expression = { num };
	exp52->first_strings = { "num" };
	l->referenced_in = { exp11 };
	l->leads_to = { exp11, exp12 };
	l->first_strings = { "id" };
	s->referenced_in = { exp12, exp11 };
	s->leads_to = { exp21, exp22 };
	s->first_strings = { "id" };
	a->referenced_in = { exp21 };
	a->leads_to = { exp31 };
	a->first_strings = { "id" };
	c->referenced_in = { exp22 };
	c->leads_to = { exp41 };
	c->first_strings = { "id" };
	e->referenced_in = { exp31, exp41 };
	e->leads_to = {exp51, exp52 };
	e->first_strings = { "id", "num" };

	vector <GrammarElement* > set = {l, s, a, c, e, semi_colon, openBracket, closeBracket, equal, num, id};
	unordered_set <GrammarExpression*> set2 = {exp11, exp12, exp21, exp22, exp31, exp41, exp51, exp52};
	unordered_set <NonTerminal*> set3;
	LlConverter converter;
	converter.left_factor(&set, &set2, &set3);
	if (set.size() == 12) {
		if (set2.size() == 9) {
				test_indirect_left_factoring_2();
		}
	}


}

void test_indirect_left_factoring_2() {
	NonTerminal* a = new NonTerminal("A", NON_TERMINAL);
	NonTerminal* b = new NonTerminal("B", NON_TERMINAL);
	NonTerminal* c = new NonTerminal("C", NON_TERMINAL);
	NonTerminal* d = new NonTerminal("D", NON_TERMINAL);
	NonTerminal* e = new NonTerminal("E", NON_TERMINAL);
	NonTerminal* f = new NonTerminal("F", NON_TERMINAL);

	GrammarElement* bS = new GrammarElement("b", TERMINAL);
	GrammarElement* eS = new GrammarElement("e", TERMINAL);
	GrammarElement* cS = new GrammarElement("c", TERMINAL);
	GrammarElement* dS = new GrammarElement("d", TERMINAL);
	GrammarElement* aS = new GrammarElement("a", TERMINAL);
	GrammarElement* fS = new GrammarElement("f", TERMINAL);

	GrammarExpression* exp11 = new GrammarExpression(a);
	exp11->expression = { b, c };
	exp11->first_strings = { "b" };
	GrammarExpression* exp12 = new GrammarExpression(a);
	exp12->expression = { d };
	exp12->first_strings = { "b" };
	GrammarExpression* exp13 = new GrammarExpression(a);
	exp13->expression = { bS, cS };
	exp13->first_strings = { "b" };
	GrammarExpression* exp14 = new GrammarExpression(a);
	exp14->expression = { eS, fS };
	exp14->first_strings = { "e" };
	GrammarExpression* exp21 = new GrammarExpression(b);
	exp21->expression = { bS, cS };
	exp21->first_strings = { "b" };
	GrammarExpression* exp31 = new GrammarExpression(c);
	exp31->expression = { dS, eS, e };
	exp31->first_strings = { "d" };
	GrammarExpression* exp41 = new GrammarExpression(d);
	exp41->expression = { bS, cS, dS, eS, f };
	exp41->first_strings = { "b" };
	GrammarExpression* exp51 = new GrammarExpression(e);
	exp51->expression = { aS, bS };
	exp51->first_strings = { "a" };
	GrammarExpression* exp61 = new GrammarExpression(f);
	exp61->expression = { aS, cS };
	exp61->first_strings = { "a" };

	a->leads_to = { exp11, exp12, exp13, exp14 };
	b->leads_to = { exp21 };
	c->leads_to = { exp31 };
	d->leads_to = { exp41 };
	e->leads_to = { exp51 };
	f->leads_to = { exp61 };
	a->first_strings = { "b" , "e" };
	b->referenced_in = { exp11 };
	b->first_strings = { "b" };
	c->referenced_in = { exp11 };
	c->first_strings = { "d" };
	d->referenced_in = { exp12 };
	d->first_strings = { "b" };
	e->referenced_in = { exp31 };
	e->first_strings = { "a" };
	f->referenced_in = { exp41 };
	f->first_strings = { "a" };

	vector <GrammarElement* > set = {a, b, c, d, e, f, aS, bS, cS, dS, eS, fS};
	unordered_set <GrammarExpression*> set2 = {exp11, exp12, exp13, exp14, exp21, exp31, exp41, exp51, exp61};
	unordered_set <NonTerminal*> set3;
	LlConverter converter;
	converter.remove_left_recursion(&set, &set2, &set3);
	converter.left_factor(&set, &set2, &set3);

	NonTerminal * ele12 =  static_cast<NonTerminal *> (set[12]);
	NonTerminal * ele13 =  static_cast<NonTerminal *> (set[13]);
	NonTerminal * ele14 =  static_cast<NonTerminal *> (set[14]);
	NonTerminal * ele0 =  static_cast<NonTerminal *> (set[0]);

	if (set.size() == 15) {
		if (ele12->eps) {
			if (ele12->leads_to.size() == 1) {
				if (ele12->leads_to[0]->expression[0] == dS) {
					if (ele12->referenced_in[0] == ele0->leads_to[0] ||
						ele12->referenced_in[0] == ele0->leads_to[1]) {
						if (ele13->referenced_in[0] == ele12->leads_to[0] &&
							ele14->referenced_in[0] == ele13->leads_to[0]) {
							if (ele14->leads_to[0]->expression[0] == bS ||
								ele14->leads_to[0]->expression[0] == cS	) {
								if (ele13->leads_to[0]->expression[0] == aS &&
									ele13->leads_to[0]->expression[1] == ele14) {
									if (ele12->leads_to[0]->expression[2] == ele13 &&
										ele12->leads_to[0]->expression[1] == eS) {
										if (set2.size() == 11) {
											if (ele12->getType() == NON_TERMINAL &&
												ele13->getType() == NON_TERMINAL &&
												ele14->getType() == NON_TERMINAL)
											cout << "Nested left factoring success..." << endl;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	delete a;
	delete b;
	delete c;
	delete d;
	delete e;
	delete f;
	delete aS;
	delete bS;
	delete cS;
	delete dS;
	delete eS;
	delete fS;
}



