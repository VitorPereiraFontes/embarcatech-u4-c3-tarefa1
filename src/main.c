#include "pico/stdlib.h"
#include "hardware/pio.h"

#include <stdio.h>

#include "matriz_leds.h"
#include "animacoes/animacoes.h"
#include "animacao.c"
#include "bootsel.c"

void aplicar_brilho(const Matriz_leds_config *src, double brightness, Matriz_leds_config *dest) {
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

int main() {
    stdio_init_all();
    setup_keypad();    // Configura os pinos do teclado
    setup_leds();      // Configura os LEDs

    Animacao anim_padrao = obter_anim_padrao();

    Animacao animacoes[4];
    animacoes[0] = obter_anim_fogos_artificio();
    animacoes[1] = obter_anim_cobra();
    // TODO: resto das animações

    double brilho = 1.0;
    size_t contador = 0;
    const Animacao *anim_atual = &animacoes[1];

    PIO pio = pio0;
    uint sm = configurar_matriz(pio);

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
                break;

            case '2':
                printf("\nTrocando para a animação da cobra...\n");
                anim_atual = &animacoes[1];
                contador = 0;
            break;

            case '3':
                animacao_leds();
            break;

            default:
                break;
            }
        }

        const Matriz_leds_config *frame_atual = &anim_atual->frames[contador];

        Matriz_leds_config display;
        aplicar_brilho(frame_atual, brilho, &display);

        if (contador < anim_atual->tamanho - 1) {
            contador++;
        }else{
            contador = 0;
        }

        // TODO: processar input do teclado

        imprimir_desenho(display, pio, sm);
        sleep_ms(anim_atual->duracao_frame_ms);
    }
}
