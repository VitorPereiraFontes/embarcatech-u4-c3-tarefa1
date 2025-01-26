#include <string.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"

#include "animacoes.h"

static Matriz_leds_config animacao[3];

Animacao obter_anim_coracao_pulsante() {
    RGB_cod vermelho_brilhante = cor_24bit_para_3double(255,0,0); // Vermelho vivo
    RGB_cod vermelho_fade = cor_24bit_para_3double(153,0,0);      // Vermelho mais escuro
    RGB_cod vermelho_apagado = cor_24bit_para_3double(77,0,0);    // Vermelho bem fraco
    RGB_cod off = {0,0,0};                                        // LEDs apagados

    // Coração apagado
    Matriz_leds_config frame1 = {
        {off, off, vermelho_apagado, off, off},
        {off, vermelho_apagado, vermelho_apagado, vermelho_apagado, off},
        {vermelho_apagado, vermelho_apagado, vermelho_apagado, vermelho_apagado, vermelho_apagado},
        {off, vermelho_apagado, vermelho_apagado, vermelho_apagado, off},
        {off, off, vermelho_apagado, off, off}
    };

    // Coração intermediário
    Matriz_leds_config frame2 = {
        {off, off, vermelho_fade, off, off},
        {off, vermelho_fade, vermelho_fade, vermelho_fade, off},
        {vermelho_fade, vermelho_fade, vermelho_fade, vermelho_fade, vermelho_fade},
        {off, vermelho_fade, vermelho_fade, vermelho_fade, off},
        {off, off, vermelho_fade, off, off}
    };

    // Coração brilhante
    Matriz_leds_config frame3 = {
        {off, off, vermelho_brilhante, off, off},
        {off, vermelho_brilhante, vermelho_brilhante, vermelho_brilhante, off},
        {vermelho_brilhante, vermelho_brilhante, vermelho_brilhante, vermelho_brilhante, vermelho_brilhante},
        {off, vermelho_brilhante, vermelho_brilhante, vermelho_brilhante, off},
        {off, off, vermelho_brilhante, off, off}
    };

    memcpy(animacao[0], frame1, sizeof(frame1));
    memcpy(animacao[1], frame2, sizeof(frame2));
    memcpy(animacao[2], frame3, sizeof(frame3));

    return (Animacao) {
        .frames = animacao,
        .tamanho = 3,
        .duracao_frame_ms = 100,
    };
}
