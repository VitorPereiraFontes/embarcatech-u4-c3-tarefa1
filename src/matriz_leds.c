#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "matriz_leds.h"

// Arquivo .pio para controle da matriz
#include "pio_matrix.pio.h"

uint configurar_matriz(PIO pio) {
    // Define o clock para 128 MHz, facilitando a divisão pelo clock
    bool ok = set_sys_clock_khz(128000, false);

    printf("Clock rodando a %ldHz\n", clock_get_hz(clk_sys));
    printf("Iniciando a transmissão PIO\n");

    // Configurações do PIO
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, LED_STRIP_PIN);

    return sm;
}

void imprimir_desenho(Matriz_leds_config configuracao, PIO pio, uint sm) {
    for (int contadorLinha = 4; contadorLinha >= 0; contadorLinha--) {
        if (contadorLinha % 2) {
            for (int contadorColuna = 0; contadorColuna < 5; contadorColuna++) {
                RGB_cod cor = configuracao[contadorLinha][contadorColuna];
                uint32_t codificado = cor_3double_para_ledstrip(cor.red, cor.green, cor.blue);
                pio_sm_put_blocking(pio, sm, codificado);
            }
        } else {
            for (int contadorColuna = 4; contadorColuna >= 0; contadorColuna--) {
                RGB_cod cor = configuracao[contadorLinha][contadorColuna];
                uint32_t codificado = cor_3double_para_ledstrip(cor.red, cor.green, cor.blue);
                pio_sm_put_blocking(pio, sm, codificado);
            }
        }
    }
}

RGB_cod cor_24bit_para_3double(uint8_t red, uint8_t green, uint8_t blue) {
    return (RGB_cod){ red / 255.0, green / 255.0, blue / 255.0 };
}

uint32_t cor_3double_para_ledstrip(double r, double g, double b) {
    uint8_t red = r * 255.0;
    uint8_t green = g * 255.0;
    uint8_t blue = b * 255.0;
    return (green << 24) | (red << 16) | (blue << 8);
}
