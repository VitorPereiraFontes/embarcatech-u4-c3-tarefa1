#include <string.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"

#include "animacoes.h"

static Matriz_leds_config animacao[11];

Animacao obter_anim_fogos_artificio() {
    RGB_cod off = {0,0,0};
    RGB_cod cor_bomba = cor_24bit_para_3double(100,102,105);
    RGB_cod cor_explosao = cor_24bit_para_3double(233,89,18);
    RGB_cod cor_explosao_fade_1 = cor_24bit_para_3double(233 * 0.6,89 * 0.6,18 * 0.6);
    RGB_cod cor_explosao_fade_2 = cor_24bit_para_3double(233 * 0.3,89 * 0.6,18 * 0.3);
    RGB_cod cor_estrela_estagio_1 = cor_24bit_para_3double(181,45,201);
    RGB_cod cor_estrela_estagio_1_fade_1 = cor_24bit_para_3double(181 * 0.6,45 * 0.6,201 * 0.6);
    RGB_cod cor_estrela_estagio_1_fade_2 = cor_24bit_para_3double(181 * 0.3,45 * 0.3,201 * 0.3);
    RGB_cod cor_estrela_estagio_2 = cor_24bit_para_3double(221,3,255);
    RGB_cod cor_estrela_estagio_2_fade_1 = cor_24bit_para_3double(221 * 0.6,3 * 0.6,255 * 0.6);
    RGB_cod cor_estrela_estagio_2_fade_2 = cor_24bit_para_3double(221 * 0.3,3 * 0.3,255 * 0.3);

    Matriz_leds_config frame1 = {
        {off,off,off,off,off},
        {off,off,off,off,off},
        {off,off,off,off,off},
        {off,off,off,off,off},
        {off,off,cor_bomba,off,off},
    };

    Matriz_leds_config frame2 = {
        {off,off,off,off,off},
        {off,off,off,off,off},
        {off,off,off,off,off},
        {off,off,cor_bomba,off,off},
        {off,off,off,off,off},
    };

    Matriz_leds_config frame3 = {
        {off,off,off,off,off},
        {off,off,off,off,off},
        {off,off,cor_bomba,off,off},
        {off,off,off,off,off},
        {off,off,off,off,off},
    };

    Matriz_leds_config frame4 = {
        {off,off,off,off,off},
        {off,off,off,off,off},
        {off,off,cor_explosao,off,off},
        {off,off,off,off,off},
        {off,off,off,off,off},
    };

    Matriz_leds_config frame5 = {
        {off,        off          ,        off          ,        off          ,off},
        {off,cor_estrela_estagio_1,cor_estrela_estagio_1,cor_estrela_estagio_1,off},
        {off,cor_estrela_estagio_1, cor_explosao_fade_1 ,cor_estrela_estagio_1,off},
        {off,cor_estrela_estagio_1,cor_estrela_estagio_1,cor_estrela_estagio_1,off},
        {off,        off          ,        off          ,        off          ,off},
    };

    Matriz_leds_config frame6 = {
        {cor_estrela_estagio_2,             off            ,    cor_estrela_estagio_2   ,           off              ,cor_estrela_estagio_2},
        {       off           ,cor_estrela_estagio_1_fade_1,cor_estrela_estagio_1_fade_1,cor_estrela_estagio_1_fade_1,          off        },
        {cor_estrela_estagio_2,cor_estrela_estagio_1_fade_1,    cor_explosao_fade_2     ,cor_estrela_estagio_1_fade_1,cor_estrela_estagio_2},
        {       off           ,cor_estrela_estagio_1_fade_1,cor_estrela_estagio_1_fade_1,cor_estrela_estagio_1_fade_1,          off        },
        {cor_estrela_estagio_2,             off            ,    cor_estrela_estagio_2   ,           off              ,cor_estrela_estagio_2},
    };

    Matriz_leds_config frame7 = {
        {cor_estrela_estagio_2,             off            ,    cor_estrela_estagio_2   ,           off              ,cor_estrela_estagio_2},
        {       off           ,cor_estrela_estagio_1_fade_2,cor_estrela_estagio_1_fade_2,cor_estrela_estagio_1_fade_2,          off        },
        {cor_estrela_estagio_2,cor_estrela_estagio_1_fade_2,    cor_explosao_fade_2     ,cor_estrela_estagio_1_fade_2,cor_estrela_estagio_2},
        {       off           ,cor_estrela_estagio_1_fade_2,cor_estrela_estagio_1_fade_2,cor_estrela_estagio_1_fade_2,          off        },
        {cor_estrela_estagio_2,             off            ,    cor_estrela_estagio_2   ,           off              ,cor_estrela_estagio_2},
    };

    Matriz_leds_config frame8 = {
        {cor_estrela_estagio_2_fade_1,             off            ,cor_estrela_estagio_2_fade_1,           off              ,cor_estrela_estagio_2_fade_1},
        {           off              ,cor_estrela_estagio_1_fade_2,cor_estrela_estagio_1_fade_2,cor_estrela_estagio_1_fade_2,               off          },
        {cor_estrela_estagio_2_fade_1,cor_estrela_estagio_1_fade_2,            off             ,cor_estrela_estagio_1_fade_2,cor_estrela_estagio_2_fade_1},
        {           off              ,cor_estrela_estagio_1_fade_2,cor_estrela_estagio_1_fade_2,cor_estrela_estagio_1_fade_2,               off          },
        {cor_estrela_estagio_2_fade_1,             off            ,cor_estrela_estagio_2_fade_1,           off              ,cor_estrela_estagio_2_fade_1},
    };

    Matriz_leds_config frame9 = {
        {cor_estrela_estagio_2_fade_1,off,cor_estrela_estagio_2_fade_1,off,cor_estrela_estagio_2_fade_1},
        {           off              ,off,          off               ,off,             off            },
        {cor_estrela_estagio_2_fade_1,off,          off               ,off,cor_estrela_estagio_2_fade_1},
        {           off              ,off,          off               ,off,             off            },
        {cor_estrela_estagio_2_fade_1,off,cor_estrela_estagio_2_fade_1,off,cor_estrela_estagio_2_fade_1},
    };

    Matriz_leds_config frame10 = {
        {cor_estrela_estagio_2_fade_2,off,cor_estrela_estagio_2_fade_2,off,cor_estrela_estagio_2_fade_2},
        {           off              ,off,          off               ,off,             off            },
        {cor_estrela_estagio_2_fade_2,off,          off               ,off,cor_estrela_estagio_2_fade_2},
        {           off              ,off,          off               ,off,             off            },
        {cor_estrela_estagio_2_fade_2,off,cor_estrela_estagio_2_fade_2,off,cor_estrela_estagio_2_fade_2},
    };

    Matriz_leds_config frame11 = {
        {off,off,off,off,off},
        {off,off,off,off,off},
        {off,off,off,off,off},
        {off,off,off,off,off},
        {off,off,off,off,off},
    };

    memcpy(animacao[0], frame1, sizeof(frame1));
    memcpy(animacao[1], frame2, sizeof(frame2));
    memcpy(animacao[2], frame3, sizeof(frame3));
    memcpy(animacao[3], frame4, sizeof(frame4));
    memcpy(animacao[4], frame5, sizeof(frame5));
    memcpy(animacao[5], frame6, sizeof(frame6));
    memcpy(animacao[6], frame7, sizeof(frame7));
    memcpy(animacao[7], frame8, sizeof(frame8));
    memcpy(animacao[8], frame9, sizeof(frame9));
    memcpy(animacao[9], frame10, sizeof(frame10));
    memcpy(animacao[10], frame11, sizeof(frame11));

    return (Animacao) {
        .frames = animacao,
        .tamanho = 11,
        .duracao_frame_ms = 100,
        .frame_buzzer = 3,
        .freq_buzzer = 2090,
    };
}
