#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED

#include "bitboard.h"

enum : int{P, N, B, R, Q, K, p, n, b, r, q, k};

class Move{
public:
	uint64_t _From;
	uint64_t _To;
};
class Position{
public:
	Position();

	uint64_t _BOcc;
	uint64_t _BA;
	uint64_t _BP;
	uint64_t _BN;
	uint64_t _BB;
	uint64_t _BR;
	uint64_t _BQ;
	uint64_t _BK;
	uint64_t _WOcc;
	uint64_t _WA;
	uint64_t _WP;
	uint64_t _WN;
	uint64_t _WB;
	uint64_t _WR;
	uint64_t _WQ;
	uint64_t _WK;
	bool     _BK_C;
	bool     _WK_C;
	bool     _BQ_C;
	bool     _WQ_C;
	bool     _Turn;
private:
	uint64_t _get_BA() const;
	uint64_t _get_WA() const;
};

inline void lsb(unsigned long& a, uint64_t& b){
	_BitScanForward64(&a, b); b ^= (1ULL << a);
}
inline void msb(unsigned long& a, uint64_t& b){
	_BitScanReverse64(&a, b); b ^= (1ULL << a);
}

#endif