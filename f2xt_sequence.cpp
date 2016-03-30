
#include "f2xt_sequence.h"
#include <cstdint>
#include <cstdio>



/**********************************************************************/
/**************** CONSTRUCTORS AND INITIALIZERS ***********************/
/**********************************************************************/


void f2xt_sequence_t::setpolys( std::vector<uint64_t> v0, std::vector<uint64_t> v1 )
{
	f0 = f2poly_t( v0 );
	f1 = f2poly_t( v1 );
	stepcount = 0;
}


void f2xt_sequence_t::setpolys( unsigned int l0, uint64_t b0, unsigned int l1, uint64_t b1 )
{
	f0 = f2poly_t( l0, b0 );
	f1 = f2poly_t( l1, b1 );
	stepcount = 0;
}



/**********************************************************************/
/*************************** OTHER METHODS ****************************/
/**********************************************************************/


bool f2xt_sequence_t::is_zero( )
{
	return f0.is_zero( ) && f1.is_zero( );
}


void f2xt_sequence_t::divide( )
{
	f0.divide( );
	f1.divide( );
}


void f2xt_sequence_t::step( )
{
	if( !is_zero( ) )
	{

		if( f0.parity( ) && f1.parity( ) ) // multiply
		{
			
			f2poly_t f0m0 = f0 * multiplier0;
			f2poly_t f0m1 = f0 * multiplier1;
			f2poly_t f1m0 = f1 * multiplier0;
			f2poly_t f1m1 = f1 * multiplier1;
			
			f2poly_t f1m1q = f1m1 * qpoly;
			
			f2poly_t f1m1t = f1m1 * 2;
			
			f0 = f0m0;
			f0 += f1m1q;
			f0 += add0;
			
			f1 = f0m1;
			f1 += f1m0;
			f1 += f1m1t;
			f1 += add1;
			
		}
		
		f0.divide( );
		f1.divide( );
		
	}
	
	stepcount++;
}


unsigned int f2xt_sequence_t::degree( )
{
	unsigned int d = f0.degree;
	if( f1.degree > d )
		d = f1.degree;
	
	return d;
}


void f2xt_sequence_t::print( )
{
	printf( "f0 = " );
	f0.print( );
	printf( "\nf1 = " );
	f1.print( );
	printf( "\n" );
	
}


void f2xt_sequence_t::print_short( )
{
	f0.printdec( );
	printf( " | " );
	f1.printdec( );
}


void f2xt_sequence_t::print_sequence( unsigned int timeout )
{
	printf( "i = %-6u: f0 = ", 0 );
	f0.print( );
	printf( "\n    %-6s  f1 = ", "" );
	f1.print( );
	printf( "\n\n" );
	
	for( unsigned int i = 1; i <= timeout && !is_zero( ); i++ )
	{
		step( );
		printf( "i = %-6u: f0 = ", i );
		f0.print( );
		printf( "\n    %-6s  f1 = ", "" );
		f1.print( );
		printf( "\n\n" );
	}
	
}


void f2xt_sequence_t::print_sequence_degrees( unsigned int timeout, unsigned int gap )
{
	printf( " %10s, %10s, %10s\n", "i", "deg f0", "deg f1" );
	printf( "%10i, %10i, %10i\n", 0, f0.degree, f1.degree );
	
	for( unsigned int i = 1; i <= timeout && !is_zero( ); i++ )
	{
		step( );
		if( i % gap == 0 ) printf( "%10i, %10i, %10i\n", i, f0.degree, f1.degree );
	}
	
}

void f2xt_sequence_t::print_parity_sequence( unsigned int timeout )
{
	printf( "%i", parity( ) );
	
	for( unsigned int i = 1; i <= timeout; i++ )
	{
		step( );
		printf( "%i", parity( ) );
		
	}
}


bool f2xt_sequence_t::operator==( const f2xt_sequence_t &other ) const
{
	return ( f0 == other.f0 && f1 == other.f1 );
}



bool f2xt_sequence_t::operator!=( const f2xt_sequence_t &other ) const
{
	return !( *this == other );
}

