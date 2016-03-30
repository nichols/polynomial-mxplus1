/* f2xt_main_print_degrees
 * 
 * This program prints the mx+1 degree sequence of a given polynomial
 * f, up to a specified maximum number of terms.
 * 
 * Parameters for the mx+1 map is specified as an environment variable:
 * F2XT_M0		multiplier m = m0 + xm1
 * F2XT_M1
 * 
 * F2XT_A0		adjustment a = a0 + xa1
 * F2XT_A1
 * 
 * F2XT_Q		quotient polynomial; ring is F_2[x,t] / (x^2 + tx + q(t))
 * 
 * (all stored as bits in a long, i.e. the k-th bit is the coefficient of t^k)
 * 
 * Command line arguments: < b0, b1, timeout, gap >
 * 		b0, b1: initial polynomial f = b0 + xb1
 * 		timeout: maximum number of steps to calculate
 * 		gap: skip this many steps between output
 * 
 */
 
 
#include "f2xt_sequence.h"
#include <cstdint>
#include <cstdlib>



int main( int argc, char **argv )
{
	if( argc < 5 ) return 0;
	
	uint64_t b0 = strtoul( argv[ 1 ], NULL, 0 );
	uint64_t b1 = strtoul( argv[ 2 ], NULL, 0 );
	unsigned int timeout = strtoul( argv[ 3 ], NULL, 0 );
	unsigned int gap = strtoul( argv[ 4 ], NULL, 0 );
	
	uint64_t m0 = strtoul( getenv( "F2XT_M0" ), NULL, 0 );
	uint64_t m1 = strtoul( getenv( "F2XT_M1" ), NULL, 0 );
	uint64_t a0 = strtoul( getenv( "F2XT_A0" ), NULL, 0 );
	uint64_t a1 = strtoul( getenv( "F2XT_A1" ), NULL, 0 );
	uint64_t q = strtoul( getenv( "F2XT_Q" ), NULL, 0 );
	
	f2xt_sequence_t f( m0, m1, a0, a1, q );
	f.setpolys( 1, b0, 1, b1 );
	
	f.print_sequence_degrees( timeout, gap );
	
}
