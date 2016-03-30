/* f2t_main_allcycles
 * 
 * This program loops over a block of n elements of F_2[t] in lexicographical
 * order, starting from a specified polynomial. For each of these elements,
 * it computes the mx+1 trajectory sequence f, T(f), T^2(f), and searches
 * for a cycle using Brent's algorithm. If no cycle is found after a
 * specified maximum number of steps, it stops.
 * 
 * Parameter for the mx+1 map is specified as an environment variable:
 * F2T_M
 * (stored in binary form, i.e. the k-th bit is the coefficient of t^k)
 * 
 * Command line arguments: < l, bottom, n, timeout >
 * 		l: number of words in initial polynomial f
 * 		bottom: bottom word of initial polynomial f
 * 			( so f = t^{64*(l+1)-1} + bottom )
 * 		n: number of polynomials in block
 * 		timeout: maximum number of steps to calculate for each trajectory
 * 
 */


#include "f2t_sequence.h"
#include "f2t_findcycles.h"
#include <cstdlib>
#include <cstdio>
#include <cstdint>


// initialize starting polynomial with l words, all 0 except most significant (top)
// start there, and do n consecutive polynoimals
void findperiod_loop( uint64_t multiplier, int l, uint64_t bottom, unsigned int n, unsigned int timeout )
{
	f2t_sequence_t f = f2t_sequence_t( multiplier );
	f.setpoly( l, bottom );
	
	printf( "\nusing multiplier %lu \n", multiplier );
	printf( "calculating periods for %u consecutive inputs,\n", n );
	printf( "starting at " );
	f.print( );
	printf( "\n%5s, %8s, %8s, %8s\n", "f", "sigma", "mu", "lambda" );
	
	for( unsigned int i = 0; i < n; i++ )
	{	
		f.setpoly( l, ++bottom );
		
		f2t_run_and_print( f, timeout );
	}
}


int main( int argc, char **argv )
{
	if( argc < 4 )
	{
		printf( "not enough arguments\n" );
		return 0;
	}
	
	char *env_F2T_M = getenv( "F2T_M" );
	if( env_F2T_M == NULL )
	{
		printf( "Error: environment variable F2T_M undefined.\n" );
		return 1;
	}
	uint64_t m = strtoul( env_F2T_M, NULL, 0 );
	
	unsigned int l = strtoul( argv[ 1 ], NULL, 0 );
	uint64_t bottom = strtoul( argv[ 2 ], NULL, 0 );
	unsigned int n = strtoul( argv[ 3 ], NULL, 0 );
	unsigned int timeout = strtoul( argv[ 4 ], NULL, 0 );
	
	findperiod_loop( m, l, bottom, n, timeout );

	
}
