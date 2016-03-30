/* f2xt_main_singlecycle
 * 
 * This program computes the mx+1 trajectory sequence of a given polynomial
 * f, and searches for a cycle using Brent's algorithm. If no cycle is
 * found after a specified maximum number of steps, it stops.
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
 * Command line arguments: < b0, b1, timeout >
 * 		b0, b1: initial polynomial f = b0 + xb1
 * 		timeout: maximum number of steps to calculate
 * 
 */


#include "f2xt_sequence.h"
#include "f2xt_findcycles.h"
#include <cstdlib>
#include <cstdio>
#include <cstdint>


int main( int argc, char **argv )
{
	
	if( argc < 4 )
	{
		printf( "not enough arguments\n" );
		return 0;
	}
	
	uint64_t b0 = strtoul( argv[ 1 ], NULL, 0 );
	uint64_t b1 = strtoul( argv[ 2 ], NULL, 0 );
	unsigned int timeout = strtoul( argv[ 3 ], NULL, 0 );
	
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
	
	f2xt_sequence_t f( m0, m1, a0, a1, q );
	f.setpolys( 1, b0, 1, b1 );
	
	f2xt_run_and_print( f, timeout );
	
}
