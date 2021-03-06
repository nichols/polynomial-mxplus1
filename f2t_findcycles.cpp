
#include "f2t_findcycles.h"
#include <cstdio>
#include <cstdint>



// find cycle in sequence starting at f using Brent's algorithm
// mu is the number of iterations until it becomces periodic
// lambda is the length of the period
// sigma is the stopping time
// returns 0 unless the iteration times out, in which case it
// returns the degree where it stopped
unsigned int f2t_findperiod( f2t_sequence_t f, unsigned int timeout, unsigned int *mu, unsigned int *lambda, unsigned int *sigma )
{
	f2t_sequence_t tortoise = f2t_sequence_t( f );	// tortoise
	f2t_sequence_t hare = f2t_sequence_t( f );
	hare.step( );									// hare	
	
	unsigned int i = 1;			// current power of 2
	*lambda = 1;				// period
	*mu = 0;					// time to begin periodic part
	*sigma = 0;
	unsigned int deg0 = tortoise.degree( );		// degree of initial poly
	
	// until the tortoise and hare are equal (or timeout)
	while( hare.count( ) < timeout && !hare.is_one( ) && tortoise != hare )
	{	
		
		//printf( "k= %6lu, ", k );
		//if( !( k % 8 ) ) printf( "\n" );
		
		
		// should we advance i to the next power of 2?
		if( i == *lambda )
		{
			tortoise = hare;
			i <<= 1;
			*lambda = 0;
		}
		
		// if this is the first term with degree < degree of initial poly,
		// update sigma
		if( !*sigma && hare.degree( ) < deg0 )
			*sigma = hare.count( );
			
		
		hare.step( );				// hare steps foward
		(*lambda)++;				// period counter
	}
	
	
	// why did we exit the loop?
	
	// if we hit 1...
	if( hare.is_one( ) )
	{
		// return mu = time to 1, lambda = 0
		*mu = hare.count( );
		*lambda = 0;
		return 0;
	}
	
	// otherwise...
	
	// if we timed out...
	if( hare.count( ) >= timeout )
	{
		*mu = 0;
		*lambda = 0;
		return hare.degree( );	// return the degree at which we timed out
	}
	
	// now we can be sure the sequence really does become periodic
	
	// lambda is the period of the sequence. We want to find the exact
	// point where the sequence becomes periodic.
	
	// set the tortoise at the beginning (f) and the hare lambda steps
	// ahead. Then step both forward together one at a time until they
	// agree
	
	tortoise = f;
	hare = f;
	
	// set the tortoise and hare (lambda) steps apart
	for( unsigned int j = 1; j <= *lambda; j++ )
		hare.step( );
	
	// now iterate until they're equal
	while( tortoise != hare )
	{	
		tortoise.step( );
		hare.step( );
	}
	
	*mu = tortoise.count( );
	return 0;
}



// This function tests one polynomial using f2t_findperiod, then outputs
// the information in a neat row of text
void f2t_run_and_print( f2t_sequence_t f, unsigned int timeout )
{
	unsigned int mu, lambda, sigma, d;
	
	f.print( );
	
	d = f2t_findperiod( f, timeout, &mu, &lambda, &sigma );
	
	if( sigma ) printf( ", %8u", sigma );
	else printf( ", %8s", "inf" );
	
	if( d ) printf( ", timeout(%u), d=%u\n", timeout, d );
	else printf( ", %8u, %8u\n", mu, lambda );
	
}





