#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

// Definição da matriz de LEDs (tamanho 5x5)
#define LED_ROWS 5
#define LED_COLS 5

// Estrutura para representar uma cor em RGB
typedef struct {
    double r;
    double g;
    double b;
} RGB_cod;

// Estrutura para a configuração de uma animação
typedef struct {
    RGB_cod frames[5][5];
    int duracao_frame_ms;
} Frame;

// Função para criar uma cor RGB
RGB_cod criar_cor(double r, double g, double b) {
    RGB_cod cor = {r, g, b};
    return cor;
}

// Função para apagar todos os LEDs (cor preta)
RGB_cod cor_preta() {
    return criar_cor(0.0, 0.0, 0.0);
}

// Função para inicializar a comunicação SPI com a matriz BitDogLab
void inicializar_spi() {
    spi_init(spi0, 500 * 1000); // Inicializa o SPI com 500kHz
    gpio_set_function(2, GPIO_FUNC_SPI); // Pino SPI SCK
    gpio_set_function(3, GPIO_FUNC_SPI); // Pino SPI MOSI
    gpio_set_function(4, GPIO_FUNC_SPI); // Pino SPI CS
}

// Função para enviar os dados da matriz de LEDs
void enviar_frame(RGB_cod matriz[LED_ROWS][LED_COLS]) {
    uint8_t dados[LED_ROWS * LED_COLS * 3]; // Cada LED tem 3 valores (RGB)
    int index = 0;

    // Converte os valores RGB em dados para enviar via SPI
    for (int i = 0; i < LED_ROWS; i++) {
        for (int j = 0; j < LED_COLS; j++) {
            dados[index++] = (uint8_t)(matriz[i][j].r * 255);
            dados[index++] = (uint8_t)(matriz[i][j].g * 255);
            dados[index++] = (uint8_t)(matriz[i][j].b * 255);
        }
    }

    // Envia os dados pelo SPI
    spi_write_blocking(spi0, dados, sizeof(dados));
}

// Frames da animação do coração pulsante
Frame criar_animacao_coracao_pulsante() {
    // Define cores para o coração pulsante
    RGB_cod vermelho_brilhante = criar_cor(1.0, 0.0, 0.0); // Vermelho vivo
    RGB_cod vermelho_fade = criar_cor(0.6, 0.0, 0.0);      // Vermelho mais escuro
    RGB_cod vermelho_apagado = criar_cor(0.3, 0.0, 0.0);   // Vermelho bem fraco
    RGB_cod off = cor_preta();                             // LEDs apagados

    // Frames representando o coração em diferentes intensidades
    static Frame frames[] = {
        // Frame 1: Coração apagado
        {
            .frames = {
                {off, off, vermelho_apagado, off, off},
                {off, vermelho_apagado, vermelho_apagado, vermelho_apagado, off},
                {vermelho_apagado, vermelho_apagado, vermelho_apagado, vermelho_apagado, vermelho_apagado},
                {off, vermelho_apagado, vermelho_apagado, vermelho_apagado, off},
                {off, off, vermelho_apagado, off, off}
            },
            .duracao_frame_ms = 100
        },
        // Frame 2: Coração intermediário
        {
            .frames = {
                {off, off, vermelho_fade, off, off},
                {off, vermelho_fade, vermelho_fade, vermelho_fade, off},
                {vermelho_fade, vermelho_fade, vermelho_fade, vermelho_fade, vermelho_fade},
                {off, vermelho_fade, vermelho_fade, vermelho_fade, off},
                {off, off, vermelho_fade, off, off}
            },
            .duracao_frame_ms = 100
        },
        // Frame 3: Coração brilhante
        {
            .frames = {
                {off, off, vermelho_brilhante, off, off},
                {off, vermelho_brilhante, vermelho_brilhante, vermelho_brilhante, off},
                {vermelho_brilhante, vermelho_brilhante, vermelho_brilhante, vermelho_brilhante, vermelho_brilhante},
                {off, vermelho_brilhante, vermelho_brilhante, vermelho_brilhante, off},
                {off, off, vermelho_brilhante, off, off}
            },
            .duracao_frame_ms = 100
        }
    };

    return frames;
}

// Função principal
int main() {
    // Inicializa o Raspberry Pi Pico
    stdio_init_all();
    inicializar_spi();

    // Cria a animação do coração pulsante
    Frame *animacao = criar_animacao_coracao_pulsante();

    // Loop principal para exibir a animação
    while (1) {
        // Percorre os frames da animação
        for (int i = 0; i < 3; i++) {
            enviar_frame(animacao[i].frames);                // Envia o frame atual
            sleep_ms(animacao[i].duracao_frame_ms);          // Espera pela duração do frame
        }
    }

    return 0;
}
