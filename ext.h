#pragma once
#include "record.h"

using namespace std;

class Ext {
	public:
		Ext(long long x = 100000);
	private:
		void generate_input();
		//void read();
		void write();
		void ext_sort();
		void replacement_selection();
		void multiway_merge();
		void fill_RAM();
		int fill_input_buffer();
		int calc_RAM();
		bool is_output_buffer_full();
		void refresh_RAM();
		void refresh_output_buffer();
		void refresh_input_buffer();
		void build_min_heap(int n);
		void sink(int k, int n);
		bool less(Record x, Record y);
		void swap(Record &x, Record &y);
		fstream in;
		ofstream out;
		long long n; // size of testing data
		char input_name[100];
		char output_name[100];
		//array<Record, 4096> RAM;
		//array<Record, 512> input_buffer;
		//array<Record, 512> output_buffer;
		//vector<Record> RAM;
		//vector<Record> input_buffer;
		//vector<Record> output_buffer;
		Record RAM[4096];
		Record input_buffer[512];
		Record output_buffer[512];
};