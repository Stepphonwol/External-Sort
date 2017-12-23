#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <random>
#include <ctime>
#include <stack>
#include <unordered_map>

using namespace std;

class Ext;

class Record {
	friend class Ext;
	private:
		Record(int x = NULL, float y = NULL) : val(x), key(y) {}
		int val;
		float key;
		void show();
};
