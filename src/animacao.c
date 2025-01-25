#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "keypad.h"
#include <FastLED.h>

#define ROW_NUM    4
#define COL_NUM    4

#define NUM_LEDS 25  // Número total de LEDs na matriz 5x5

// Definindo os pinos para os LEDs WS2812 (mapeie com seu hardware)
#define DATA_PIN 16  // Pino de dados do WS2812

CRGB leds[NUM_LEDS];  // Definindo a matriz de LEDs

// Mapeamento do teclado
char keys[ROW_NUM][COL_NUM] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Definindo os pinos do teclado (ajuste conforme necessário)
int rowPins[ROW_NUM] = {2, 3, 4, 5};
int colPins[COL_NUM] = {6, 7, 8, 9};

// Inicializando o teclado matricial
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROW_NUM, COL_NUM);

// Função para iniciar uma animação na matriz de LEDs
void animacao_leds() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;  // Apaga todos os LEDs
    }
    FastLED.show();  // Atualiza os LEDs para apagar a matriz

    // Animação: Acende os LEDs em uma sequência
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Red;  // Acende o LED na cor vermelha
        FastLED.show();
        sleep_ms(100);  // Espera 100ms entre os LEDs
        leds[i] = CRGB::Black;  // Apaga o LED após a espera
    }

    FastLED.show();  // Atualiza os LEDs para mostrar a sequência
}

int main() {
    stdio_init_all();  // Inicializa a comunicação serial
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);  // Define os LEDs

    while (true) {
        char key = keypad.getKey();  // Lê a tecla pressionada

        if (key) {  // Se uma tecla foi pressionada
            printf("Tecla pressionada: %c\n", key);

            // Se a tecla '1' for pressionada, executa a animação
            if (key == '1') {
                animacao_leds();  // Chama a função que executa a animação
            }
        }

        sleep_ms(100);  // Atraso para evitar leituras excessivas
    }

    return 0;
}
