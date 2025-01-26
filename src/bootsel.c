#include "pico/bootrom.h"  // Biblioteca necessária para reiniciar o sistema

// Função para reiniciar o Raspberry Pi Pico W e entrar no modo de gravação (bootloader)
void check_reboot(char key) {
    if (key == '*') {  // Se a tecla '*' for pressionada
        printf("Tecla '*' pressionada! Reiniciando...\n");
        sleep_ms(1000);  // Atraso para exibir a mensagem antes de reiniciar
        reset_usb_boot(0,0);  // Reinicia o Raspberry Pi Pico W e entra no modo de gravação
    }
}
