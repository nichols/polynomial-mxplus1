/* f2t_main_singlecycle
 * 
 * This program computes the mx+1 trajectory sequence of a given polynomial
 * f, and searches for a cycle using Brent's algorithm. If no cycle is
 * found after a specified maximum number of steps, it stops.
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
#include "f2t_findcycles.h"
#include <cstdlib>
#include <cstdio>
#include <cstdint>



int main( int argc, char **argv )
{
	
	if( argc < 4 ) return 0;
	
	char *env_F2T_M = getenv( "F2T_M" );
	if( env_F2T_M == NULL )
	{
		printf( "Error: environment variable F2T_M undefined.\n" );
		return 1;
	}
	uint64_t m = strtoul( env_F2T_M, NULL, 0 );
	
	unsigned int l = strtoul( argv[ 1 ], NULL, 0 );
	uint64_t bottom = strtoul( argv[ 2 ], NULL, 0 );
	unsigned int timeout = strtoul( argv[ 3 ], NULL, 0 );
	
	f2t_sequence_t f( m );
	f.setpoly( l, bottom );
	
	f2t_run_and_print( f, timeout );
	
}
