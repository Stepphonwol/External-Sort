#include "ext.h"

Ext::Ext(long long x) {
	n = x;
	cout << "Name of the input text: " << endl;
	cin >> input_name;
	cout << "Name of the buffer text: " << endl;
	cin >> output_name;
	cout << "Name of the output text : " << endl;
	cin >> ans_name;
	generate_input();
	ext_sort();
	//read();
	//replacement_selection();
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
	//out.open(output_name, fstream::app | fstream::in | fstream::out);
	//int t{ 0 };
	while (!out) {
		cout << "Invalid buffer!!!" << endl
			<< "Name of the buffer txt : " << endl;
		cin >> output_name;
		out.open(output_name);
	}
	for (int i = 0; i < 512; ++i) {
		if (output_buffer[i].key != 0) {
			out << output_buffer[i].val << " " << output_buffer[i].key << " ";
			out << endl;
			//++t;
		}
	}
	//cout << t << endl;
	//out.close();
}

void Ext::final_write()
{
	ans.open(ans_name, fstream::app | fstream::in | fstream::out);
	while (!ans) {
		cout << "Invalid output!!!" << endl
			<< "Name of the output txt : " << endl;
		cin >> ans_name;
		ans.open(ans_name);
	}
	for (int i = 0; i < 512; ++i) {
		if (output_buffer[i].key != 0) {
			ans << output_buffer[i].val << " " << output_buffer[i].key;
			ans << endl;
		}
	}
	ans.close();
}

void Ext::temp_write()
{
	auto old_pos = out.tellg();
	out.seekp(0, fstream::end);
	for (int i = 0; i < 512; ++i) {
		if (output_buffer[i].key != 0) {
			out << output_buffer[i].val << " " << output_buffer[i].key;
			out << endl;
		}
	}
	out.seekg(old_pos);
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
	//int t{ 0 };
	for (int i = 0; i < 4096; ++i) {
		int temp_value;
		float temp_key;
		if (in.peek() == EOF) {
			break;
		}
		if (RAM[i].key == 0) {
			in >> temp_value >> temp_key;
			//++t;
			Record temp(temp_value, temp_key);
			RAM[i] = temp;
		}
	}
	//cout << t << endl;
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
		if (in.peek() == EOF) {
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
	out.open(output_name, fstream::app | fstream::in | fstream::out); // initialize mark
	mark.push_back(out.tellg());
	//out.close();
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
			//out.open(output_name, fstream::app | fstream::in | fstream::out);
			mark.push_back(out.tellp()); // end of the current run (beginning of the next run)
			//out.close();
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
	in.close(); // input file exhausted

	while (length >= 1) { // write the remaining heap in RAM
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
	refresh_output_buffer(); // get ready for multi-way merge
	j = 0;
	refresh_RAM(); // get ready for multi-way merge
	out.close(); // get ready for multi-way merge
}

int Ext::read_block(int &i, int j)
{
	int sign{ 0 }, ending_point{ -1 };
	//bool cmp{ true };
	while (sign != 512) {
	   	/*if (j != mark.size() - 1 && out.tellg() >= mark[j + 1]) {
			break;
		}*/
		int temp_value;
		float temp_key;
		auto old_pos = out.tellg();
		out >> temp_value >> temp_key;
		Record temp(temp_value, temp_key);
		if (out.peek() == EOF || temp.key < RAM[i].key) {
			out.seekg(old_pos);
			ending_point = i;
			return ending_point;
			//cmp = false;
		} // encounters the next run
		RAM[i++] = temp;
		++sign;
	}
	return -1;
}

void Ext::exhaust_run(vector<int> &mp, vector<Record> &buffer_compare, vector<int> &b, vector<fstream::pos_type> &t, int sign, int min)
{
	mp.erase(mp.begin() + min);
	buffer_compare.erase(buffer_compare.begin() + min);
	b.erase(b.begin() + min);
	if (sign == 0) {
		mark.erase(mark.begin() + min);
	}
	else if (sign == 1) {
		t.erase(t.begin() + min);
	}
	//a[sign].erase(a[sign].begin() + min);
}

void Ext::multiway_merge()
{
	int u{ 0 }; // u = 0, merge runs; u = 1; merge super-runs
	out.open(output_name, fstream::app | fstream::in | fstream::out);
	out.seekg(0, fstream::end);
	vector<vector<fstream::pos_type>> all_mark;
	vector<fstream::pos_type> temp_mark;
	temp_mark.push_back(out.tellg());
	all_mark.push_back(mark);
	all_mark.push_back(temp_mark);
	//super_mark.push_back(out.tellg());
	//out.seekg(0, fstream::beg);
	while (!all_mark[0].empty() || !all_mark[1].empty()) {
		vector<int> mp; // contains pointers on each run
		vector<Record> buffer_compare; // contains the first records from each run
		vector<int> break_points;
		int i{ 0 }; // pointer on RAM
		int j{ 0 }; // pointer on MARK
		int k{ 0 }; // pointer on output buffer
		int min{ 0 }; // minimum index
		mp.push_back(i); // the first position
		while (1) { 
			if (j >= all_mark[u].size()) {
				break;
			}
			out.seekg(all_mark[u][j]);
			read_block(i, j); // i += 512
			all_mark[u][j++] = out.tellg(); // update the reading postion for each run
			if (i != 4096 && i != 512 * all_mark[u].size()) {
				mp.push_back(i);
			}
			else {
				break;
			}
		} // initialize current pass for multi-way merge
		for (auto c : mp) {
			break_points.push_back(-1);
		}
		for (auto c : mp) {
			buffer_compare.push_back(RAM[c]);
		} // initialize comparing buffer
		vector<int> origin_mp = mp; // save the beginning position for each run
		while (!mp.empty() && !buffer_compare.empty() && !break_points.empty()) { // a new pass begins
			for (int i = 0; i < buffer_compare.size(); ++i) {
				if (break_points[i] != -1 && mp[i] == break_points[i]) {
					exhaust_run(mp, buffer_compare, break_points, temp_mark, u, min);
					all_mark[0] = mark; // update mark
					all_mark[1] = temp_mark; // update temp-mark
					continue;
				}
				if (buffer_compare[i].key == 0) {
					buffer_compare[i] = RAM[mp[i]];
					//RAM[mp[i]] = 0;
				}
			} // refill the comparing buffer from RAM
			if (mp.empty() || buffer_compare.empty()) {
				break;
			}
			min = 0;
			for (int i = 1; i < buffer_compare.size(); ++i) {
				if (less(buffer_compare[i], buffer_compare[min])) {
					min = i;
				}
			} // find the least record
			if (is_output_buffer_full()) {
				if (u == 0) {
					temp_write();
				}
				else if (u == 1) {
					final_write();
				}
				refresh_output_buffer();
				k = 0;
			}
			output_buffer[k++] = buffer_compare[min]; // get the least record of the comparing buffer to 
			buffer_compare[min].key = 0; // minimum element has been sent to output buffer
			++mp[min]; // move to the next record in the run whose head element has been sent to output buffer
			//bool sign{ true };
			if (mp[min] - origin_mp[min] >= 511) { // this block has been all sent to output buffer
				i = origin_mp[min]; // refill this block
				out.seekg(all_mark[u][min]);
				j = min;
				break_points[j] = read_block(i, j);
				all_mark[u][j] = out.tellg(); // !!!!! update the reading position of this run
				mp[min] = origin_mp[min]; // rewind
			}
			//out.seekg(mark[min]);
			/*if ((min == mark.size() - 1 && out.peek() == EOF) || !sign) { // this run has been exhausted
				buffer_compare.erase(buffer_compare.begin() + min);
				mp.erase(mp.begin() + min);
				mark.erase(mark.begin() + min);
			}*/
		}
		/*if (is_output_buffer_full()) {
			if (u == 0) {
				temp_write();
			}
			else if (u == 1) {
				final_write();
			}
			refresh_output_buffer();
			k = 0;
		}*/
		if (u == 0) {
			temp_write();
		}
		else if (u == 1) {
			final_write();
		}
		refresh_output_buffer();
		k = 0;
		refresh_RAM();
		out.seekg(0, fstream::end);
		temp_mark.push_back(out.tellg());
		all_mark[1] = temp_mark;
		if (mark.empty()) { // all runs are exhausted
			//temp_mark.push_back(out.tellg());
			u = 1;
			temp_mark.erase(temp_mark.end() - 1);
			all_mark[1] = temp_mark;
			//mark = temp_mark;
		}
	}
	//super_mark.erase(super_mark.end() - 1); // last positon is useless
	/*while (!super_mark.empty()) {
		
	}*/
	out.close();
}

void Ext::ext_sort()
{
	replacement_selection();
	multiway_merge();
}