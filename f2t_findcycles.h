#ifndef F2T_FINDCYCLES_H
#define F2T_FINDCYCLES_H

#include "f2t_sequence.h"
#include <cstdint>

// find cycle in sequence starting at f using Brent's algorithm
// mu is the number of iterations until it becomces periodic
// lambda is the length of the period
// returns 0 unless the iteration times out, in which case it
// returns the degree where it stopped
unsigned int f2t_findperiod( f2t_sequence_t f, unsigned int timeout, unsigned int *mu, unsigned int *lambda );


// This function tests one polynomial using f2t_findperiod, then outputs
// the information in a neat row of text
void f2t_run_and_print( f2t_sequence_t f, unsigned int timeout );





#endif
