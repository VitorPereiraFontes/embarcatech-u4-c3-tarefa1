#include <string.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"

#include "animacoes.h"

static Matriz_leds_config animacao[5];  // Aumentando para 5 frames

Animacao obter_anim_coracao_pulsante() {
    RGB_cod vermelho_brilhante = cor_24bit_para_3double(255, 0, 0);  // Vermelho vivo
    RGB_cod vermelho_fade = cor_24bit_para_3double(153, 0, 0);       // Vermelho mais escuro
    RGB_cod vermelho_apagado = cor_24bit_para_3double(77, 0, 0);      // Vermelho bem fraco
    RGB_cod off = {0, 0, 0};                                           // LEDs apagados

    // Frame 1: Coração apagado
    Matriz_leds_config frame1 = {
        {off, vermelho_apagado, off, vermelho_apagado, off},
        {vermelho_apagado, off, vermelho_apagado, off, vermelho_apagado},
        {vermelho_apagado, off, off, off, vermelho_apagado},
        {off, vermelho_apagado, off, vermelho_apagado, off},
        {off, off, vermelho_apagado, off, off}
    };

    // Frame 2: Coração intermediário
    Matriz_leds_config frame2 = {
        {off, vermelho_apagado, off, vermelho_apagado, off},
        {vermelho_apagado, off, vermelho_apagado, off, vermelho_apagado},
        {vermelho_apagado, off, off, off, vermelho_apagado},
        {off, vermelho_apagado, off, vermelho_apagado, off},
        {off, off, vermelho_apagado, off, off}
    };

    // Frame 3: Coração brilhante
    Matriz_leds_config frame3 = {
        {off, vermelho_apagado, off, vermelho_apagado, off},
        {vermelho_apagado, off, vermelho_apagado, off, vermelho_apagado},
        {vermelho_apagado, off, off, off, vermelho_apagado},
        {off, vermelho_apagado, off, vermelho_apagado, off},
        {off, off, vermelho_apagado, off, off}
    };

    // Frame 4: Coração ainda mais brilhante
    Matriz_leds_config frame4 = {
        {off, vermelho_apagado, off, vermelho_apagado, off},
        {vermelho_apagado, off, vermelho_apagado, off, vermelho_apagado},
        {vermelho_apagado, off, off, off, vermelho_apagado},
        {off, vermelho_apagado, off, vermelho_apagado, off},
        {off, off, vermelho_apagado, off, off}
    };

    // Frame 5: Coração apagando
    Matriz_leds_config frame5 = {
        {off, vermelho_apagado, off, vermelho_apagado, off},
        {vermelho_apagado, off, vermelho_apagado, off, vermelho_apagado},
        {vermelho_apagado, off, off, off, vermelho_apagado},
        {off, vermelho_apagado, off, vermelho_apagado, off},
        {off, off, vermelho_apagado, off, off}
    };

    // Copiando os frames para a animação
    memcpy(animacao[0], frame1, sizeof(frame1));
    memcpy(animacao[1], frame2, sizeof(frame2));
    memcpy(animacao[2], frame3, sizeof(frame3));
    memcpy(animacao[3], frame4, sizeof(frame4));
    memcpy(animacao[4], frame5, sizeof(frame5));

    // Retornando a animação com 5 frames
    return (Animacao) {
        .frames = animacao,
        .tamanho = 5,  // Agora com 5 frames
        .duracao_frame_ms = 100,  // Duração de cada frame
        .frame_buzzer = -1,
        .freq_buzzer = 0,
    };
}
