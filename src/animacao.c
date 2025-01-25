#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Definições para a matriz de LEDs
#define NUM_LEDS 25   // Número total de LEDs na matriz 5x5
#define DATA_PIN 16   // Pino de dados do WS2812

// Definições para o teclado matricial
#define ROW_NUM 4
#define COL_NUM 4

// Mapeamento do teclado
char keys[ROW_NUM][COL_NUM] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Pinos de linhas e colunas do teclado
int rowPins[ROW_NUM] = {2, 3, 4, 5};
int colPins[COL_NUM] = {6, 7, 8, 9};

// Função para configurar os pinos do teclado
void setup_keypad() {
    for (int i = 0; i < ROW_NUM; i++) {
        gpio_init(rowPins[i]);
        gpio_set_dir(rowPins[i], GPIO_OUT);
        gpio_put(rowPins[i], 1);  // Mantém a linha desativada inicialmente
    }

    for (int i = 0; i < COL_NUM; i++) {
        gpio_init(colPins[i]);
        gpio_set_dir(colPins[i], GPIO_IN);
        gpio_pull_up(colPins[i]);  // Habilita pull-up para as colunas
    }
}

// Função para ler uma tecla pressionada
char get_key() {
    for (int row = 0; row < ROW_NUM; row++) {
        // Ativa a linha atual
        gpio_put(rowPins[row], 0);

        for (int col = 0; col < COL_NUM; col++) {
            // Verifica se a coluna está em nível baixo (tecla pressionada)
            if (gpio_get(colPins[col]) == 0) {
                // Aguarda enquanto a tecla está pressionada
                while (gpio_get(colPins[col]) == 0);
                gpio_put(rowPins[row], 1);  // Desativa a linha
                return keys[row][col];
            }
        }

        // Desativa a linha atual
        gpio_put(rowPins[row], 1);
    }

    return 0;  // Nenhuma tecla pressionada
}

// Função para inicializar os LEDs WS2812 (em C puro)
void setup_leds() {
    gpio_init(DATA_PIN);
    gpio_set_dir(DATA_PIN, GPIO_OUT);
}

// Função para enviar dados para os LEDs WS2812
void send_led_data(uint32_t *leds, int num_leds) {
    for (int i = 0; i < num_leds; i++) {
        uint32_t color = leds[i];
        for (int j = 23; j >= 0; j--) {
            if (color & (1 << j)) {
                // Envia "1" (código de tempo para WS2812)
                gpio_put(DATA_PIN, 1);
                sleep_us(0.8);
                gpio_put(DATA_PIN, 0);
                sleep_us(0.45);
            } else {
                // Envia "0"
                gpio_put(DATA_PIN, 1);
                sleep_us(0.4);
                gpio_put(DATA_PIN, 0);
                sleep_us(0.85);
            }
        }
    }
}

// Função para executar uma animação nos LEDs
void animacao_leds() {
    uint32_t leds[NUM_LEDS] = {0};  // Matriz de LEDs, todos desligados

    // Apaga todos os LEDs
    send_led_data(leds, NUM_LEDS);

    // Animação: Acende os LEDs em sequência
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = 0xFF0000;  // Vermelho
        send_led_data(leds, NUM_LEDS);
        sleep_ms(100);  // Espera 100ms entre os LEDs
        leds[i] = 0x000000;  // Apaga o LED
    }

    send_led_data(leds, NUM_LEDS);  // Apaga todos os LEDs ao final
}

int main() {
    stdio_init_all();  // Inicializa a comunicação serial
    setup_keypad();    // Configura os pinos do teclado
    setup_leds();      // Configura os LEDs

    while (1) {
        char key = get_key();  // Lê a tecla pressionada

        if (key) {  // Se uma tecla foi pressionada
            printf("Tecla pressionada: %c\n", key);

            if (key == '1') {
                animacao_leds();  // Executa a animação se a tecla '1' for pressionada
            }
        }

        sleep_ms(100);  // Delay para evitar leituras excessivas
    }

    return 0;
}
