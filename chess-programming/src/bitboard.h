#ifndef BITBOARD_H_INCLUDED
#define BITBOARD_H_INCLUDED

#include <intrin.h>
#include <iostream>
#include <vector>

using namespace std;

class Bitboard{
public:
	Bitboard();

	void print(uint64_t);

	vector<uint64_t> _BA_mask;
	vector<uint64_t> _KA_mask;
	vector<uint64_t> _NA_mask;
	vector<vector<uint64_t>> _PA_mask;
	vector<uint64_t> _RA_mask;

private:
	void BA_mask();
	void KA_mask();
	void NA_mask();
	void PA_mask();
	void RA_mask();
};

#endif