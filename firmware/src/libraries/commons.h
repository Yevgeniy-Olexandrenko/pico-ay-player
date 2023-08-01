#ifndef _COMMONS_H_
#define _COMMONS_H_

// bits manipulations
#define set_bit(sfr, bit) (  (sfr) |=  _BV(bit) )
#define clr_bit(sfr, bit) (  (sfr) &= ~_BV(bit) )
#define isb_set(sfr, bit) (  (sfr) &   _BV(bit) )
#define isb_clr(sfr, bit) (!((sfr) &   _BV(bit)))
#define set_bit(sfr, bit, val) \
    {                          \
        if (bool(val))         \
            set_bit(sfr, bit); \
        else                   \
            res_bit(sfr, bit); \
    }

// TODO

#endif // _COMMONS_H_
