/*
 * tokenizer_test.cpp
 *
 *  Created on: Mar 23, 2018
 *      Author: amrnasr
 */

#include <iostream>
#include "../../../test_headers/p1_tests.h"
#include "../../transition_table/model/DfaNode.h"
#include "../../transition_table/model/DfaEdge.h"
#include "tokenizer.h"


void tokenizer_test_1();
void tokenizer_test_2();

void test_tokenizer() {
    tokenizer_test_1();
    tokenizer_test_2();
}


void tokenizer_test_1() {
    DfaNode * n1 = new DfaNode("n1-end",true);
    DfaNode * n2 = new DfaNode("n2",false);
    DfaNode * n3 = new DfaNode("n3-end",true);
    DfaNode * n4 = new DfaNode("n4",false);
    DfaNode * n5 = new DfaNode("n5",false);
    DfaNode * n6 = new DfaNode("n6",false);
    DfaNode * n7 = new DfaNode("n7-end",true);

    DfaEdge * n1n2 = new DfaEdge('1', '1', n1, n2);
    DfaEdge * n1n5 = new DfaEdge('0', '0', n1, n5);
    DfaEdge * n2n3 = new DfaEdge('0', '0', n2, n3);
    DfaEdge * n2n6 = new DfaEdge('1', '1', n2, n6);
    DfaEdge * n3n4 = new DfaEdge('0', '0', n3, n4);
    DfaEdge * n3n7 = new DfaEdge('1', '1', n3, n7);
    DfaEdge * n4n4 = new DfaEdge('0', '1', n4, n4);
    DfaEdge * n5n5 = new DfaEdge('0', '1', n5, n5);
    DfaEdge * n6n5 = new DfaEdge('1', '1', n6, n5);
    DfaEdge * n6n1 = new DfaEdge('0', '0', n6, n1);
    DfaEdge * n7n3 = new DfaEdge('0', '0', n7, n3);
    DfaEdge * n7n2 = new DfaEdge('1', '1', n7, n2);

    n1->addEdge(n1n2);
    n1->addEdge(n1n5);
    n2->addEdge(n2n3);
    n2->addEdge(n2n6);
    n3->addEdge(n3n4);
    n3->addEdge(n3n7);
    n4->addEdge(n4n4);
    n5->addEdge(n5n5);
    n6->addEdge(n6n1);
    n6->addEdge(n6n5);
    n7->addEdge(n7n2);
    n7->addEdge(n7n3);

    auto tokenizer = new Tokenizer(n1);


    string s1 = "";
    string s2 = "xx1010101x10101110";
    string s3 = "xx1010101x10101110ss";
    tokenizer->tokenize(s1);
    int i = 0;
    string expectedClasses[] = {"n1-end"};
    string expectedLexemes[] = {""};
    TOKEN_TYPE expectedTypes[] = {REAL_TOKEN};
    bool error = false;
    while (tokenizer->hasNext()) {
        Token t = tokenizer->nextToken();
        if (t.lexme != expectedLexemes[i] || t.token_class != expectedClasses[i]
                || t.type != expectedTypes[i]) {
            cout << "Tokenizer: test 1 error: " << i;
            error = true;
        }

        i++;
    }

    int i2 = 0;
    string expectedClasses2[] = {"", "n7-end", "" , "n1-end"};
    string expectedLexemes2[] = {"xx", "1010101", "x", "10101110"};
    TOKEN_TYPE expectedTypes2[] = {ERROR_TOKEN, REAL_TOKEN, ERROR_TOKEN, REAL_TOKEN};

    tokenizer->tokenize(s2);
    while (tokenizer->hasNext()) {
        Token t = tokenizer->nextToken();

        if (t.lexme != expectedLexemes2[i2] || t.token_class != expectedClasses2[i2]
            || t.type != expectedTypes2[i2]) {
            cout << "Tokenizer: test 2 error: " << i2 << endl;
            cout << "Lexeme:\nExpected: " << expectedLexemes2[i2] << ", Actual: " << t.lexme << endl;
            cout << "Class:\nExpected: " << expectedClasses2[i2] << ", Actual: " << t.token_class << endl;
            cout << "Type:\nExpected: " << expectedTypes2[i2] << ", Actual: " << t.type << endl;

            error = true;
        }

        i2++;
    }

    int i3 = 0;
    string expectedClasses3[] = {"", "n7-end", "" , "n1-end", ""};
    string expectedLexemes3[] = {"xx", "1010101", "x", "10101110", "ss"};
    TOKEN_TYPE expectedTypes3[] = {ERROR_TOKEN, REAL_TOKEN, ERROR_TOKEN, REAL_TOKEN, ERROR_TOKEN};

    tokenizer->tokenize(s3);
    while (tokenizer->hasNext()) {
        Token t = tokenizer->nextToken();

        if (t.lexme != expectedLexemes3[i3] || t.token_class != expectedClasses3[i3]
            || t.type != expectedTypes3[i3]) {
            cout << "Tokenizer: test 3 error: " << i3 << endl;
            cout << "Lexeme:\nExpected: " << expectedLexemes2[i3] << ", Actual: " << t.lexme << endl;
            cout << "Class:\nExpected: " << expectedClasses2[i3] << ", Actual: " << t.token_class << endl;
            cout << "Type:\nExpected: " << expectedTypes2[i3] << ", Actual: " << t.type << endl;

            error = true;
        }

        i3++;
    }

    if (!error) {
        cout << "Tokenizer Success..." << endl;
    }
}


void tokenizer_test_2() {
    DfaNode * n1 = new DfaNode("n1",false);
    DfaNode * n2 = new DfaNode("n2-end",true);
    DfaNode * n3 = new DfaNode("n3-end",true);
    DfaNode * n4 = new DfaNode("n4-end",true);
    DfaNode * n5 = new DfaNode("n5-end",true);
    DfaNode * n6 = new DfaNode("n6-end",true);

    DfaEdge * n1n2 = new DfaEdge('0', '0', n1, n2);
    DfaEdge * n1n5 = new DfaEdge('1', '1', n1, n5);
    DfaEdge * n2n2 = new DfaEdge('0', '0', n2, n2);
    DfaEdge * n2n4 = new DfaEdge('1', '1', n2, n4);
    DfaEdge * n3n1 = new DfaEdge('1', '1', n3, n1);
    DfaEdge * n5n3 = new DfaEdge('1', '1', n5, n3);
    DfaEdge * n4n1 = new DfaEdge('0', '0', n4, n1);
    DfaEdge * n5n1 = new DfaEdge('0', '0', n5, n1);
    DfaEdge * n4n6 = new DfaEdge('1', '1', n4, n6);
    DfaEdge * n6n2 = new DfaEdge('0', '1', n6, n2);

    n1->addEdge(n1n2);
    n1->addEdge(n1n5);
    n2->addEdge(n2n2);
    n2->addEdge(n2n4);
    n3->addEdge(n3n1);
    n4->addEdge(n4n1);
    n4->addEdge(n4n6);
    n6->addEdge(n6n2);
    n5->addEdge(n5n3);
    n5->addEdge(n5n1);

    auto tokenizer = new Tokenizer(n1);


    string s1 = "0";
    string s2 = "1010101 111010";
    string s3 = "1010111001";
    tokenizer->tokenize(s1);
    int i = 0;
    string expectedClasses[] = {"n2-end"};
    string expectedLexemes[] = {"0"};
    TOKEN_TYPE expectedTypes[] = {REAL_TOKEN};
    bool error = false;
    while (tokenizer->hasNext()) {
        Token t = tokenizer->nextToken();
        if (t.lexme != expectedLexemes[i] || t.token_class != expectedClasses[i]
                || t.type != expectedTypes[i]) {
            cout << "Tokenizer: test 1 error: " << i;
            error = true;
        }

        i++;
    }


    if (!error) {
        cout << "Tokenizer Success..." << endl;
    }
}
