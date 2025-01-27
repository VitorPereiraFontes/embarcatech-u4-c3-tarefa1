#include <string.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"

#include "animacoes.h"

static Matriz_leds_config animacao[5];  // Array para armazenar os frames

Animacao obter_anim_onda_luz() {
    RGB_cod azul_brilhante = cor_24bit_para_3double(0, 0, 255);  // Azul vivo
    RGB_cod azul_fade = cor_24bit_para_3double(0, 0, 153);       // Azul mais escuro
    RGB_cod azul_apagado = cor_24bit_para_3double(0, 0, 77);      // Azul bem fraco
    RGB_cod off = {0, 0, 0};                                     // LEDs apagados

    // Frame 1: Luz no topo
    Matriz_leds_config frame1 = {
        {azul_brilhante, azul_fade, azul_apagado, off, off},
        {off, off, off, off, off},
        {off, off, off, off, off},
        {off, off, off, off, off},
        {off, off, off, off, off}
    };

    // Frame 2: Luz descendo
    Matriz_leds_config frame2 = {
        {off, off, off, off, off},
        {azul_brilhante, azul_fade, azul_apagado, off, off},
        {off, off, off, off, off},
        {off, off, off, off, off},
        {off, off, off, off, off}
    };

    // Frame 3: Luz no meio
    Matriz_leds_config frame3 = {
        {off, off, off, off, off},
        {off, off, off, off, off},
        {azul_brilhante, azul_fade, azul_apagado, off, off},
        {off, off, off, off, off},
        {off, off, off, off, off}
    };

    // Frame 4: Luz quase no final
    Matriz_leds_config frame4 = {
        {off, off, off, off, off},
        {off, off, off, off, off},
        {off, off, off, off, off},
        {azul_brilhante, azul_fade, azul_apagado, off, off},
        {off, off, off, off, off}
    };

    // Frame 5: Luz no final
    Matriz_leds_config frame5 = {
        {off, off, off, off, off},
        {off, off, off, off, off},
        {off, off, off, off, off},
        {off, off, off, off, off},
        {azul_brilhante, azul_fade, azul_apagado, off, off}
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
        .tamanho = 5,  // 5 frames no total
        .duracao_frame_ms = 150,  // Duração de cada frame
        .frame_buzzer = -1,
        .freq_buzzer = 0,
    };
}
