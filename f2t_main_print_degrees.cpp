/* f2t_main_print_degrees
 * 
 * This program prints the mx+1 degree sequence of a given polynomial
 * f up to a specified number of terms.
 * 
 * Parameter for the mx+1 map is specified as an environment variable:
 * F2T_M
 * (stored in binary form, i.e. the k-th bit is the coefficient of t^k)
 * 
 * Command line arguments: < l, bottom, timeout >
 * 		l: number of words in initial polynomial f
 * 		bottom: bottom word of initial polynomial f
 * 			( so f = t^{64*(l+1)-1} + bottom )
 * 		timeout: maximum number of steps to calculate
 * 
 */


#include "f2t_sequence.h"
#include <cstdint>
#include <cstdlib>



int main( int argc, char **argv )
{
	
	if( argc < 4 ) return 0;
	
	uint64_t b = strtoul( argv[ 1 ], NULL, 0 );
	unsigned int timeout = strtoul( argv[ 2 ], NULL, 0 );
	unsigned int gap = strtoul( argv[ 3 ], NULL, 0 );
	
	uint64_t m = strtoul( getenv( "F2T_M" ), NULL, 0 );
	
	f2t_sequence_t f( m );
	f.setpoly( 1, b );
	
	f.print_sequence_degrees( timeout, gap );
	
}
