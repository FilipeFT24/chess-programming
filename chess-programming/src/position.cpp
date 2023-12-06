#include "position.h"

Position::Position(){
	_BOcc = 0x000000000000FFFFULL;
	_BP   = 0x000000000000FF00ULL;
	_BN   = 0x0000000000000042ULL;
	_BB   = 0x0000000000000024ULL;
	_BR   = 0x0000000000000081ULL;
	_BQ   = 0x0000000000000008ULL;
	_BK   = 0x0000000000000010ULL;
	_WOcc = 0xFFFF000000000000ULL;
	_WP   = 0x00FF000000000000ULL;
	_WN   = 0x4200000000000000ULL;
	_WB   = 0x2400000000000000ULL;
	_WR   = 0x8100000000000000ULL;
	_WQ   = 0x0800000000000000ULL;
	_WK   = 0x1000000000000000ULL;
	_BK_C = 1;
	_WK_C = 1;
	_BQ_C = 1;
	_WQ_C = 1;
	_Turn = 1;
	_BA   = _get_BA();
	_WA   = _get_WA();
}
uint64_t Position::_get_BA() const{
	unsigned long a = 0UL;

	uint64_t BA = 0ULL;
	
	for(uint64_t b = _BP; __popcnt64(b) > 0; BA |= Bitboard::_get()._PA_mask[1][a]){lsb(a, b);}
	for(uint64_t b = _BN; __popcnt64(b) > 0; BA |= Bitboard::_get()._NA_mask   [a]){lsb(a, b);}
	for(uint64_t b = _BK; __popcnt64(b) > 0; BA |= Bitboard::_get()._KA_mask   [a]){lsb(a, b);}

	return BA;
}
uint64_t Position::_get_WA() const{
	unsigned long a = 0UL;

	uint64_t WA = 0ULL;

	for(uint64_t b = _WP; __popcnt64(b) > 0; WA |= Bitboard::_get()._PA_mask[0][a]){lsb(a, b);}
	for(uint64_t b = _WN; __popcnt64(b) > 0; WA |= Bitboard::_get()._NA_mask   [a]){lsb(a, b);}
	for(uint64_t b = _WK; __popcnt64(b) > 0; WA |= Bitboard::_get()._KA_mask   [a]){lsb(a, b);}

	return WA;
}