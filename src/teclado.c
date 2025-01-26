void acionar_tecla(char key) {  // Função que recebe a tecla pressionada e executa a ação correspondente
    switch (key) {  // Estrutura de controle para verificar qual tecla foi pressionada
        case 'A':  // Se a tecla pressionada for 'A'
            // Desliga todos os LEDs, configurando todos os LEDs para a cor preta (apagados)
            for (int i = 0; i < NUM_LEDS; i++) {  // Laço para percorrer todos os LEDs
                leds[i] = CRGB::Black;  // Define a cor preta para cada LED (apagado)
            }
            break;  // Sai do switch case após a execução do comando para a tecla 'A'
        case 'B':  // Se a tecla pressionada for 'B'
            // Liga todos os LEDs em azul
            fill_solid(leds, NUM_LEDS, CRGB::Blue);  // Preenche todos os LEDs com a cor azul
            break;  // Sai do switch case após a execução do comando para a tecla 'B'
        case 'C':  // Se a tecla pressionada for 'C'
            // Liga todos os LEDs em vermelho com 80% de intensidade (cor ajustada)
            fill_solid(leds, NUM_LEDS, CRGB(204, 0, 0));  // Preenche todos os LEDs com vermelho (RGB ajustado para 80% de intensidade)
            break;  // Sai do switch case após a execução do comando para a tecla 'C'
        case 'D':  // Se a tecla pressionada for 'D'
            // Liga todos os LEDs em verde com 50% de intensidade
            fill_solid(leds, NUM_LEDS, CRGB(0, 128, 0));  // Preenche todos os LEDs com verde (RGB ajustado para 50% de intensidade)
            break;  // Sai do switch case após a execução do comando para a tecla 'D'
        case '#':  // Se a tecla pressionada for '#'
            // Liga todos os LEDs em branco com 20% de intensidade
            fill_solid(leds, NUM_LEDS, CRGB(51, 51, 51));  // Preenche todos os LEDs com branco (RGB ajustado para 20% de intensidade)
            break;  // Sai do switch case após a execução do comando para a tecla '#'
        default:  // Se nenhuma tecla conhecida for pressionada (caso default)
            break;  // Não faz nada e sai do switch case
    }
    FastLED.show();  // Atualiza os LEDs para mostrar as mudanças feitas acima
}
