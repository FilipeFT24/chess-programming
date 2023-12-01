#include "bitboard.h"

void BB::print(uint64_t b){
	for(int r = 0; r < 8 ; ++r){
		cout << " " << 8-r << "   ";
		for(int f = 0; f < 8; ++f){
			cout << (!(b & (1ULL << (r*8+f))) ? 0 : 1) << " ";
		}
		cout << endl;
	}
	cout << endl << "     A B C D E F G H: " << b << endl << endl << endl;
}

void BB::init_AT(){
	init_BA();
	init_KA();
	init_NA();
	init_PA();
	init_RA();
	init_QA();
}
void BB::init_BA(){
	for(vector<uint64_t>::iterator i = _BA.begin(); i != _BA.end(); ++i){
		*i |= (Diag1(get<0>(X_ij[i-_BA.begin()])-get<1>(X_ij[i-_BA.begin()])  )) & ~((1ULL << (i-_BA.begin())) | 0xFF818181818181FFULL); // i-j   = const
		*i |= (Diag2(get<0>(X_ij[i-_BA.begin()])+get<1>(X_ij[i-_BA.begin()])-7)) & ~((1ULL << (i-_BA.begin())) | 0xFF818181818181FFULL); // i+j-7 = const
	}
}
void BB::init_KA(){
	for(vector<uint64_t>::iterator i = _KA.begin(); i != _KA.end(); ++i){
		*i |= ((1ULL << (i-_KA.begin())) >>  1) & ~(File[7]);
		*i |= ((1ULL << (i-_KA.begin())) >>  7) & ~(File[0]);
		*i |= ((1ULL << (i-_KA.begin())) >>  8);
		*i |= ((1ULL << (i-_KA.begin())) >>  9) & ~(File[7]);
		*i |= ((1ULL << (i-_KA.begin())) <<  1) & ~(File[0]);
		*i |= ((1ULL << (i-_KA.begin())) <<  7) & ~(File[7]);
		*i |= ((1ULL << (i-_KA.begin())) <<  8);
		*i |= ((1ULL << (i-_KA.begin())) <<  9) & ~(File[0]);
	}
}
void BB::init_NA(){
	for(vector<uint64_t>::iterator i = _NA.begin(); i != _NA.end(); ++i){
		*i |= ((1ULL << (i-_NA.begin())) >>  6) & ~(File[0] | File[1]);
		*i |= ((1ULL << (i-_NA.begin())) >> 10) & ~(File[6] | File[7]);
		*i |= ((1ULL << (i-_NA.begin())) >> 15) & ~(File[0]);
		*i |= ((1ULL << (i-_NA.begin())) >> 17) & ~(File[7]);
		*i |= ((1ULL << (i-_NA.begin())) <<  6) & ~(File[6] | File[7]);
		*i |= ((1ULL << (i-_NA.begin())) << 10) & ~(File[0] | File[1]);
		*i |= ((1ULL << (i-_NA.begin())) << 15) & ~(File[7]);
		*i |= ((1ULL << (i-_NA.begin())) << 17) & ~(File[0]);
	}
}
void BB::init_PA(){
	for(vector<uint64_t>::iterator i = _PA[0].begin()+8; i != _PA[0].end()-8; ++i){
		*i |= ((1ULL << (i-_PA[0].begin())) >>  7) & ~(File[0]);
		*i |= ((1ULL << (i-_PA[0].begin())) >>  9) & ~(File[7]);
	}
	for(vector<uint64_t>::iterator i = _PA[1].begin()+8; i != _PA[1].end()-8; ++i){
		*i |= ((1ULL << (i-_PA[1].begin())) <<  7) & ~(File[7]);
		*i |= ((1ULL << (i-_PA[1].begin())) <<  9) & ~(File[0]);
	}
}
void BB::init_QA(){
	for(vector<uint64_t>::iterator i = _QA.begin(); i != _QA.end(); ++i){
		*i |= _BA[i-_QA.begin()] | _RA[i-_QA.begin()];
	}
}
void BB::init_RA(){
	for(vector<uint64_t>::iterator i = _RA.begin(); i != _RA.end(); ++i){
		*i |= File[get<0>(X_ij[i-_RA.begin()])] & ~((1ULL << (i-_RA.begin())) | Rank[0] | Rank[7]);
		*i |= Rank[get<1>(X_ij[i-_RA.begin()])] & ~((1ULL << (i-_RA.begin())) | File[0] | File[7]);
	}
}