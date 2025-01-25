#include "pico/stdlib.h"
#include "hardware/pio.h"

#include "matriz_leds.h"
#include "animacoes/fogos_artificio/fogos_artificio.h"

int main() {
    stdio_init_all();

    PIO pio = pio0;
    uint sm = configurar_matriz(pio);

    RGB_cod cor0 = cor_24bit_para_3double(0, 0, 0);
    RGB_cod cor1 = cor_24bit_para_3double(0, 0, 255);

    Matriz_leds_config orig = {
        {cor1, cor1, cor1, cor1, cor1},
        {cor1, cor1, cor1, cor1, cor1},
        {cor1, cor1, cor1, cor1, cor1},
        {cor1, cor1, cor1, cor1, cor1},
        {cor1, cor1, cor1, cor1, cor1},
    };

    Matriz_leds_config display;

    double i100 = 1.0;
    double i80 = 0.8;
    double i50 = 0.5;
    double i20 = 0.2;

    iniciar_animacao_fogos_artificio(pio, sm);

    /* while (true) { */
    /*     for (int i = 0; i < 5; i++) { */
    /*         for (int j = 0; j < 5; j++) { */
    /*             RGB_cod c = orig[i][j]; */
    /*             c.red *= brightness; */
    /*             c.green *= brightness; */
    /*             c.blue *= brightness; */
    /*             display[i][j] = c; */
    /*         } */
    /*     } */
    /*     imprimir_desenho(display, pio, sm); */
    /*     brightness += 0.1; */
    /*     sleep_ms(1000); */
    /* } */
}
