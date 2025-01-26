#include <string.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"

#include "animacoes.h"

static Matriz_leds_config animacao[1];

Animacao obter_anim_padrao() {
    RGB_cod cor = cor_24bit_para_3double(0, 255, 0);

    Matriz_leds_config frame = {
        {cor, cor, cor, cor, cor},
        {cor, cor, cor, cor, cor},
        {cor, cor, cor, cor, cor},
        {cor, cor, cor, cor, cor},
        {cor, cor, cor, cor, cor},
    };
    memcpy(animacao[0], frame, sizeof(Matriz_leds_config));

    return (Animacao) {
        .frames = animacao,
        .tamanho = 1,
        .duracao_frame_ms = 200,
    };
}
