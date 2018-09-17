//
// Created by programajor on 3/21/18.
//

#ifndef COMPILERS_DFAEDGE_H
#define COMPILERS_DFAEDGE_H

#include "DfaNode.h"

class DfaNode;
class DfaEdge {
private:
    char first_allowed_char;
    char last_allowed_char;
    DfaNode* source_node;
    DfaNode* target_node;
    int allowing_range;
    vector<char> disallowed_chars;
public:
    DfaNode* do_transition(char c);
    DfaNode* get_target_node();
    void set_target_node(DfaNode* node);
    char get_first_allowed_char();
    char get_last_allowed_char();
    int get_allowing_range();
    vector<char> get_disallowed_chars();
    bool valid_transition(char c);
    void disallow_character_sequence(char s, char t);
    bool equals(DfaEdge* edge);
    DfaEdge(char start, char end, DfaNode* source, DfaNode* target);

};


#endif //COMPILERS_DFAEDGE_H
