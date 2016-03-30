/* f2t_sequence_t
 * by Daniel Nichols (daniel.g.nichols@gmail.com)
 * 
 * This class represents an mx+1 trajectory in F_2[t]. That is, a sequence
 * x, T(x), T^2(x), ..., T^k(x), ...
 * where T(x) is the mx+1 map
 * 
 * We store the current element f in F_2[t], as well as the number of
 * steps so far and the multiplier polynomial m in F_2[t]
 * 
 */



#ifndef F2T_SEQUENCE_H
#define F2T_SEQUENCE_H

#include "f2poly.h"
#include <cstdint>
#include <vector>


class f2t_sequence_t
{
	private:
		f2poly_t poly;			// current point in the trajectory
		
		uint64_t multiplier;	// m in F_2[t] used to define mx+1 map
		
		unsigned int stepcount;	// number of steps taken so far
		
	public:
		f2t_sequence_t( ) {};
		f2t_sequence_t( uint64_t m ) : multiplier( m ) { }
		f2t_sequence_t( uint64_t m, f2poly_t f ) : poly( f ), multiplier( m ), stepcount( 0 ) { }
		
		// initialize polynomial from list of words...
		void setpoly( std::vector<uint64_t> a );
		
		// ... or from bottom word and number of words
		void setpoly( unsigned int l, uint64_t bottom );
		
		// apply mx+1 map to move to next element of sequence
		void step( );
		
		
		unsigned int count( ) { return stepcount; }
		unsigned int degree( ) { return poly.degree; }
		int parity( ) { return poly.parity( ); }
		void reset_count( ) { stepcount = 0; }
		uint64_t bottomword( ) { return poly.bottomword( );	}
		bool is_one( );
		
		void print( ); // print f
		
		// print all elements of sequence until number of steps reaches timeout
		void print_sequence( unsigned int timeout );
		
		// print list of degrees until number of steps reaches timeout
		void print_sequence_degrees( unsigned int timeout, unsigned int gap );
		
		// print list of parities until number of steps reaches timeout
		void print_parity_sequence( unsigned int timeout );
		
		
		bool operator==( const f2t_sequence_t &other ) const;
		bool operator!=( const f2t_sequence_t &other ) const;
		
		
		~f2t_sequence_t( ) { };
};














#endif
