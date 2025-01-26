#ifndef _ANIMACOES_H
#define _ANIMACOES_H

#include "../matriz_leds.h"

typedef struct {
    const Matriz_leds_config *frames;
    size_t tamanho;
    uint32_t duracao_frame_ms;
} Animacao;

Animacao obter_anim_padrao();
Animacao obter_anim_fogos_artificio();
Animacao obter_anim_cobra();

#endif
