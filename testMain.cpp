
#include <iostream>
#include "test_headers/p1_tests.h"
#include "test_headers/p2_tests.h"
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

void run_tests_p1(void);
void run_tests_p2(void);

int main() {
	run_tests_p1();
	run_tests_p2();
    return 0;
}

void run_tests_p2() {
//	test_grammar_table_writer_reader();
	test_grammar_table();
	test_grammar_table_reader();
	test_grammar_table_writer();
	test_grammar_file_parser();
	test_first_calculator();
	test_follow_calculator();
	test_ll_converter();
	test_grammar_table_builder();
	test_syntactic_analyzer_generator();
	test_parser();
}

void run_tests_p1() {
	test_edge();
	test_node();
	test_grammar_parser();
	test_minimizer();
	test_nfa_builder();
    test_nfa_dfa_converter();
	test_transition_table_builder();
    test_transition_table_writer_human_form();
    test_transition_table_writer_readable_form();
	test_transition_table_reader();
    test_transition_table_deconstructor();
	test_tokenizer();
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	test_analyzer_generator();
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>( t2 - t1 ).count();
	cout << "Time taken to generate transition tables: " << duration << " millisecond" << endl;
	t1 = high_resolution_clock::now();
	test_token_generator();
	t2 = high_resolution_clock::now();
	duration = duration_cast<milliseconds>( t2 - t1 ).count();
	cout << "Time taken to generate tokens: " << duration << " millisecond" << endl;
}
