#pragma once
#include "record.h"

using namespace std;

class Ext {
	public:
		Ext(long long x = 100000);
	private:
		void generate_input();
		//void read();
		void write(); // used in replacement selection
		void final_write(); // used in multi-way merge
		void temp_write(); // used in multy-way merge
		void ext_sort();
		void replacement_selection();
		void multiway_merge();
		void fill_RAM();
		int fill_input_buffer();
		int calc_RAM();
		bool is_output_buffer_full();
		int read_block(int &i, int j); // used in multi-way merge to fill RAM
		void exhaust_run(vector<int> &mp, vector<Record> &buffer_compare, vector<int> &b, vector<fstream::pos_type> &t, int sign, int min); // used in multy-way merge when certain run has been exhausted
		void refresh_RAM();
		void refresh_output_buffer();
		void refresh_input_buffer();
		void build_min_heap(int n);
		void sink(int k, int n);
		bool end_pass(vector<int> x);
		bool less(Record x, Record y);
		void swap(Record &x, Record &y);
		fstream in;
		fstream out;
		fstream ans;
		long long n; // size of testing data
		char input_name[100];
		char output_name[100];
		char ans_name[100];
		Record RAM[4096]; // main memory
		Record input_buffer[512];
		Record output_buffer[512];
		vector<fstream::pos_type> mark; // beginning positions of each run
		//vector<fstream::pos_type> super_mark; // beginning positions of each supoer-run
};