/* 
 * GrammarTable.cpp
 * Created on: 4/20/18
 *     Author: marc
 */

#include <iostream>
#include "GrammarTable.h"

bool GrammarTable::add_entry(string non_terminal, string terminal, vector<string> rules) {
    bool exist = has_entry(non_terminal, terminal);
    pair<string, string> nt_t_pair = make_pair(non_terminal, terminal);
    if (!exist) {
        table.insert(make_pair(nt_t_pair, rules));
    }

    return !exist;
}

bool GrammarTable::has_entry(string non_terminal, string terminal) {
    bool exist = false;
    pair<string, string> nt_t_pair = make_pair(non_terminal, terminal);
    if (table.find(nt_t_pair) != table.end()) {
        exist = true;
    }

    return exist;
}

vector<string> GrammarTable::get_entry(string non_terminal, string terminal) {
    if (!has_entry(non_terminal, terminal)) {
        return {};
    }

    auto got = table.find(make_pair(non_terminal, terminal));
    return  got.operator->()->second;
}

void GrammarTable::add_synch(string non_terminal, string terminal) {
    synchronizing.insert(make_pair(non_terminal, terminal));
}

bool GrammarTable::is_synch(string non_terminal, string terminal) {
    return synchronizing.find(make_pair(non_terminal, terminal)) != synchronizing.end();
}

vector<string> GrammarTable::get_terminals() {
    auto ret = new vector<string>();
    ret->insert(ret->end(), terminals.begin(), terminals.end());
    return *ret;
}

vector<string> GrammarTable::get_non_terminals() {
    auto ret = new vector<string>();
    ret->insert(ret->end(), non_terminals.begin(), non_terminals.end());
    return *ret;
}

void GrammarTable::set_terminals(vector<string> term) {
    terminals = unordered_set<string>(term.begin(), term.end());
}

void GrammarTable::set_non_terminals(vector<string> non_term) {
    non_terminals = unordered_set<string>(non_term.begin(), non_term.end());
}

bool GrammarTable::is_terminal(string str) {
    return terminals.find(str) != terminals.end();
}

bool GrammarTable::is_non_terminal(string str) {
    return non_terminals.find(str) != non_terminals.end();
}

string GrammarTable::get_start() {
    return start_rule;
}

void GrammarTable::set_start(string str) {
    start_rule = str;
}

unsigned long GrammarTable::get_sync_elements_count() {
    return synchronizing.size();
}

unsigned long GrammarTable::get_table_elements_count() {
    return table.size();
}

bool GrammarTable::compare_table(GrammarTable *grammarTable) {
    auto t1 = this->table;
    auto t2 = grammarTable->table;
    if (t1.size() != t2.size()) {
        return false;
    }

    return compare_map(t1, t2);
}

bool GrammarTable::compare_sync(GrammarTable *grammarTable) {
    auto s1 = this->synchronizing;
    auto s2 = grammarTable->synchronizing;
    if (s1.size() != s2.size()) {
        return false;
    }

    return compare_set(s1, s2);
}

/**.
 *
 * @param v1 computed vector
 * @param v2 expected vector
 * @return
 */
bool GrammarTable::compare_vector(vector<string> v1, vector<string> v2) {
    for (int i = 0; i < v1.size(); i++) {
        if (v1[i] != v2[i]) {
            cout << "Vectors not matched. Expected(" << v2[i] << ") Actual(" << v1[i] << ").\n";
            return false;
        }
    }

    return true;
}

/**.
 * @param map1 computed output
 * @param map2 expected output
 * @return
 */
bool GrammarTable::compare_map(unordered_map<pair<string, string>, vector<string>, pair_hash> map1,
                               unordered_map<pair<string, string>, vector<string>, pair_hash> map2) {
    for (auto const m2Pair : map2) {
        pair<string, string> m2Key = m2Pair.first;
        vector<string> m2Value = m2Pair.second;
        auto m1Pair = map1.find(m2Key);
        if (m1Pair != map1.end()) {
            auto m1Value = m1Pair.operator->()->second;
            if (m1Value.size() != m2Value.size()) {
                cout << "Vector size not matched. Expected(" << m2Value.size()
                     <<") Actual(" << m1Value.size() << ").\n";
                cout << "Key(" << m2Key.first << " " << m2Key.second << ")\n";
                return false;
            } else if (!compare_vector(m1Value, m2Value)) {
                cout << "Key(" << m2Key.first << " " << m2Key.second << ")\n";
                return false;
            }
        } else {
            cout << "Key(" << m2Key.first << " " << m2Key.second << ")not found in table\n";
            return false;
        }

    }

    return true;
}

bool GrammarTable::compare_set(unordered_set<pair<string, string>, pair_hash> set1
        , unordered_set<pair<string, string>, pair_hash> set2) {
    for (auto const v1 : set1) {
        auto v2 = set2.find(v1);
        if (v2 == set2.end()) {
            cout << "Key(" << v1.first << " " << v1.second << ")not found as sync.\n";
            return false;
        }
    }

    return true;
}