#ifndef F2XT_FINDCYCLES_H
#define F2XT_FINDCYCLES_H

#include "f2xt_sequence.h"
#include <cstdint>

// find cycle in sequence starting at f using Brent's algorithm
// mu is the number of iterations until it becomces periodic
// lambda is the length of the period
// returns 0 unless the iteration times out, in which case it
// returns the degree where it stopped
unsigned int f2xt_findperiod( f2xt_sequence_t f, unsigned int timeout, unsigned int *mu, unsigned int *lambda );


void f2xt_run_and_print( f2xt_sequence_t f, unsigned int timeout );






#endif
