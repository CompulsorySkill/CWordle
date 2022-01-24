#pragma once
#include "Wordle.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <random>

template<int N>
class WordList {
public:
	WordList(const char* file)
	{
		using namespace std;
		ifstream in(file);
		if (!in.is_open()) {
			return;
		}

		string temp;
		while (getline(in, temp)) {
			const char* ctemp = temp.c_str();
			char* cword = new char[N];
			ccopy(ctemp, cword, N);
			list.push_back(cword);
		}

		random_device rd;
		twister_engine = new mt19937(rd());
	}
	~WordList()
	{
		for (auto pc : list) {
			delete pc;
		}
		delete twister_engine;
	}
	int getCount() const
	{
		return list.size();
	}
	Wordle<N> generateWordle() const
	{
		using namespace std;
		uniform_int_distribution<int> gen(0, getCount());
		int index = gen(*twister_engine);
		char* wordle = list.at(index);
		return Wordle<N>(wordle);
	}
protected:
	static void ccopy(const char* source, char* target, size_t n)
	{
		for (size_t i = 0; i < n; i++) {
			target[i] = source[i];
		}
	}
private:
	std::vector<char*> list{};
	std::mt19937 *twister_engine;
};
