#include "keypad.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"

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

char get_key() {
    for (int row = 0; row < ROW_NUM; row++) {
        // Ativa a linha atual
        gpio_put(rowPins[row], 0);

        // Se for usar a placa tirar o sleep do comentario
        sleep_ms(50);
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
