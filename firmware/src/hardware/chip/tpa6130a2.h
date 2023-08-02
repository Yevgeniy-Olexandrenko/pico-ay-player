// -----------------------------------------------------------------------------
// TPA6130A2 Chip
// -----------------------------------------------------------------------------

#ifndef _TPA6130A2_H_
#define _TPA6130A2_H_

#include "../../arduino.h"

bool    tpa6130a2_init();
void    tpa6130a2_set_volume(uint8_t volume);
void    tpa6130a2_set_mute(bool yes);
void    tpa6130a2_set_shutdown(bool yes);
uint8_t tpa6130a2_get_volume();
bool    tpa6130a2_get_mute();
bool    tpa6130a2_get_shutdown();

#endif // _TPA6130A2_H_
