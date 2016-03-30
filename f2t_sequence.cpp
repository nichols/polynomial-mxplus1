#include "f2t_sequence.h"
#include "f2poly.h"
#include <cstdint>
#include <cstdio>




/**********************************************************************/
/**************** CONSTRUCTORS AND INITIALIZERS ***********************/
/**********************************************************************/


void f2t_sequence_t::setpoly( std::vector<uint64_t> a )
{
	poly = f2poly_t( a );
	stepcount = 0;
}


void f2t_sequence_t::setpoly( unsigned int l, uint64_t bottom )
{
	poly = f2poly_t( l, bottom );
	stepcount = 0;
}



/**********************************************************************/
/*************************** OTHER METHODS ****************************/
/**********************************************************************/


// apply mx+1 transformation
void f2t_sequence_t::step( )
{
	if( poly.parity( ) )
		poly = poly * multiplier + 1;
	
	poly.divide( );
	stepcount++;
}


void f2t_sequence_t::print( )
{
	poly.printdec( );
}


void f2t_sequence_t::print_sequence( unsigned int timeout )
{
	printf( "\ni = %6i, f = ", 0 );
	poly.print( );
	
	for( unsigned int i = 1; i <= timeout; i++ )
	{
		step( );
		printf( "\ni = %6u, f = ", i );
		poly.print( );
	}
	
}


void f2t_sequence_t::print_parity_sequence( unsigned int timeout )
{
	printf( "%i", parity( ) );
	
	for( unsigned int i = 1; i <= timeout; i++ )
		printf( "%i", parity( ) );
	
}


void f2t_sequence_t::print_sequence_degrees( unsigned int timeout, unsigned int gap )
{
	printf( "# %10s %10s\n", "i", "deg f" );
	printf( "  %10i %10i\n", 0, degree( ) );
	
	for( unsigned int i = 1; i <= timeout && !is_one( ); i++ )
	{
		step( );
		if( i % gap == 0 ) printf( "  %10i %10i\n", i, degree( ) );
	}
	printf( "\n\n" );
}


bool f2t_sequence_t::is_one( )
{
	return poly.is_one( );
}


bool f2t_sequence_t::operator==( const f2t_sequence_t &other ) const
{
	return poly == other.poly;
}


bool f2t_sequence_t::operator!=( const f2t_sequence_t &other ) const
{
	return !( *this == other );
}



