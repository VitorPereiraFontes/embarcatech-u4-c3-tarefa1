#ifndef _KEYPAD_H
#define _KEYPAD_H

// Definições para o teclado matricial
#define ROW_NUM 4
#define COL_NUM 4

// Mapeamento do teclado
static const char keys[ROW_NUM][COL_NUM] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Pinos de linhas e colunas do teclado
static const int rowPins[ROW_NUM] = {16, 17, 18, 19};
static const int colPins[COL_NUM] = {20, 4, 9, 8};

// Função para configurar os pinos do teclado
void setup_keypad();

// Função para ler uma tecla pressionada
char get_key();

#endif
