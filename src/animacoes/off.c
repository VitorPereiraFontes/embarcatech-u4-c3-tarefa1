#include <string.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"

#include "animacoes.h"

static Matriz_leds_config animacao[1];

Animacao obter_anim_off() {
    RGB_cod off = {0,0,0};

    Matriz_leds_config frame1 = {
        {off,off,off,off,off},
        {off,off,off,off,off},
        {off,off,off,off,off},
        {off,off,off,off,off},
        {off,off,off,off,off},
    };

    memcpy(animacao[0], frame1, sizeof(frame1));

    return (Animacao) {
        .frames = animacao,
        .tamanho = 1,
        .duracao_frame_ms = 100,
        .frame_buzzer = -1,
        .freq_buzzer = 0,
    };
}
