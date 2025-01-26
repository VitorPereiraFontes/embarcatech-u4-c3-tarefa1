#ifndef _BUZZER_H
#define _BUZZER_H

#include <stdint.h>

typedef struct Buzzer {
	uint pin;
    bool is_playing;
} Buzzer;

void Buzzer_init(Buzzer *bz, uint pin);
void Buzzer_deinit(Buzzer *bz);
void Buzzer_play(Buzzer *bz, uint32_t frequency, uint duration_ms);
void Buzzer_play_start(Buzzer *bz, uint32_t frequency);
void Buzzer_play_stop(Buzzer *bz);

#endif
