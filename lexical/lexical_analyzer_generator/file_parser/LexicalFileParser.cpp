/*
 * GrammerParser.cpp
 *
 *  Created on: Mar 19, 2018
 *      Author: amrnasr
 */
#include "LexicalFileParser.h"

#include "../models/NfaToken.h"
#include <map>
#include <regex>
#include <stack>
#include <list>
#include <set>

#include "../../../utils/Utils.h"

const regex LexicalFileParser::regDefRegex = regex("\\s*([A-Za-z][A-Za-z0-9_]*)\\s*=\\s*(.*)$");
const regex LexicalFileParser::regExpRegex = regex("\\s*([A-Za-z][A-Za-z0-9_]*)\\s*:\\s*(.*)$");
const regex LexicalFileParser::keyWordRegex = regex("\\s*\\{((?:\\s*[^\\s]*\\s*)*)}\\s*");
const regex LexicalFileParser::punctRegex = regex("\\s*\\[((?:\\s*[^\\s]*\\s*)*)]\\s*");

string filter_string(string str);
bool isReservedSymbol(char c);
bool escapeReserved(string str, bool regOps, vector<string> *errors, unsigned line_n);
vector<MiniToken> regular_expression_split(string str, map<string, vector<MiniToken>> mapOfDefinitions, set<char> * alphabet);
vector<MiniToken> regular_expression_postfix(vector<MiniToken> regexp, bool * error,  vector<string> *errors, unsigned line_n);
bool valid_postfix(vector<MiniToken> tokens, vector<string>* errors, unsigned line_n);
bool is_operation_char(char c);
char nonspacechar_before(string str, unsigned i);
char nonspacechar_after(string str, unsigned i);
bool is_parenthesis(char c);
void add_error(unsigned line_n, string error, vector<string> *errors);
void add_to_alphabet(set<char> * alphabet, MiniToken *token);

void add_to_alphabet(set<char> * alphabet, MiniToken *token) {
	if (token->type == CHAR_GROUP) {
		char strt = token->tok[0];
		char endt = token->tok[2];
		for (char i = strt; i <= endt; i++) {
			alphabet->insert(i);
		}
	} else if (token->type == WORD) {
		string str = token->tok;
		for (unsigned i = 0; i < str.size(); i++) {
			alphabet->insert(str.at(i));
		}
	}
}

vector<string> LexicalFileParser::parse_lexical_file(vector<NfaToken> *result, vector<string> *priorities, ifstream * grammar_stream, set<char> *alphabet) {
	string line;
	vector<string> errors;
	map<string, vector<MiniToken>> mapOfDefinitions;
	vector<string> punctPr, keyPr, regPr;
	if (grammar_stream->is_open()) {
		unsigned line_number = 0;
		while (getline (*grammar_stream,line) ) {
			line_number++;
			if (line.empty()) {
				continue;
			}
			if (regex_match(line, punctRegex)) {
				smatch sm;
				regex_search(line,sm,punctRegex);
				if (!escapeReserved(sm[1], false, &errors, line_number)) {
					continue;
				} else {
					string filtered = filter_string(sm[1]);
					vector<string> tokens = split_spaces(filtered);
					for (unsigned i = 0; i < tokens.size(); i++) {
						NfaToken token (PUNCTUATION, tokens[i]);
						MiniToken mtoken (WORD, tokens[i]);
						add_to_alphabet(alphabet, &mtoken);
						token.tokens.push_back(mtoken);
						punctPr.push_back(token.tokenName);
						result->push_back(token);
					}
				}
			} else if (regex_match(line, keyWordRegex)) {
				smatch sm;
				regex_search(line,sm,keyWordRegex);
				if (!escapeReserved(sm[1], false, &errors, line_number)) {
					continue;
				} else {
					string filtered = filter_string(sm[1]);
					vector<string> tokens = split_spaces(filtered);
					for (unsigned i = 0; i < tokens.size(); i++) {
						NfaToken token (KEYWORD, tokens[i]);
						MiniToken mtoken (WORD, tokens[i]);
						add_to_alphabet(alphabet, &mtoken);
						token.tokens.push_back(mtoken);
						keyPr.push_back(token.tokenName);
						result->push_back(token);
					}
				}
			} else if (regex_match(line, regDefRegex)) {
				smatch sm;
				regex_search(line,sm,regDefRegex);
				string tokenName = sm[1];
				string tokenRegex = sm[2];
				if (!escapeReserved(tokenRegex, true, &errors, line_number)) {
					continue;
				} else {
					vector<MiniToken> tokens = regular_expression_split(tokenRegex, mapOfDefinitions, alphabet);
					bool error = false;
					regular_expression_postfix(tokens, &error, &errors, line_number);
					if (error) {
						continue;
					} else {
						mapOfDefinitions.insert(make_pair(tokenName, tokens));
					}
				}
			} else if (regex_match(line, regExpRegex)) {
				smatch sm;
				regex_search(line,sm,regExpRegex);
				string tokenName = sm[1];
				string tokenRegex = sm[2];
				if (!escapeReserved(tokenRegex, true, &errors, line_number)) {
					continue;
				} else {
					bool error = false;
					vector<MiniToken> tokens = regular_expression_postfix(regular_expression_split(tokenRegex, mapOfDefinitions, alphabet), &error, &errors, line_number);
					if (error) {
						continue;
					}
					NfaToken token(REGULAR_EXPRESSION, tokenName);
					for (unsigned i = 0; i < tokens.size(); i++) {
						token.tokens.push_back(tokens[i]);
					}
					regPr.push_back(token.tokenName);
					result->push_back(token);
				}
			} else {
				add_error(line_number, "Undefined Line Type.", &errors);
				continue;
			}
		}
		if (result->size() == 0) {
			add_error(line_number, "Empty file...", &errors);
		}
	}
	if (errors.empty()) {
		for (unsigned i = 0; i < punctPr.size(); i++) {
			priorities->push_back(punctPr[i]);
		}
		for (unsigned i = 0; i < keyPr.size(); i++) {
			priorities->push_back(keyPr[i]);
		}
		for (unsigned i = 0; i < regPr.size(); i++) {
			priorities->push_back(regPr[i]);
		}
	}
	return errors;
}

string filter_string(string str) {
	string res= "";
	for (unsigned i = 0; i < str.size(); i++) {
		if (str.at(i) == '\\' && i < str.size() - 1 && isReservedSymbol(str.at(i+1))) {
			i++;
		}
		res += str.at(i);
	}
	return res;
}

bool escapeReserved(string str, bool regOps, vector<string> *errors, unsigned int line_n) {
	bool noError = true;
	for (unsigned i = 0; i < str.size(); i++) {
		if (isReservedSymbol(str.at(i)) && i > 0 && str.at(i-1) != '\\') {
			if (regOps) {
				if (str.at(i) == '=' || str.at(i) == ':') {
					if (i > 1) {
						add_error(line_n,
							string("Reserved char ") + str.at(i) + " at position " + to_string(i) + " in \"" + str.substr(i - 2, i + 2) + "\". Please use \\" + str.at(i) + " instead.",
							errors);
					} else {
						add_error(line_n,
							string("Reserved char ") + str.at(i) + " at position " + to_string(i) + " in \"" + str.substr(i - 1, i + 3) + "\". Please use \\" + str.at(i) + " instead.",
							errors);
					}
					noError = false;
				}
				if (str.at(i) == '-') {
					char bf = nonspacechar_before(str, i - 1);
					char af = nonspacechar_after(str, i + 1);
					if (af == '\0' || bf == '\0' || isReservedSymbol(af)) {
						string reason = isReservedSymbol(af) ? "Found reserved charcter after it.":af == '\0'? "Missing character after range":"Missing character before range";
						if (i > 1) {
							add_error(line_n,
								"Range operation error at position " + to_string(i) + " in \"" + str.substr(i - 2, i + 2) + "\". Range need two valid characters before and after it. " + reason,
								errors);
						} else {
							add_error(line_n,
								"Range operation error at position " + to_string(i) + " in \"" + str.substr(i, i + 4) + "\". Range need two valid characters before and after it. " + reason,
								errors);
						}
						noError = false;
					} else if (isReservedSymbol(bf)) {
						int j = i - 1;
						while (j >= 0 && isspace(str.at(j))) {
							j--;
						}
						if (j < 1 || str.at(j - 1) != '\\') {
							if (i > 1) {
								add_error(line_n,
									"Range operation error at position " + to_string(i) + " in \"" + str.substr(i - 2, i + 2) + "\". Range need two valid characters before and after it. Found reserved character before it.",
									errors);
							} else {
								add_error(line_n,
									"Range operation error at position " + to_string(i) + " in \"" + str.substr(j, i + 1) + "\". Range need two valid characters before and after it. Found reserved character before it.",
									errors);
							}
							noError = false;
						}
					} else if (af < bf) {
						add_error(line_n,
							"Range operation error at position " + to_string(i) + " . Range needs to be in format of a-b where a is a character this is before b.",
							errors);
						noError = false;
					}

				}
			} else {
				if (i > 1) {
					add_error(line_n,
						string("Reserved char ") + str.at(i) + " at position " + to_string(i) + " in \"" + str.substr(i - 2, i + 2) + "\". Please use \\" + str.at(i) + " instead.",
						errors);
				} else {
					add_error(line_n,
						string("Reserved char ") + str.at(i) + " at position " + to_string(i) + " in \"" + str.substr(i - 1, i + 3) + "\". Please use \\" + str.at(i) + " instead.",
						errors);
				}
				noError = false;
			}
		} else if (isReservedSymbol(str.at(i)) && i == 0) {
			add_error(line_n,
					string("Reserved char ") + str.at(i) + " at position " + to_string(i) + " in \"" + str.substr(i, i + 4) + "\". Please use \\" + str.at(i) + " instead.",
					errors);
			noError = false;
		}
	}
	return noError;
}

bool isReservedSymbol(char c) {
	return (c == '+' || c == '-' || c == '|' || c == '=' || c == '*'
					  || c == '(' || c == ')' || c == ':');
}

vector<MiniToken> regular_expression_split(string str, map<string, vector<MiniToken>> mapOfDefinitions, set<char> * alphabet) {
	vector<MiniToken> res;
	for (unsigned i = 0; i < str.length(); i++) {
		string k = "";
		char c = str.at(i);
		while (isspace(c)) {
			i++;
			c = str.at(i);
		}
		if (is_operation_char(c)) {
			k+=c;
			res.push_back(MiniToken(OPERATION, k));
		} else if (is_parenthesis(c)) {
			k+=c;
			res.push_back(MiniToken(PARENTHESES, k));
		} else if (c == '-') {
			k += nonspacechar_before(str, i - 1);
			k += c;
			char temp = nonspacechar_after(str, i + 1);
			k += temp;
			i = str.find(temp, i);
			MiniToken mtoken(CHAR_GROUP, k);
			res.push_back(mtoken);
			add_to_alphabet(alphabet, &mtoken);
		} else {
			bool collecting_token = true;
			bool add_eps = false;
			while (collecting_token && i < str.length()) {
				c = str.at(i);
				if (isspace(c) || isReservedSymbol(c)) {
					collecting_token = false;
					i--;
				} else if (c == '\\') {
					if (i == str.length() - 1 || !isReservedSymbol(str.at(i+1))) {
						if (str.at(i+1) == 'L') {
							add_eps = true;
							collecting_token = false;
							i++;
						} else {
							k += c;
						}
					} else {
						i++;
						k += str.at(i);
					}
				} else if (i == str.length() - 1 || nonspacechar_after(str, i + 1) != '-') {
					k += c;
				} else {
					collecting_token = false;
				}
				i++;
			}
			i--;
			if (k != "") {
				if (mapOfDefinitions.find(k) != mapOfDefinitions.end()) {
					vector<MiniToken> temp = mapOfDefinitions.find(k)->second;
					res.push_back(MiniToken(PARENTHESES, "("));
					for (auto it = temp.begin(); it != temp.end(); it++) {
						res.push_back(*it);
					}
					res.push_back(MiniToken(PARENTHESES, ")"));
				} else {
					MiniToken mtoken (WORD,k);
					add_to_alphabet(alphabet, &mtoken);
					res.push_back(mtoken);
				}
			}
			if (add_eps) {
				res.push_back(MiniToken(EPSILON, "\\L"));
			}
		}
	}
	list<MiniToken> expandedReg;
	for (unsigned i = 0; i < res.size() - 1; i++) {
		MiniToken cur = res[i];
		MiniToken next = res[i + 1];
		if ((cur.type == WORD || cur.type == CHAR_GROUP || cur.type == EPSILON ||
				(cur.type == PARENTHESES && cur.tok == ")") || (cur.type == OPERATION && (cur.tok == "*" || cur.tok == "+"))) &&
				(next.type == WORD || next.type == CHAR_GROUP || next.type == EPSILON ||
						(next.type == PARENTHESES && next.tok == "("))) {
			expandedReg.push_back(cur);
			expandedReg.push_back(MiniToken(OPERATION,"@"));
		} else {
			expandedReg.push_back(cur);
		}
	}
	expandedReg.push_back(res[res.size() - 1]);
	return vector<MiniToken>(expandedReg.begin(), expandedReg.end());
}
char nonspacechar_before(string str, unsigned i) {
	while (i >= 0) {
		if (!isspace(str.at(i))) {
			return str.at(i);
		}
		i--;
	}
	return '\0';
}

char nonspacechar_after(string str, unsigned i) {
	while (i < str.length()) {
		if (!isspace(str.at(i))) {
			return str.at(i);
		}
		i++;
	}
	return '\0';
}
bool is_parenthesis(char c) {
	return c == '(' || c == ')';
}
bool is_operation_char(char c) {
	return c == '*' || c == '+' || c == '|';
}

vector<MiniToken> regular_expression_postfix(vector<MiniToken> regexp, bool *error, vector<string> *errors, unsigned line_n) {
	vector<MiniToken> tokens;
	stack<MiniToken> operations;
	unsigned i = 0;
	*error = false;
	bool last_token_operand = false;
	while (!(*error) && i < regexp.size()) {
		MiniToken cur = regexp[i];
		if (cur.type == WORD || cur.type == CHAR_GROUP || cur.type == EPSILON) {
			tokens.push_back(cur);
			last_token_operand = true;
		} else if (cur.type == OPERATION) {
			if (!last_token_operand) {
				*error = true;
				add_error(line_n, "Operation without a previous operand found ! Operation : " + cur.tok, errors);
			} else if (cur.tok == "|" || cur.tok == "@") {
				last_token_operand = false;
				while (!operations.empty()
						&& (operations.top().type == OPERATION &&
								!(operations.top().tok == "|" && cur.tok == "@"))
						&& !(operations.top().type == PARENTHESES && operations.top().tok == "(")) {
					tokens.push_back(operations.top());
					operations.pop();
				}
				operations.push(cur);
			} else if (cur.tok == "*" || cur.tok == "+"){
				tokens.push_back(cur);
			} else {
				*error = true;
				add_error(line_n, "Undefined operation : " + cur.tok, errors);
			}
		} else if (cur.type == PARENTHESES) {
			if (cur.tok == "(") {
				last_token_operand = false;
				operations.push(cur);
			} else if (cur.tok == ")"){
				last_token_operand = true;
				if (operations.empty()) {
					*error = true;
					add_error(line_n, "Parenthesis closed without being opened", errors);
				}
				MiniToken popped = operations.top();
				operations.pop();
				while (!operations.empty() && (popped.type != PARENTHESES || popped.tok != "(")) {
					tokens.push_back(popped);
					popped = operations.top();
					operations.pop();
				}
				if (popped.type != PARENTHESES || popped.tok != "(") {
					add_error(line_n, "Parenthesis closed without being opened", errors);
					*error = true;
				}
			} else {
				*error = true;
				add_error(line_n, "Undefined symbols " + cur.tok, errors);
			}
		} else {
			*error = true;
			add_error(line_n, "Undefined symbols " + cur.tok, errors);
		}
		i++;
	}
	while (!(*error) && !operations.empty()) {
		if (operations.top().type == PARENTHESES) {
			*error = true;
			add_error(line_n, "Parenthesis opened without being closed", errors);
		} else {
			tokens.push_back(operations.top());
		}
		operations.pop();
	}
	if(!(*error) && !valid_postfix(tokens, errors, line_n)) {
		*error = true;
	}
	return tokens;
}
bool valid_postfix(vector<MiniToken> tokens, vector<string>* errors, unsigned line_n) {
	stack<MiniToken> operands;
	bool noError = true;
	for (unsigned i = 0; noError && i < tokens.size(); i++) {
		MiniToken cur = tokens[i];
		if (cur.type == CHAR_GROUP || cur.type == WORD || cur.type == EPSILON) {
			operands.push(cur);
		} else if (cur.type == OPERATION) {
			if (cur.tok == "@" || cur.tok == "|") {
				if (operands.size() < 2) {
					noError = false;
					add_error(line_n, "Binary operation " + cur.tok + " needs two operands.", errors);
				} else {
					operands.pop();
					operands.pop();
					operands.push(cur);
				}
			} else if (cur.tok == "*" || cur.tok == "+") {
				if (operands.size() < 1) {
					noError = false;
					add_error(line_n, "Unary operation " + cur.tok + " needs one operand.", errors);
				} else {
					operands.pop();
					operands.push(cur);
				}
			} else {
				noError = false;
				add_error(line_n, "Unknown token. ", errors);
			}
		} else {
			noError = false;
			add_error(line_n, "Unknown token. ", errors);
		}
	}
	if (operands.size() != 1) {
		add_error(line_n, "Missing operation.", errors);
		noError = false;
	}
	return noError;
}
void add_error(unsigned line_n, string error, vector<string> *errors) {
	errors->push_back("ERROR at " + to_string(line_n) + " : " + error);
}
