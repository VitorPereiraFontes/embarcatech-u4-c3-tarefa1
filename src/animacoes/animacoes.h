#ifndef _ANIMACOES_H
#define _ANIMACOES_H

#include "../matriz_leds.h"

typedef struct {
    const Matriz_leds_config *frames;
    size_t tamanho;
    uint32_t duracao_frame_ms;
    int frame_buzzer;
    uint32_t freq_buzzer;
} Animacao;

Animacao obter_anim_padrao();
Animacao obter_anim_fogos_artificio();
Animacao obter_anim_cobra();
Animacao obter_anim_coracao_pulsante();
Animacao obter_anim_off();
Animacao obter_anim_blue();
Animacao obter_anim_red();
Animacao obter_anim_green();
Animacao obter_anim_white();

#endif
