#include "f2poly.h"
#include <cstdint>
#include <cstdio>
#include <vector>

// masks for each bit in word
const uint64_t bits[ 64 ] = { 1,2,4,8,16,32,64,128,256,512,1024,
2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,
4194304,8388608,16777216,33554432,67108864,134217728,268435456,
536870912,1073741824,2147483648,4294967296,8589934592,17179869184,
34359738368,68719476736,137438953472,274877906944,549755813888,
1099511627776,2199023255552,4398046511104,8796093022208,17592186044416,
35184372088832,70368744177664,140737488355328,281474976710656,
562949953421312,1125899906842624,2251799813685248,4503599627370496,
9007199254740992,18014398509481984,36028797018963968,72057594037927936,
144115188075855872,288230376151711744,576460752303423488,
1152921504606846976,2305843009213693952,4611686018427387904,
9223372036854775808 };



// ceil(log_2(x)) (used to find most significant nonzero bit)
unsigned int ilog2( uint64_t x )
{
	if( !x || x == 1 ) return 0;
	
	unsigned int l = 1;
	while( l <= WORDLENGTH && x >> l > 1) l++;
	return l;
}


// if the poly is newly created, or if something has been added which
// may result in a lower degree, this function calculates the new degree
// (and makes sure the vector is the right size)
unsigned int f2poly_t::find_degree( )
{
	unsigned int l = size( ) - 1;
	while( l > 0 && !words[ l ] )
		l--;
	
	words.resize( l + 1 );
	
	return WORDLENGTH * ( l ) + ilog2( words[ l ] );
}



/**********************************************************************/
/************************** CONSTRUCTORS ******************************/
/**********************************************************************/


// default constructor: create zero polynomial
f2poly_t::f2poly_t( ) : words( 1, 0 )
{
	degree = 0;
}


// constructor for bitarray
// l: number of words
// bottom: least significant word
// top word will be 1, all others 0
f2poly_t::f2poly_t( unsigned int l, uint64_t bottom ) : words( l, 0 )
{
	words[ 0 ] = bottom;
	
	if( l == 1 )
		degree = ilog2( bottom );
	else
	{
		words[ l - 1 ] = 1;
		degree = WORDLENGTH * ( l - 1 );
	}
}


// constructor for array with l words given as a vector argument
f2poly_t::f2poly_t( std::vector<uint64_t> a ) : words( a )
{
	degree = find_degree( );
}


uint64_t f2poly_t::bottomword( )
{
	return words[ 0 ];
}


/**********************************************************************/
/*********************** DIRECT BIT ACCESS ****************************/
/**********************************************************************/
// these four functions are used to set (to 1), clear (to 0), toggle, or
// check a specific digit in a bit array


void f2poly_t::setbit( unsigned int k )
{
	words[ k / WORDLENGTH] |= bits[ k % WORDLENGTH ];
}

void f2poly_t::clearbit( unsigned int k )                
{
	words[ k / WORDLENGTH ] &= ~bits[ k % WORDLENGTH ];
}

void f2poly_t::togglebit( unsigned int k )
{
	words[ k / WORDLENGTH ] ^= bits[ k % WORDLENGTH ];
}

int f2poly_t::checkbit( unsigned int k )
{
	return( ( words[ k / WORDLENGTH ] & bits[ k % WORDLENGTH ] ) != 0 );
}



/**********************************************************************/
/**************************** OPERATORS *******************************/
/**********************************************************************/


bool f2poly_t::operator==( const f2poly_t &other ) const
{
	if( degree != other.degree )
		return 0;
	
	return words == other.words;
}


// these operators add/multiply something to the current f2poly in-place



// add another f2poly
f2poly_t& f2poly_t::operator+=( const f2poly_t &other )
{
	// save original size of *this in case it changes later
	unsigned int l = size( );
	
	/* three cases:
		1. other has more words than *this (need to resize *this, copy high words, add low words)
		2. *this has more words than other (easy, just need to add low words)
		3. *this and other have same # of words (if they're the same degree, we may have to remove words and find the new degree)
	*/
	
	if( degree < other.degree )
	{
		degree = other.degree;
		
		// if other has extra words,
		if( size( ) < other.words.size( ) )
		{
			// resize *this
			words.resize( other.words.size( ) );
			
			// copy the extra words over (adding to zero)
			for( unsigned int k = l; k < size( ); k++ )
				words[ k ] = other.words[ k ];
			
		}
	}
	
	// now we add the low words which are nonzero in both polynomials
	
	// l = min( original size of *this, size of other )
	if( l > other.words.size( ) ) l = other.words.size( );
	
	for( unsigned int k = 0; k < l; k++ )
		words[ k ] ^= other.words[ k ];
	
	// lastly, if the degrees are exactly equal, some of the top bits will cancel
	if( other.degree == degree )
	{	
		// recalculate degree
		degree = find_degree( );
	}
	
	return *this;
}


// add a long (not wrapped in an f2poly)
f2poly_t& f2poly_t::operator+=( const uint64_t &a )
{
	words[ 0 ] ^= a;
	if( size( ) == 1 )
		degree = find_degree( );
		
	return *this;
}


// multiply by low degree polynomial m
f2poly_t& f2poly_t::operator*=( const uint64_t &m )
{
	// If l = 1 (i.e. the bitarray is a single word), we can just xor f
	// with itself shifted left by various values. But if not, we also
	// have to 'carry over' the bits at the edges of words.
	
	unsigned int md = ilog2( m );
	
	unsigned int l = words.size( );
	
	// do we need to increase the array size and add a new word? (word l)
	if( ( degree + md ) / WORDLENGTH > degree / WORDLENGTH )
	{
		uint64_t new_word = 0;
		
		// take highest (md) bits
		uint64_t carryover = words[ size( ) - 1 ] >> ( WORDLENGTH - md );
		
		
		// for each index i such that f_i == 1
		for( unsigned int i = 0; i < md; i++ )
		{
			if( m & bits[ md - i ] )
			{
				// shift carryover this much and add (xor)
				new_word ^= ( carryover >> i );	
			}
		}
		
		words.push_back( new_word );
	}
	
	// do words l-1 down to 1
	for( unsigned int k = l - 1; k > 0; k-- ) // start from highest word in f
	{
		// save a copy of current word
		uint64_t new_word = 0;
		
		// take highest (md) bits of next word
		uint64_t carryover = words[ k - 1 ] >> ( WORDLENGTH - md );	
		
		// for each index i such that f_i == 1
		for( unsigned int i = 0; i <= md; i++ )
			if( m & bits[ i ] )
			{
				new_word ^= ( words[ k ] << i ); // xor with itself shifted left
				new_word ^= ( carryover >> i );	// xor with top bits from next word
			}
			
		words[ k ] = new_word;
	}
	
	// do word 0
	uint64_t new_word = 0;
	for( unsigned int i = 0; i <= md; i++ )
		if( m & bits[ i ] )
			new_word ^= ( words[ 0 ] << i );
	words[ 0 ] = new_word;
	
	// update degree
	degree += md;
	
	return *this;
}



void f2poly_t::divide( )
{
	
	// do all words except the most significant, starting from word 0.
	unsigned int top = size( ) - 1;
	for( unsigned int k = 0; k < top; k++ )
	{
		// shift right, and shift over the lowest bit from the next word
		words[ k ] >>= 1;
		words[ k ] ^= ( words[ k + 1 ] % 2 ) ? bits[ WORDLENGTH - 1 ] : 0;
	}
	
	if( top > 0 && degree % WORDLENGTH == 0 ) // if the top word is just a 1
	{
		words.resize( top );	// shrink the vector
	}
	else
	{
		words[ top ] >>= 1; 	// otherwise, shift the top word
	}
	
	if( degree )
		degree--;
	
}


int f2poly_t::parity( )
{
	return checkbit( 0 );
}


bool f2poly_t::is_zero( )
{
	return size( ) == 1 && !words[ 0 ];
}


bool f2poly_t::is_one( )
{
	return size( ) == 1 && words[ 0 ] == 1;
}



/**********************************************************************/
/*************************** OTHER METHODS ****************************/
/**********************************************************************/


// set all words to 0
void f2poly_t::reset( )
{
	for( unsigned int k = 0; k < size( ); k++ )
		words[ k ] = 0;
	degree = 0;
}


// print array as list of words in binary form (little-endian)
void f2poly_t::print( )
{
	for( unsigned int k = 0; k <= degree; k++ )
	{
		if( k && k % WORDLENGTH == 0 ) printf( " . " );
		else if( k && k % 4 == 0 ) printf( " " );
		printf( "%i", checkbit( k ) );
	}
}


// print array as list of words in hex form
void f2poly_t::printhex( )
{
	printf( "%#lx", words[ 0 ] );
	for( unsigned int i = 1; i < size( ); i++ )
		printf( ".%#lx", words[ i ] );
}


// print array as list of words in integer form
void f2poly_t::printdec( )
{
	printf( "%lu", words[ 0 ] );
	for( unsigned int i = 1; i < size( ); i++ )
		printf( ".%lu", words[ i ] );
}


// print polynomial in expanded form
void f2poly_t::printpoly( )
{
	printf( "%i", checkbit( 0 ) );
	
	if( degree >= 1 )
		printf( " + %ix", checkbit( 1 ) );
	
	for( unsigned int i = 2; i < degree; i++ )
		printf( " + %ix^%i", checkbit( i ), i );
	
}




