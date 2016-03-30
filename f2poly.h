/* f2poly
 * by Daniel Nichols (daniel.g.nichols@gmail.com)
 * 
 * Defines a class f2poly_t representing a polynomial in F_2[t]
 * (F_2 is the finite field of 2 elements)
 * 
 * Polynomial is stored as a vector of unsigned longs, with each bit
 * representing a coefficient
 * 
 */


#ifndef F2POLY_H
#define F2POLY_H

#include <cstdint>
#include <vector>


#define WORDLENGTH 64 

extern const uint64_t bits[WORDLENGTH]; // masks for each bit

unsigned int ilog2( uint64_t x );



class f2poly_t
{
	private:
		// vector of words representing a bit array
		std::vector<uint64_t> words;
		
	public:
		unsigned int degree;	// (most significant 1 bit)
		
		unsigned int size( ) { return words.size( ); }	// number of words used
		unsigned int find_degree( );					// set degree
		
		f2poly_t( );								 // zero polynomial
		f2poly_t( unsigned int l, uint64_t bottom ); // # words and bottom word
		f2poly_t( std::vector<uint64_t> a ); 		 // all words
		
		// these four functions are used to set (to 1), clear (to 0), toggle, or
		// check a specific digit in a bit array
		void setbit( unsigned int k );
		void clearbit( unsigned int k );
		void togglebit( unsigned int k );
		int checkbit( unsigned int k );
		
		uint64_t bottomword( );		// return least significant word

		void divide( );			// divide by t
		
		int parity( );			// return f(0)
		bool is_zero( );
		bool is_one( );
		
		void reset( );			// reset all words to zero
		
		// display polynomial in different formats
		void print( );
		void printhex( );
		void printdec( );
		void printpoly( );
		
		
		// operators
		bool operator==( const f2poly_t &other ) const;
		f2poly_t& operator+=( const f2poly_t &other );
		f2poly_t& operator+=( const uint64_t &a );
		f2poly_t& operator*=( const uint64_t &m );
		
		~f2poly_t( ) { }
};




/**********************************************************************/
/************************** BINARY OPERATORS **************************/
/**********************************************************************/
// uint64_t arguments here represent low degree polynomials (deg < 64)


inline const f2poly_t operator+( f2poly_t lhs, const f2poly_t& rhs ) {
	return f2poly_t( lhs ) += rhs;
}

inline const f2poly_t operator+( f2poly_t lhs, uint64_t rhs ) {
	return f2poly_t( lhs ) += rhs;
}
inline const f2poly_t operator+( uint64_t lhs, const f2poly_t& rhs ) {
	return rhs + lhs;
}

inline const f2poly_t operator*( f2poly_t lhs, uint64_t rhs ) {
	return f2poly_t( lhs ) *= rhs;
}

inline const f2poly_t operator*( uint64_t lhs, const f2poly_t& rhs ) {
	return rhs * lhs;
}





#endif
