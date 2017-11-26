#include "ext.h"

Ext::Ext(long long x) {
	n = x;
	cout << "Name of the input text: " << endl;
	cin >> input_name;
	cout << "Name of the output text: " << endl;
	cin >> output_name;
	generate_input();
	//read();
	replacement_selection();
	/*fill_RAM();
	fill_input_buffer();
	build_min_heap();
	for (auto c : RAM) {
		c.show();
	}
	cout << endl;*/
	//ext_sort();
}

void Ext::generate_input()
{
	static default_random_engine e;
	static uniform_int_distribution<unsigned> v(0, 10000);
	static uniform_real_distribution<float> u(0, 10000);
	//ofstream temp_in;
	//temp_in.open(input_name);
	in.open(input_name, fstream::out | fstream::in);
	auto start = in.tellg();
	for (long long i = 0; i < n; ++i) {
		in << v(e) << " " << u(e) << " ";
	}
	in.seekg(0, start);
	//in.close();
}

/*void Ext::read()
{
	in.open(input_name, fstream::in | fstream::out);
	while (!in) {
		cout << "Invalid input!!!" << endl
			<< "Name of the input txt : " << endl;
		cin >> input_name;
		in.open(input_name);
	}
	cout << "Input file successfully read!!!" << endl;
}*/

void Ext::write()
{
	out.open(output_name, ofstream::app);
	while (!out) {
		cout << "Invalid output!!!" << endl
			<< "Name of the output txt : " << endl;
		cin >> input_name;
		in.open(input_name);
	}
	for (int i = 0; i < 512; ++i) {
		if (output_buffer[i].key != 0) {
			out << output_buffer[i].val << " " << output_buffer[i].key;
			out << endl;
		}
	}
	out.close();
}

void Ext::fill_RAM()
{
	/*if (RAM.size() == 4096) {
		cout << "RAM Full !!!" << endl;
		return;
	}*/
	/*while (!in.eof() && RAM.size() != 4096) {
		int temp_value;
		float temp_key;
		in >> temp_value >> temp_key;
		Record temp(temp_value, temp_key);
		RAM.push_back(temp);
	}*/
	for (int i = 0; i < 4096; ++i) {
		int temp_value;
		float temp_key;
		if (!in) {
			break;
		}
		if (RAM[i].key == 0) {
			in >> temp_value >> temp_key;
			Record temp(temp_value, temp_key);
			RAM[i] = temp;
		}
	}
}

int Ext::fill_input_buffer()
{
	/*if (input_buffer.size() == 512) {
		cout << "Input Buffer Full !!!" << endl;
		return;
	}*/
	/*while (!in.eof() && input_buffer.size() != 512) {
		int temp_value;
		int temp_key;
		in >> temp_value >> temp_key;
		Record temp(temp_value, temp_key);
		input_buffer.push_back(temp);
	}*/
	int i{ 0 };
	for (i = 0; i < 512; ++i) {
		int temp_value;
		float temp_key;
		if (!in) {
			break;
		}
		in >> temp_value >> temp_key;
		Record temp(temp_value, temp_key);
		input_buffer[i] = temp;
	}
	return i;
}

int Ext::calc_RAM()
{
	int n{ 0 }, j{ 0 };
	for (int i = 0; i < 4096; ++i) {
		if (RAM[i].key != 0) {
			++n;
			RAM[j++] = RAM[i];
		}
	}
	return n;
}

bool Ext::is_output_buffer_full()
{
	if (output_buffer[511].key != NULL) {
		return true;
	}
	else {
		return false;
	}
}

void Ext::refresh_RAM()
{
	for (int i = 0; i < 4096; ++i) {
		RAM[i].key = 0;
		RAM[i].val = 0;
	}
}

void Ext::refresh_input_buffer()
{
	for (int i = 0;  i < 512; ++i) {
		input_buffer[i].key = 0;
		input_buffer[i].val = 0;
	}
}

void Ext::refresh_output_buffer()
{
	for (int i = 0; i < 512; ++i) {
		output_buffer[i].key = 0;
		output_buffer[i].val = 0;
	}
}

bool Ext::less(Record x, Record y)
{
	if (x.key < y.key) {
		return true;
	}
	else {
		return false;
	}
}

void Ext::swap(Record &x, Record &y)
{
	Record temp = x;
	x = y;
	y = temp;
}

void Ext::build_min_heap(int n)
{
	//int n = RAM.size();
	for (int k = n / 2 - 1; k >= 0; --k) {
		sink(k, n);
	}
}

void Ext::sink(int k, int n)
{
	while (2 * k + 1 < n) {
		int j = 2 * k + 1; // j : left-son; k : root; 
		if (j < n - 1 && !less(RAM[j], RAM[j + 1])) {
			++j;
		}
		if (less(RAM[k], RAM[j])) {
			//swap(RAM[k], RAM[j]);
			break;
		}
		swap(RAM[k], RAM[j]);
		k = j;
	}
}

void Ext::replacement_selection()
{
	fill_RAM(); // Fill RAM from fisk
	int i = fill_input_buffer() - 1; // Fill input buffer from disk, pointer on the input buffer
	int j{ 0 }; // pointer on the output buffer
	int length = calc_RAM(); // the actual size of the heap
	build_min_heap(length); // Build a min heap on RAM
	while (!in.eof()) {
		if (is_output_buffer_full()) {
			write();
			refresh_output_buffer();
			j = 0;
		}
		if (length == 0) { // current run is complete
			write(); // written the output buffer to output run files
			refresh_output_buffer(); // get ready for the next run
			j = 0; // get ready for the next run
			fill_RAM(); // get ready for the next run
			length = calc_RAM();; // initialize the next run (heap size)
			build_min_heap(length); // initialize the next run(build min-heap)
			continue;
		}
		output_buffer[j++] = RAM[0];// Send the record with minimum key value to output buffer
		if (i < 0) {
			i = fill_input_buffer() - 1;
		}
		Record input;
		if (i >= 0) {
			input = input_buffer[i];
			input_buffer[i--].key = NULL;
		}
		if (input.key == NULL) { // no input, input-buffer is empty
			while (length >= 1) {
				if (is_output_buffer_full()) {
					write();
					refresh_output_buffer();
					j = 0;
				}
				output_buffer[j++] = RAM[0];
				swap(RAM[0], RAM[--length]);
				sink(0, length);
			}
			write();
			//RAM.clear();
			refresh_RAM();
			refresh_output_buffer();//output_buffer.clear();
			j = 0;
			break;
		}
		else if (!less(input, RAM[0])) { // if the input record has greater key value than the root record
			//output_buffer.push_back(input); 
			RAM[0] = input; // place the input record at the root
		}
		else {
			swap(RAM[0], RAM[length - 1]); // replace the root with record in the last position
			RAM[length - 1] = input; // place the input record at the last position
			--length;
		}
		sink(0, length);
	}

	while (length >= 1) {
		if (is_output_buffer_full()) {
			write();
			refresh_output_buffer();
			j = 0;
		}
		output_buffer[j++] = RAM[0];
		swap(RAM[0], RAM[--length]);
		sink(0, length);
	}
	write();
	refresh_output_buffer();
	j = 0;
	refresh_RAM();
}

void Ext::ext_sort()
{
	
}