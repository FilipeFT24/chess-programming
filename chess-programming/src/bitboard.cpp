#include "bitboard.h"

constexpr uint64_t FileA = 0x0101010101010101ULL;
constexpr uint64_t Rank1 = 0xFF00000000000000ULL;
constexpr uint64_t DiagX = 0x0102040810204080ULL;
constexpr uint64_t DiagY = 0x8040201008040201ULL;

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
const vector<pair<int, int>> X_ij{
	{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {6, 7}, {7, 7},
	{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 6}, {7, 6},
	{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 5}, {7, 5},
	{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4},
	{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3},
	{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2},
	{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1},
	{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}
};
const vector<uint64_t> File{
	FileA << (0),
	FileA << (1),
	FileA << (2),
	FileA << (3),
	FileA << (4),
	FileA << (5),
	FileA << (6),
	FileA << (7)
};
const vector<uint64_t> Rank{
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


Bitboard::Bitboard() : _BA_mask(64, 0ULL), _KA_mask(64, 0ULL), _NA_mask(64, 0ULL), _PA_mask(2, vector<uint64_t>(64, 0ULL)), _RA_mask(64, 0ULL){
	BA_mask();
	KA_mask();
	NA_mask();
	PA_mask();
	RA_mask();
}
void Bitboard::BA_mask(){
	for(vector<uint64_t>::iterator i = _BA_mask.begin(); i != _BA_mask.end(); ++i){
		*i |= (Diag1(get<0>(X_ij[i-_BA_mask.begin()])-get<1>(X_ij[i-_BA_mask.begin()])  )) & ~((1ULL << (i-_BA_mask.begin())) | 0xFF818181818181FFULL); // i-j   = const
		*i |= (Diag2(get<0>(X_ij[i-_BA_mask.begin()])+get<1>(X_ij[i-_BA_mask.begin()])-7)) & ~((1ULL << (i-_BA_mask.begin())) | 0xFF818181818181FFULL); // i+j-7 = const
	}
}
void Bitboard::KA_mask(){
	for(vector<uint64_t>::iterator i = _KA_mask.begin(); i != _KA_mask.end(); ++i){
		*i |= ((1ULL << (i-_KA_mask.begin())) >>  1) & ~(File[7]);
		*i |= ((1ULL << (i-_KA_mask.begin())) >>  7) & ~(File[0]);
		*i |= ((1ULL << (i-_KA_mask.begin())) >>  8);
		*i |= ((1ULL << (i-_KA_mask.begin())) >>  9) & ~(File[7]);
		*i |= ((1ULL << (i-_KA_mask.begin())) <<  1) & ~(File[0]);
		*i |= ((1ULL << (i-_KA_mask.begin())) <<  7) & ~(File[7]);
		*i |= ((1ULL << (i-_KA_mask.begin())) <<  8);
		*i |= ((1ULL << (i-_KA_mask.begin())) <<  9) & ~(File[0]);
	}
}
void Bitboard::NA_mask(){
	for(vector<uint64_t>::iterator i = _NA_mask.begin(); i != _NA_mask.end(); ++i){
		*i |= ((1ULL << (i-_NA_mask.begin())) >>  6) & ~(File[0] | File[1]);
		*i |= ((1ULL << (i-_NA_mask.begin())) >> 10) & ~(File[6] | File[7]);
		*i |= ((1ULL << (i-_NA_mask.begin())) >> 15) & ~(File[0]);
		*i |= ((1ULL << (i-_NA_mask.begin())) >> 17) & ~(File[7]);
		*i |= ((1ULL << (i-_NA_mask.begin())) <<  6) & ~(File[6] | File[7]);
		*i |= ((1ULL << (i-_NA_mask.begin())) << 10) & ~(File[0] | File[1]);
		*i |= ((1ULL << (i-_NA_mask.begin())) << 15) & ~(File[7]);
		*i |= ((1ULL << (i-_NA_mask.begin())) << 17) & ~(File[0]);
	}
}
void Bitboard::PA_mask(){
	for(vector<uint64_t>::iterator i = _PA_mask[0].begin()+8; i != _PA_mask[0].end()-8; ++i){
		*i |= ((1ULL << (i-_PA_mask[0].begin())) >>  7) & ~(File[0]);
		*i |= ((1ULL << (i-_PA_mask[0].begin())) >>  9) & ~(File[7]);
	}
	for(vector<uint64_t>::iterator i = _PA_mask[1].begin()+8; i != _PA_mask[1].end()-8; ++i){
		*i |= ((1ULL << (i-_PA_mask[1].begin())) <<  7) & ~(File[7]);
		*i |= ((1ULL << (i-_PA_mask[1].begin())) <<  9) & ~(File[0]);
	}
}
void Bitboard::RA_mask(){
	for(vector<uint64_t>::iterator i = _RA_mask.begin(); i != _RA_mask.end(); ++i){
		*i |= File[get<0>(X_ij[i-_RA_mask.begin()])] & ~((1ULL << (i-_RA_mask.begin())) | Rank[0] | Rank[7]);
		*i |= Rank[get<1>(X_ij[i-_RA_mask.begin()])] & ~((1ULL << (i-_RA_mask.begin())) | File[0] | File[7]);
	}
}
/*
*/
void Bitboard::print(uint64_t b){
	for(int r = 0; r < 8 ; ++r){
		cout << " " << 8-r << "   ";
		for(int f = 0; f < 8; ++f){
			cout << (!(b & (1ULL << (r*8+f))) ? 0 : 1) << " ";
		}
		cout << endl;
	}
	cout << endl << "     A B C D E F G H: " << b << endl << endl << endl;
}