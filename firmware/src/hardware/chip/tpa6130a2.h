// -----------------------------------------------------------------------------
// TPA6130A2 Chip (Headphone Amplifier)                                completed
// -----------------------------------------------------------------------------

#ifndef _TPA6130A2_H_
#define _TPA6130A2_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "../../arduino.h"

bool    amp_init         ();
void    amp_set_volume   (uint8_t volume);
void    amp_set_mute     (bool yes);
void    amp_set_shutdown (bool yes);
uint8_t amp_get_volume   ();
bool    amp_get_mute     ();
bool    amp_get_shutdown ();

#ifdef __cplusplus
}
#endif
#endif // _TPA6130A2_H_
