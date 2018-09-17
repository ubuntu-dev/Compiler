//
// Created by programajor on 4/26/18.
//

#include <iostream>
#include "../model/GrammarTable.h"
#include "GrammarTableReader.h"
#include "../writer/GrammarTableWriter.h"

GrammarTable *GrammarTableReader::readGrammarTable(ifstream *stream) {
    GrammarTable* grammarTable = new GrammarTable();
    vector<string> nonTerminals, terminals;
    string start;

    if (stream->is_open()) {
        int nonTerminalsSize, terminalsSize;
        if (!(*stream >> nonTerminalsSize) || nonTerminalsSize < 0) {
            cout << "ERROR: In reading non terminals size" << endl;
            return nullptr;
        }
        for (int i = 0; i < nonTerminalsSize; i++) {
            string name;
            if (!(*stream >> name) || name.empty()) {
                cout << "Couldn't read correct name for non terminal ..." << endl;
                return nullptr;
            } else {
                nonTerminals.push_back(name);
            }
        }
        grammarTable->set_non_terminals(nonTerminals);

        if (!(*stream >> terminalsSize) || terminalsSize < 0) {
            cout << "ERROR: In reading terminals size" << endl;
            return nullptr;
        }
        for (int i = 0; i < terminalsSize; i++) {
            string name;
            if (!(*stream >> name) || name.empty()) {
                cout << "Couldn't read correct name for terminal ..." << endl;
                return nullptr;
            } else {
                terminals.push_back(name);
            }
        }
        grammarTable->set_terminals(terminals);

        if (!(*stream >> start) || start.empty()) {
            cout << "Couldn't read correct name for start ..." << endl;
            return nullptr;
        } else {
            grammarTable->set_start(start);
        }

        for (int i = 0; i < nonTerminalsSize; ++i) {
            string nonTerminal = nonTerminals[i];
            for (int j = 0; j < terminalsSize; ++j) {
                string terminal = terminals[j];
                int vectorSize;
                if (!(*stream >> vectorSize) || vectorSize < -2) {
                    cout << "Couldn't read correct name for vector size ..." << endl;
                    return nullptr;
                } else {
                    if (vectorSize == -1) {
                        grammarTable->add_synch(nonTerminal, terminal);
                    } else if (vectorSize != -2) {
                        vector<string> nextElements;
                        for (int k = 0; k < vectorSize; ++k) {
                            string next;
                            if (!(*stream >> next) || next.empty()) {
                                cout << "Couldn't read correct name for element in vector ..." << endl;
                                return nullptr;
                            } else {
                                nextElements.push_back(next);
                            }
                        }
                        grammarTable->add_entry(nonTerminal, terminal, nextElements);
                    }
                }
            }
        }
    }
    return grammarTable;
}
