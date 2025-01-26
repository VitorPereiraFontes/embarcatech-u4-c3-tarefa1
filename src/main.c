#include "pico/stdlib.h"
#include "hardware/pio.h"

#include <stdio.h>

#include "matriz_leds.h"
#include "buzzer.h"

#include "animacoes/animacoes.h"
#include "animacao.c"
#include "bootsel.c"

#define BUZZER_PIN 10

static void aplicar_brilho(const Matriz_leds_config *src, double brightness, Matriz_leds_config *dest);

int main() {
    stdio_init_all();
    setup_keypad();    // Configura os pinos do teclado
    setup_leds();      // Configura os LEDs

    Animacao anim_padrao = obter_anim_padrao();

    Animacao animacoes[8];
    animacoes[0] = obter_anim_fogos_artificio();
    animacoes[1] = obter_anim_cobra();
    animacoes[2] = obter_anim_coracao_pulsante();
    animacoes[3] = obter_anim_off();
    animacoes[4] = obter_anim_blue();
    animacoes[5] = obter_anim_red();
    animacoes[6] = obter_anim_green();
    animacoes[7] = obter_anim_white();

    // TODO: resto das animações

    double brilho = 1.0;
    size_t contador = 0;
    const Animacao *anim_atual = &animacoes[1];

    PIO pio = pio0;
    uint sm = configurar_matriz(pio);

    Buzzer bz;
    Buzzer_init(&bz, BUZZER_PIN);

    sleep_ms(1000);

    while (true) {
        char key = get_key();  // Lê a tecla pressionada

        if (key) {  // Se uma tecla foi pressionada
            printf("Tecla pressionada: %c\n", key);

            check_reboot(key);

            switch (key){
            case '1':
                printf("\nTrocando para a animação de fogos de artifício...\n");
                anim_atual = &animacoes[0];
                contador = 0;
                brilho = 1.0;
            break;

            case '2':
                printf("\nTrocando para a animação da cobra...\n");
                anim_atual = &animacoes[1];
                contador = 0;
                brilho = 1.0;
            break;

            case '3':
                printf("\nTrocando para a animação do coração pulsante...\n");
                anim_atual = &animacoes[2];
                contador = 0;
                brilho = 1.0;
            break;

            case 'A':
                anim_atual = &animacoes[3];
                contador = 0;
            break;

            case 'B':
                anim_atual = &animacoes[4];
                contador = 0;
                brilho = 1.0;
            break;

            case 'C':
                anim_atual = &animacoes[5];
                contador = 0;
                brilho = 0.8;
            break;

            case 'D':
                anim_atual = &animacoes[6];
                contador = 0;
                brilho = 0.5;
            break;

            case '#':
                anim_atual = &animacoes[7];
                contador = 0;
                brilho = 0.2;
            break;

            default:
                break;
            }
        }

        const Matriz_leds_config *frame_atual = &anim_atual->frames[contador];

        Buzzer_play_stop(&bz);

        if (anim_atual->frame_buzzer == contador)
            Buzzer_play_start(&bz, anim_atual->freq_buzzer);

        Matriz_leds_config display;
        aplicar_brilho(frame_atual, brilho, &display);

        if (contador < anim_atual->tamanho - 1) {
            contador++;
        } else {
            contador = 0;
        }

        // TODO: processar input do teclado

        imprimir_desenho(display, pio, sm);
        sleep_ms(anim_atual->duracao_frame_ms);
    }
}

static void aplicar_brilho(const Matriz_leds_config *src, double brightness, Matriz_leds_config *dest) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            RGB_cod cor_src = (*src)[i][j];
            RGB_cod cor = {
                .red = MIN(1.0, cor_src.red * brightness),
                .green = MIN(1.0, cor_src.green * brightness),
                .blue = MIN(1.0, cor_src.blue * brightness),
            };
            (*dest)[i][j] = cor;
        }
    }
}
