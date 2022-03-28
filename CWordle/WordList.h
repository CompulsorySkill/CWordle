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

		// init random seed
		random_device rd;
		twister_engine = new mt19937(rd());

		// load word file
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
	int indexOf(const char *key)
	{
		for (int i = 0; i < list.size(); i++) {
			if (ccompare(key, list.at(i), N) == 0) {
				return i;
			}
		}
		return 0;
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
	static int ccompare(const char *source, char *target, size_t n)
	{
		for (size_t i = 0; i < n; i++) {
			if (source[i] == target[i]) {
				continue;
			} else {
				return source[i] - target[i];
			}
		}
		return 0;
	}
private:
	std::vector<char*> list{};
	std::mt19937 *twister_engine;
};
