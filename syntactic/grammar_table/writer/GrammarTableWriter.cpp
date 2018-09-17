//
// Created by programajor on 4/26/18.
//

#include <iostream>
#include <iomanip>
#include "../model/GrammarTable.h"
#include "GrammarTableWriter.h"

void GrammarTableWriter::writeGrammarTableInReadableForamt(GrammarTable *table, ostream *stream) {
    vector<string> nonTerminals = table->get_non_terminals();
    vector<string> terminals = table->get_terminals();
    string start = table->get_start();

    *stream << nonTerminals.size() << endl;
    for (int i = 0; i < nonTerminals.size(); ++i) {
        *stream << nonTerminals[i] << endl;
    }

    *stream << terminals.size() << endl;
    for (int i = 0; i < terminals.size(); ++i) {
        *stream << terminals[i] << endl;
    }

    *stream << start << endl;

    for (int i = 0; i < nonTerminals.size(); ++i) {
        string nonTerminal = nonTerminals[i];
        for (int j = 0; j < terminals.size(); ++j) {
            string terminal = terminals[j];
            if (table->has_entry(nonTerminal, terminal)) {
                vector<string> vec = table->get_entry(nonTerminal, terminal);
                *stream << vec.size() << endl;
                for (int k = 0; k < vec.size(); ++k) {
                    *stream << vec[k] << endl;
                }
            } else if  (table->is_synch(nonTerminal, terminal)) {
                *stream << SYNC_ENTRY << endl;
            } else {
                *stream << HAS_NO_ENTRY << endl;
            }
        }
    }
}

void GrammarTableWriter::writeGrammarTableInHumanReadableFormat(GrammarTable *table, ostream *stream) {
    vector<string> nonTerminals = table->get_non_terminals();
    vector<string> terminals = table->get_terminals();

    string tablePrinted[nonTerminals.size() + 1][terminals.size() + 1];

    tablePrinted[0][0]= "NT \\ T";

    for (int i = 0; i < terminals.size(); ++i) {
        tablePrinted[0][i + 1] = " | " + terminals[i];
    }

    for (int i = 0; i < nonTerminals.size(); ++i) {
        string nonTerminal = nonTerminals[i];
        tablePrinted[i + 1][0] = nonTerminal;
        for (int j = 0; j < terminals.size(); ++j) {
            string terminal = terminals[j];
            if (table->has_entry(nonTerminal, terminal) ) {
                vector<string> vec = table->get_entry(nonTerminal, terminal);
                if (vec.size() == 0) {
                    tablePrinted[i + 1][j + 1] = " | " + nonTerminal + " -> EPS";
                } else {
                    string next;
                    for (int k = 0; k < vec.size(); ++k) {
                        next += (" " + vec[k]);
                    }
                    tablePrinted[i + 1][j + 1] = " | " + nonTerminal + " ->" + next;
                }
            } else if (table->is_synch(nonTerminal, terminal)) {
                tablePrinted[i + 1][j + 1] = " | Synch";
            } else {
                tablePrinted[i + 1][j + 1] = " | Error";
            }
        }
    }

    vector<int> maxLengths;
    for (int i = 0; i <= terminals.size(); ++i) {
        int max = 0;
        for (int j = 0; j <= nonTerminals.size(); ++j) {
            if (tablePrinted[j][i].length() > max) {
                max = tablePrinted[j][i].length();
            }
        }
        maxLengths.push_back(max);
    }

    for (int i = 0; i <= nonTerminals.size(); ++i) {
        for (int j = 0; j <= terminals.size(); ++j) {
            int length = maxLengths[j];
            *stream << left << setw(length) << tablePrinted[i][j];
        }
        *stream << endl;
    }
    *stream << endl << "Start is: " << table->get_start();
}
