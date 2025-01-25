#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "../../matriz_leds.h"
#include "fogos_artificio.h"

void iniciar_animacao_fogos_artificio(PIO pio, uint sm){
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
}
