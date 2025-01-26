#include <string.h>
#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"

#include "animacoes.h"

#define FRAME_COUNT 16
#define MAX_COBRA_SIZE 10

#define CLAMP(_x, _min, _max) \
    if (_x < _min) _x = _min; \
    else if (_x > _max) _x = _max;

enum Direction {
    DIR_UP,
    DIR_RIGHT,
    DIR_DOWN,
    DIR_LEFT,
};

static Matriz_leds_config animacao[32];

Animacao obter_anim_cobra() {
    // Not to be confused with snake. I am specifically talking about a cobra.

    RGB_cod cor_vazio = {0.0, 0.0, 0.0};
    RGB_cod cor_cobra = {0.0, 0.0, 1.0};
    RGB_cod cor_maca = {1.0, 0.0, 0.0};

    size_t tam_cobra = 5;
    uint8_t direction = DIR_RIGHT;

    size_t pos_buffer[MAX_COBRA_SIZE][2];
    for (int i = 0; i < MAX_COBRA_SIZE; i++) {
        pos_buffer[i][0] = 0;
        pos_buffer[i][1] = 0;
    }

#define PASS_BUFFER() \
    for (int i = MAX_COBRA_SIZE - 1; i > 0; i--) { \
        pos_buffer[i][0] = pos_buffer[i-1][0]; \
        pos_buffer[i][1] = pos_buffer[i-1][1]; \
    }

    for (int f = 0; f < FRAME_COUNT; f++) {
        Matriz_leds_config *frame = &animacao[f];

        // fundo vazio
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                (*frame)[i][j] = cor_vazio;
            }
        }

        // renderizar a cobra
        for (int i = 0; i < tam_cobra; i++) {
            size_t x = pos_buffer[i][0];
            size_t y = pos_buffer[i][1];

            CLAMP(x, 0, 4);
            CLAMP(y, 0, 4);

            printf("a %d, (%d, %d)\n", i, x, y);

            (*frame)[y][x] = cor_cobra;
        }

        // mudar de direção em momentos específicos
        if (f == 3) direction = DIR_DOWN;
        if (f == 7) direction = DIR_LEFT;
        if (f == 9) direction = DIR_UP;
        if (f == 11) direction = DIR_RIGHT;
        if (f == 14) direction = DIR_DOWN;

        // seguir a direção desejada
        switch (direction) {
        case DIR_RIGHT:
            PASS_BUFFER();
            pos_buffer[0][0]++;
            break;
        case DIR_LEFT:
            PASS_BUFFER();
            pos_buffer[0][0]--;
            break;
        case DIR_UP:
            PASS_BUFFER();
            pos_buffer[0][1]--;
            break;
        case DIR_DOWN:
            PASS_BUFFER();
            pos_buffer[0][1]++;
            break;
        }
    }

    return (Animacao) {
        .frames = animacao,
        .tamanho = FRAME_COUNT,
        .duracao_frame_ms = 200, // 1s/(200ms/f) = 5fps
        .frame_buzzer = -1,
        .freq_buzzer = 0,
    };
}
