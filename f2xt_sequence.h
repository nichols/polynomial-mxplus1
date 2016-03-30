/* f2xt_sequence_t
 * by Daniel Nichols (daniel.g.nichols@gmail.com)
 * 
 * This class represents an mx+1 trajectory in F_2[x,t]/(x^2 + tx + q(t)).
 * That is, a sequence x, T(x), T^2(x), ..., T^k(x), ...
 * where T(x) is the mx+1 map in F_2[x,t]/(x^2 + tx + q(t)).
 * 
 * We store the current element f in F_2[x,t]/(), as well as the number of
 * steps so far and the multiplier polynomial m
 * 
 */


#ifndef F2XT_SEQUENCE_H
#define F2XT_SEQUENCE_H

#include "f2poly.h"
#include <cstdint>
#include <vector>


class f2xt_sequence_t
{
	private:
		f2poly_t f0;
		f2poly_t f1;
		
		uint64_t multiplier0;
		uint64_t multiplier1;	// multiplier is m = m0(t) + xm1(t)
		
		uint64_t add0;
		uint64_t add1;			// perturbation is a = a0 + xa1
		
		uint64_t qpoly;			// quotient polynomial q(t)
		
		unsigned int stepcount;
		
	public:
		f2xt_sequence_t( )
			: multiplier0( 0 ), multiplier1( 0 ), add0( 0 ), add1( 0 ), qpoly( 2 ) { };
		f2xt_sequence_t( uint64_t m0, uint64_t m1, uint64_t a0, uint64_t a1, uint64_t q )
			: multiplier0( m0 ), multiplier1( m1 ), add0( a0 ), add1( a1 ), qpoly( q ) { }; 
		
		// set f0 and f1, either as vectors of words or with l,b
		void setpolys( std::vector<uint64_t> v0, std::vector<uint64_t> v1 );
		void setpolys( unsigned int l0, uint64_t b0, unsigned int l1, uint64_t b1 );
		
		unsigned int count( ) { return stepcount; }
		unsigned int degree( );
		bool is_zero( );
		
		void divide( ); // divide by t
		void step( );	// apply mx+1 map
		
		// in this setting, "parity" is an element of { 0, 1, x, 1 + x }
		int parity() { return f0.parity( ) + ( f1.parity( ) << 1 ); }
		
		// display current polynomial
		void print( );
		void print_short( );
		
		// print sequences
		void print_sequence( unsigned int timeout );
		void print_sequence_degrees( unsigned int timeout, unsigned int gap );
		void print_parity_sequence( unsigned int timeout );
		
		bool operator==( const f2xt_sequence_t &other ) const;
		bool operator!=( const f2xt_sequence_t &other ) const;
		
		~f2xt_sequence_t( ) { };
};














#endif
