/* 
 * Parser.cpp
 * Created on: 4/26/18
 *     Author: marc
 */

#include "Parser.h"

void Parser::init_parser() {
    current_derived_index = 0;
    rules.emplace_back("$");
    rules.push_back(table.get_start());
    derivations.push_back({table.get_start()});
}

void Parser::set_grammar_table(GrammarTable gTable) {
    this->table = gTable;
}

void Parser::derive_token(Token token) {
    string value = token.token_class;

    // pop TOS
    string topStackVal = rules.back();
    rules.pop_back();

    bool search = true;
    while (search) {
        // handle if TOS is terminal and not matched
        while (table.is_terminal(topStackVal) && topStackVal != value) {
            string s = "Error: missing " + topStackVal + ", inserted";
            errors.push_back(s);
            matched_tokens.push_back(topStackVal);
            topStackVal = rules.back();
            rules.pop_back();
        }

        // if it's non terminal, exchange with it's value from the table, if invalid discard
        while (search && table.is_non_terminal(topStackVal)) {
            if (table.has_entry(topStackVal, value)) {
                // add to stack
                vector<string> rule = table.get_entry(topStackVal, value);
                add_new_rule(&rule);

                vector<string> derivation;
                // add new derivation
                add_matched_tokens(&derivation);
                add_current_rules(&derivation);
                derivations.push_back(derivation);

                // pop top element
                topStackVal = rules.back();
                rules.pop_back();
            } else if (table.is_synch(topStackVal, value)) {
                string s = "Error: synch, discard(" + topStackVal + ")";
                errors.push_back(s);
                topStackVal = rules.back();
                rules.pop_back();
            } else {
                // Mark error - non terminal not matched - discard input and continue
                string s = "Error:(illegal " + topStackVal + ") – discard " + value;
                search = false;
                errors.push_back(s);
                rules.push_back(topStackVal);
            }
        }

        if (topStackVal == value) {
            matched_tokens.push_back(topStackVal);
            search = false;
        } else if (topStackVal == "$") {
            rules.emplace_back("$");
            search = false;
        }
    }
}


void Parser::finish_derivation(vector<string> *rerrors, vector<vector<string>> *rderiv) {
    Token endToken(REAL_TOKEN, "", "$");
    derive_token(endToken);
    if (!rules.empty()) {
        errors.emplace_back("Error: input not matched, stack is not empty.\nStack context:");
        for (auto rule : rules) {
            errors.push_back(rule);
        }
    }

    copy_vector(&errors, rerrors);

    for (auto vec : derivations) {
        rderiv->push_back(vector<string>());
        copy_vector(&vec, &rderiv->back());
    }
}

void Parser::copy_vector(vector<string> *src, vector<string> *destination) {
    destination->assign(src->begin(), src->end());
}

void Parser::add_new_rule(vector<string>* rule) {
    for (long i = rule->size() - 1; i >= 0; i--) {
        rules.push_back((*rule)[i]);
    }
}

void Parser::add_matched_tokens(vector<string> *derivation) {
    for (auto const s : matched_tokens) {
        derivation->push_back(s);
    }
}

void Parser::add_current_rules(vector<string> *derivation) {
    for (long i = rules.size() - 1; i > 0; i--) {
        derivation->push_back(rules[i]);
    }
}