#ifndef BITBOARD_H_INCLUDED
#define BITBOARD_H_INCLUDED

#include <iostream>
#include <vector>

using namespace std;

class BB{
public:
	BB() : _BA(64, 0ULL), _KA(64, 0ULL), _NA(64, 0ULL), _PA(2, vector<uint64_t>(64, 0ULL)), _QA(64, 0ULL), _RA(64, 0ULL){
	}
	void print(uint64_t);
	void init_AT();

private:
	void init_BA();
	void init_KA();
	void init_NA();
	void init_PA();
	void init_QA();
	void init_RA();

	vector<uint64_t> _BA;
	vector<uint64_t> _KA;
	vector<uint64_t> _NA;
	vector<vector<uint64_t>> _PA;
	vector<uint64_t> _QA;
	vector<uint64_t> _RA;
};

static constexpr uint64_t FileA = 0x0101010101010101ULL;
static constexpr uint64_t Rank1 = 0xFF00000000000000ULL;
static constexpr uint64_t DiagX = 0x0102040810204080ULL;
static constexpr uint64_t DiagY = 0x8040201008040201ULL;

enum : int{
	A8, B8, C8, D8, E8, F8, G8, H8,
	A7, B7, C7, D7, E7, F7, G7, H7,
	A6, B6, C6, D6, E6, F6, G6, H6,
	A5, B5, C5, D5, E5, F5, G5, H5,
	A4, B4, C4, D4, E4, F4, G4, H4,
	A3, B3, C3, D3, E3, F3, G3, H3,
	A2, B2, C2, D2, E2, F2, G2, H2,
	A1, B1, C1, D1, E1, F1, G1, H1
};
static const vector<pair<int, int>> X_ij{
	{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {6, 7}, {7, 7},
	{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 6}, {7, 6},
	{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 5}, {7, 5},
	{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4},
	{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3},
	{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2},
	{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1},
	{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}
};
static const vector<uint64_t> File{
	FileA << (0),
	FileA << (1),
	FileA << (2),
	FileA << (3),
	FileA << (4),
	FileA << (5),
	FileA << (6),
	FileA << (7)
};
static const vector<uint64_t> Rank{
	Rank1 >> (0*8),
	Rank1 >> (1*8),
	Rank1 >> (2*8),
	Rank1 >> (3*8),
	Rank1 >> (4*8),
	Rank1 >> (5*8),
	Rank1 >> (6*8),
	Rank1 >> (7*8)
};
static inline uint64_t Diag1(int d){
	if(d > 0){
		return (DiagX <<  d) & ~(0x0101010101010101ULL*((2ULL << (d-1))-1)); // i-j = const (i >  j)
	}
	else{
		return (DiagX >> -d) &  (0x0101010101010101ULL*((2ULL << (7+d))-1)); // i-j = const (j >= i)
	}
}
static inline uint64_t Diag2(int d){
	if(d > 0){
		return (DiagY <<  d) & ~(0xFFFFFFFFFFFFFFFFULL << (8*(8-d)));        // i+j = const (i >  7-j)
	}
	else{
		return (DiagY >> -d) &  (0xFFFFFFFFFFFFFFFFULL << (8*( -d)));        // i+j = const (i <= 7-j)
	}
}
enum{P, N, B, R, Q, K, p, n, b, r, q, k};
enum{
	CK = 1, // White king can castle to the king  side (0001).
	CQ = 2, // White king can castle to the queen side (0010).
	Ck = 4, // Black king can castle to the king  side (0100).
	Cq = 8  // Black king can castle to the queen side (1000).
};

#endif