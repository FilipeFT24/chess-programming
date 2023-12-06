#ifndef BITBOARD_H_INCLUDED
#define BITBOARD_H_INCLUDED

#include <intrin.h>
#include <iostream>
#include <vector>

using namespace std;

class Bitboard{
public:
	// Member functions (#0).
	static Bitboard& _get(){
		static Bitboard bitboard; return bitboard; // Guaranteed to be destroyed (instantiated on first use).
	}
	Bitboard      (Bitboard const&) = delete;      // Don't implement.
	void operator=(Bitboard const&) = delete;      // Don't implement.
	
	void print(uint64_t);


	// Member variables.
	vector<uint64_t> _BA_mask;
	vector<uint64_t> _KA_mask;
	vector<uint64_t> _NA_mask;
	vector<vector<uint64_t>> _PA_mask;
	vector<uint64_t> _RA_mask;
private:
	// Member functions (#0).
	Bitboard      ();
	// Member functions (#1).
	void BA_mask  ();
	void KA_mask  ();
	void NA_mask  ();
	void PA_mask  ();
	void RA_mask  ();
};

#ifdef USE_INLINING
	#ifdef _MSC_VER
		#define MMINLINE __forceinline
	#elif  define(__GNUC__)
		#define MMINLINE __inline__ __attribute__((always_inline))
	#else
		#define MMINLINE inline
	#endif
#endif

#ifndef VARIABLE_SHIFT
	#define MINIMAL_B_BIT_SHIFT(position) 55
	#define MINIMAL_R_BIT_SHIFT(position) 52
#else
	#define MINIMAL_B_BIT_SHIFT(position) MM_BShift[position]
	#define MINIMAL_R_BIT_SHIFT(position) MM_RShift[position]
#endif

#ifndef PERFECT_MAGIC_HASH
	#ifdef MINIMIZE_MAGIC
		#ifndef USE_INLINING
			#define BMagic(position, occupancy)
			#define RMagic(position, occupancy)
		#endif
	#else
		#ifndef USE_INLINING
			#define BMagic(position, occupancy)
			#define RMagic(position, occupancy)
		#endif
	#endif
#else
#endif

#define QMagic(position, occupancy)(BMagic(position, occupancy) | RMagic(position, occupancy))

#endif