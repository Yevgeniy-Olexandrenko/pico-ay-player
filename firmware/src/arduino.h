#ifndef _COMMONS_H_
#define _COMMONS_H_

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

// bits manipulations
#define set_bit(sfr, bit) (  (sfr) |=  _BV(bit) )
#define clr_bit(sfr, bit) (  (sfr) &= ~_BV(bit) )
#define isb_set(sfr, bit) (  (sfr) &   _BV(bit) )
#define isb_clr(sfr, bit) (!((sfr) &   _BV(bit)))
#define upd_bit(sfr, bit, val) \
    {                          \
        if (val)               \
            set_bit(sfr, bit); \
        else                   \
            res_bit(sfr, bit); \
    }

// TODO

#endif // _COMMONS_H_
