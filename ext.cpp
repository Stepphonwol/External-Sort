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
	auto start = clock();
	ext_sort();
	auto end = clock();
	test();
	cout << "Total running time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
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
	out.close();
	ofstream temp_out;
 	temp_out.open(output_name, fstream::out | fstream::app);
	//out.seekp(0, fstream::end);
	//out.clear();
	for (int i = 0; i < 512; ++i) {
		if (output_buffer[i].key != 0) {
			temp_out << output_buffer[i].val << " " << output_buffer[i].key;
			temp_out << endl;
		}
	}
	temp_out.close();
	out.open(output_name, fstream::in | fstream::out | fstream::app);
	//out.clear();
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
	for (int i = 0; i < 4096 && in.peek() != EOF; ++i) {
		int temp_value;
		float temp_key;
		if (RAM[i].key == 0) {
			in >> temp_value >> temp_key;
			if (in.eof()) {
				break;
			}
			//++t;
			Record temp(temp_value, temp_key);
			RAM[i] = temp;
		}
		/*if (in.peek() == EOF) {
			break;
		}*/
	}
	//cout << t << endl;
}

bool Ext::is_RAM_empty()
{
	int i{ 0 };
	bool ans{ false };
	for (i = 0; i < 4096; ++i) {
		if (RAM[i].key != 0) {
			break;
		}
	}
	if (i == 4096) {
		ans = true;
	}
	return ans;
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
	for (i = 0; i < 512 && in.peek() != EOF; ++i) {
		int temp_value;
		float temp_key;
		in >> temp_value >> temp_key;
		if (in.eof()) {
			break;
		}
		Record temp(temp_value, temp_key);
		input_buffer[i] = temp;
	}
	return i;
}

bool Ext::is_input_buffer_empty()
{
	int i{ 0 };
	bool ans{ false };
	for (i = 0; i < 512; ++i) {
		if (input_buffer[i].key != 0) {
			break;
		}
	}
	if (i == 512) {
		ans = true;
	}
	return ans;
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
	int l{ 0 }; // length of each run
	int length = calc_RAM(); // the actual size of the heap
	build_min_heap(length); // Build a min heap on RAM
	out.open(output_name, fstream::app | fstream::in | fstream::out); // initialize mark
	mark.push_back(out.tellg());
	//out.close();
	while ((in.peek() != EOF) || !is_input_buffer_empty()) {
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
			mark_length.push_back(l);
			l = 0; // a new run
			//out.close();
			fill_RAM(); // get ready for the next run
			length = calc_RAM();; // initialize the next run (heap size)
			build_min_heap(length); // initialize the next run(build min-heap)
			continue;
		}
		output_buffer[j++] = RAM[0];// Send the record with minimum key value to output buffer
		++l; // run increasing
		if (i < 0) {
			i = fill_input_buffer() - 1;
		}
		Record input;
		if (i >= 0) {
			input = input_buffer[i];
			input_buffer[i--].key = 0;
		}
		if (input.key == 0) { // no input, input-buffer is empty
			break;
		}
		else if (!less(input, RAM[0])) { // if the input record has greater key value than the root record
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
		++l;
		swap(RAM[0], RAM[length - 1]);
		RAM[length - 1].key = 0; // !!!!no need to store this record
		--length;
		sink(0, length);
	}

	if (!is_RAM_empty()) { // still elements left in RAM to build another run
		write();
		refresh_output_buffer();
		j = 0;
		mark.push_back(out.tellg());
		mark_length.push_back(l);
		l = 0;
		//fill_RAM();
		length = calc_RAM();
		build_min_heap(length);
		while (length >= 1) { // write the remaining heap in RAM
			if (is_output_buffer_full()) {
				write();
				refresh_output_buffer();
				j = 0;
			}
			output_buffer[j++] = RAM[0];
			++l;
			swap(RAM[0], RAM[length - 1]);
			RAM[length - 1].key = 0; // !!!!no need to store this record
			--length;
			sink(0, length);
		}
	}
	write();
	refresh_output_buffer(); // get ready for multi-way merge
	mark_length.push_back(l); // length of the last run
	j = 0;
	refresh_RAM(); // get ready for multi-way merge
	out.close(); // get ready for multi-way merge
}

int Ext::read_block(int &i, int j, int u, vector<vector<int>*> all_mark_length)
{
	int sign{ 0 };
	while (sign != 512) {
		int delete_sign = *(all_mark_length[u]->begin() + j);
		if (delete_sign == 0) { // run exhausted
			break;
		}
		int temp_value;
		float temp_key;
		auto old_pos = out.tellg();
		out >> temp_value >> temp_key;
		Record temp(temp_value, temp_key);
		if (out.eof()) {
			out.clear();
			out.seekg(old_pos);
			break;
		}
		RAM[i++] = temp;
		++sign;
		--*(all_mark_length[u]->begin() + j);
	}
	return i;
}

void Ext::exhaust_run(vector<int> &mp, vector<Record> &buffer_compare, vector<vector<fstream::pos_type>*> all_mark, vector<vector<int>*> all_mark_length, vector<int>& break_points, int sign, int min)
{
	mp.erase(mp.begin() + min);
	buffer_compare.erase(buffer_compare.begin() + min);
	break_points.erase(break_points.begin() + min);
	if (sign == 0) {
		all_mark[sign]->erase(all_mark[sign]->begin() + min);
		all_mark_length[sign]->erase(all_mark_length[sign]->begin() + min);
	}
	else if (sign == 1) {
		all_mark[sign]->erase(all_mark[sign]->begin() + min);
		all_mark_length[sign]->erase(all_mark_length[sign]->begin() + min);
	}
}

void Ext::multiway_merge()
{
	int u{ 0 }; // u = 0, merge runs; u = 1; merge super-runs
	int l{ 0 }; // store the length of runs
	out.open(output_name, fstream::ate | fstream::in | fstream::out);
	vector<vector<fstream::pos_type>*> all_mark;
	vector<vector<int>*> all_mark_length;
	vector<fstream::pos_type> temp_mark; // store super runs
	vector<int> temp_mark_length; // store the length of super runs
	temp_mark.push_back(out.tellg());
	all_mark.push_back(&mark); // initialize mark container
	all_mark.push_back(&temp_mark);
	all_mark_length.push_back(&mark_length); // initialize mark length container
	all_mark_length.push_back(&temp_mark_length);
	while (!all_mark[u]->empty()) {
		vector<int> mp; // contains pointers on each run
		vector<Record> buffer_compare; // contains the first records from each run
		vector<int> break_points; // ending positions for each block
		int i{ 0 }; // pointer on RAM
		int j{ 0 }; // pointer on MARK
		int k{ 0 }; // pointer on output buffer
		int min{ 0 }; // minimum index
		for (j = 0; j < all_mark[u]->size() && i < 4096; ++j) {
			out.seekg(*(all_mark[u]->begin() + j));
			mp.push_back(i);
			read_block(i, j, u, all_mark_length); // i += 512
			break_points.push_back(i);
			*(all_mark[u]->begin() + j) = out.tellg(); // !!! update the reading position for each run
		} // initialize current run for multi-way merge
		for (auto c : mp) {
			buffer_compare.push_back(RAM[c]);
		} // initialize comparing buffer
		vector<int> origin_mp = mp; // save the beginning position for each run
		while (!mp.empty() && !buffer_compare.empty() && !all_mark_length[u]->empty()) { // a new pass begins
			for (int i = 0; i < buffer_compare.size(); ++i) {
				if (mp[i] >= break_points[i]) { // this run has been exhausted
					exhaust_run(mp, buffer_compare, all_mark, all_mark_length, break_points, u, i);
					continue;
				}
				if (buffer_compare[i].key == 0) {
					buffer_compare[i] = RAM[mp[i]];
				}
			} // refill the comparing buffer from RAM
			if (mp.empty() || buffer_compare.empty() || all_mark_length[u]->empty()) {
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
			output_buffer[k++] = buffer_compare[min]; // get the least record of the comparing buffer to output buffer
			++l;
			buffer_compare[min].key = 0; // minimum element has been sent to output buffer
			++mp[min]; // move to the next record in the run whose head element has been sent to output buffer
			if (mp[min] - origin_mp[min] >= 512) { // this block has been all sent to output buffer
				i = origin_mp[min]; // refill this block
				out.seekg(*(all_mark[u]->begin() + min));
				auto pos1 = out.tellg();
				j = min;
				int receive = read_block(i, j, u, all_mark_length);
				*(all_mark[u]->begin() + min) = out.tellg(); // !!!!! update the reading position of this run
				auto pos2 = out.tellg();
				if (pos1 != pos2) { // only when new records were read, then rewinding is necessary
					mp[min] = origin_mp[min]; // rewind
					break_points[j] = receive; // !!!!!!!!!! update the break points only when new records were read
				}
			}
		}
		if (u == 0) {
			temp_write();
		}
		else if (u == 1) {
			final_write();
		}
		refresh_output_buffer();
		k = 0;
		refresh_RAM();
		out.close();
		out.open(output_name, fstream::ate | fstream::in | fstream::out);
		all_mark[1]->push_back(out.tellg());
		all_mark_length[1]->push_back(l);
		l = 0;
		if (all_mark[0]->empty()) { // all runs are exhausted
			u = 1; // start merging super runs
			all_mark[1]->erase(all_mark[1]->end() - 1);
		}
	}
	out.close();
}

void Ext::ext_sort()
{
	replacement_selection();
	multiway_merge();
}

void Ext::test()
{
	long long count{ 0 };
	fstream test_input;
	fstream test_output;
	stack<double> s;
	test_input.open(input_name, fstream::in);
	test_output.open(ans_name, fstream::in);
	while (1) { // initialize test table
		int temp_val;
		double temp_key;
		test_input >> temp_val >> temp_key;
		if (test_input.eof()) {
			break;
		}
		test_table[temp_key] = true;
	}
	test_input.close();
	while (1) { // verify output
		int temp_val;
		double temp_key;
		test_output >> temp_val >> temp_key;
		if (test_output.eof()) {
			break;
		}
		if (!s.empty()) {
			double prev = s.top();
			if (temp_key >= prev) {
				++count;
			}
			else {
				cout << "Wrong sorting!!!" << endl;
			}
		}
		test_table[temp_key] = false;
		s.push(temp_key);
	}
	test_output.close();
	test_input.open(input_name, fstream::in);
	while (1) { // output the missing records
		int temp_val;
		double temp_key;
		test_input >> temp_val >> temp_key;
		if (test_input.eof()) {
			break;
		}
		if (test_table[temp_key] == true) {
			cout << temp_key << endl;
		}
	}
	if (count == n - 1) {
		cout << "All elements are in place!!!" << endl
			<< "No records missing!!!" << endl;
	}
	test_input.close();
}