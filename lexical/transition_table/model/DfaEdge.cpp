//
// Created by programajor on 3/21/18.
//

using namespace std;

#include <algorithm>
#include "DfaEdge.h"

DfaEdge::DfaEdge(char start, char end, DfaNode* source, DfaNode* target) {
    this->first_allowed_char = start;
    this->last_allowed_char = end;
    this->allowing_range = end - start + 1;
    this->source_node = source;
    this->target_node = target;
}

void DfaEdge::disallow_character_sequence(char s, char t) {
//    this->disallowed_chars.push_back(c);

    if (t < this->first_allowed_char || s > this->last_allowed_char) {
        return;
    }

    if (s > this->first_allowed_char && t < this->last_allowed_char) {
        this->allowing_range = s - this->first_allowed_char;
        DfaEdge* newEdge = new DfaEdge(t + 1, this->last_allowed_char, this->source_node, this->target_node);
        this->source_node->addEdge(newEdge);
        this->last_allowed_char = s - 1;
    } else if (s == this->last_allowed_char) {
        this->allowing_range--;
        this->last_allowed_char--;
    } else if (t == this->first_allowed_char) {
        this->allowing_range--;
        this->first_allowed_char++;
    } else if (s > this->first_allowed_char && t >= this->last_allowed_char) {
        this->allowing_range = s - this->first_allowed_char;
        this->last_allowed_char = s - 1;
    } else if (s <= this->first_allowed_char && t < this->last_allowed_char) {
        this->allowing_range = this->last_allowed_char - t;
        this->first_allowed_char = t + 1;
    }
}

DfaNode* DfaEdge::do_transition(char c) {
    if (this->valid_transition(c)) {
        return this->target_node;
    } else {
        return nullptr;
    }
}

bool DfaEdge::valid_transition(char c) {
//    if (find(this->disallowed_chars.begin(), this->disallowed_chars.end(), c) != this->disallowed_chars.end()) {
//        return false;
//    } else {
        return c <= this->last_allowed_char && c >= this->first_allowed_char;
//    }
}

DfaNode* DfaEdge :: get_target_node() {
    return this->target_node;
}
bool  DfaEdge :: equals(DfaEdge* edge) {

	if (edge->get_disallowed_chars().size() != this->get_disallowed_chars().size()) {
		return false;
	}
	for (auto i = edge->get_disallowed_chars().begin();
			i != edge->get_disallowed_chars().end(); ++i) {
		int flag = 0;
		for (auto j = this->get_disallowed_chars().begin();
					j != this->get_disallowed_chars().end(); ++j) {
				 if (i == j) {
					 flag = 1;
				 }
			}
		if (flag == 0) {
			return false;
		}
	}
	return (this->get_first_allowed_char() == edge->get_first_allowed_char()) &&
			(this->get_last_allowed_char() == edge->get_last_allowed_char());
}
char DfaEdge :: get_first_allowed_char() {
    return this->first_allowed_char;
}

char DfaEdge :: get_last_allowed_char() {
    return this->last_allowed_char;
}

vector<char> DfaEdge :: get_disallowed_chars() {
    return this->disallowed_chars;
}

void DfaEdge :: set_target_node(DfaNode* node) {
    this->target_node = node;
}

int DfaEdge:: get_allowing_range(){
	return this->allowing_range;
}

//void DfaEdge::splitEdge(char c) {
//    if (c > this->last_allowed_char || c < this->first_allowed_char) {
//        return;
//    }
//
//}
