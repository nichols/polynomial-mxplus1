/* f2xt_main_allcycles
 * 
 * This program loops over a block of elements of F_2[x,t]/(x^2+tx+q(t))
 * in lexicographical order, starting from a specified polynomial. For
 * each of these elements, it computes the mx+1 trajectory sequence
 * f, T(f), T^2(f), and searches for a cycle using Brent's algorithm. If
 * no cycle is found after a specified maximum number of steps, it stops.
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
 * Command line arguments: < b0, b1, n, timeout >
 * 		b0, b1: initial polynomial f = b0 + xb1
 * 		n: block width
 * 			(i.e. check f0 + f1x for n choices of f0 and n choices of f1)
 * 		timeout: maximum number of steps to calculate for each trajectory
 * 
 */


#include "f2xt_sequence.h"
#include "f2xt_findcycles.h"
#include <cstdlib>
#include <cstdio>
#include <cstdint>


// initialize starting polynomial with l words, all 0 except most significant (top)
// start there, and do n consecutive polynoimals
void findperiod_loop( uint64_t m0, uint64_t m1, uint64_t a0, uint64_t a1, uint64_t q, uint64_t b0, uint64_t b1, unsigned int n0, unsigned int n1, unsigned int timeout )
{
	f2xt_sequence_t f = f2xt_sequence_t( m0, m1, a0, a1, q );
	f.setpolys( 1, b0, 1, b1 );
	
	printf( "\nusing multiplier %lu + x %lu \n", m0, m1 );
	printf( "calculating periods for %u x %u block of inputs,\n", n0, n1 );
	printf( "starting at " );
	f.print_short( );
	printf( "\n%5s, %8s, %8s, %8s\n", "f", "sigma", "mu", "lambda" );
	
	for( unsigned int j = 1; j <= n0; j++ )
	{
		uint64_t b1copy = b1;
		for( unsigned int i = 1; i <= n1; i++ )
		{	
			f.setpolys( 1, b0, 1, b1copy++ );
			
			f2xt_run_and_print( f, timeout );
		}
		b0++;
		
	}
}


int main( int argc, char **argv )
{
	if( argc < 5 )
	{
		printf( "not enough arguments\n" );
		return 0;
	}
	
	char *env_F2XT_M0 = getenv( "F2XT_M0" );
	char *env_F2XT_M1 = getenv( "F2XT_M1" );
	char *env_F2XT_A0 = getenv( "F2XT_A0" );
	char *env_F2XT_A1 = getenv( "F2XT_A1" );
	char *env_F2XT_Q = getenv( "F2XT_Q" );
	if( env_F2XT_M0 == NULL || env_F2XT_M1 == NULL || env_F2XT_A0 == NULL
	|| env_F2XT_A1 == NULL || env_F2XT_Q == NULL )
	{
		printf( "Error: environment variable(s) undefined.\n" );
		return 1;
	}
	
	uint64_t m0 = strtoul( env_F2XT_M0, NULL, 0 );
	uint64_t m1 = strtoul( env_F2XT_M1, NULL, 0 );
	uint64_t a0 = strtoul( env_F2XT_A0, NULL, 0 );
	uint64_t a1 = strtoul( env_F2XT_A1, NULL, 0 );
	uint64_t q = strtoul( env_F2XT_Q, NULL, 0 );
	
	
	uint64_t b0 = strtoul( argv[ 1 ], NULL, 0 );
	uint64_t b1 = strtoul( argv[ 2 ], NULL, 0 );
	unsigned int n = strtoul( argv[ 3 ], NULL, 0 );
	unsigned int timeout = strtoul( argv[ 4 ], NULL, 0 );
	
	unsigned int n0 = n;
	unsigned int n1 = n;
	
	
	findperiod_loop( m0, m1, a0, a1, q, b0, b1, n0, n1, timeout );

	
}
