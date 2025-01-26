#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/bootrom.h"  // Biblioteca necessária para reiniciar o sistema

#include "bootsel.h"

void check_reboot(char key) {
    if (key == '*') {  // Se a tecla '*' for pressionada
        printf("Tecla '*' pressionada! Reiniciando...\n");
        sleep_ms(1000);  // Atraso para exibir a mensagem antes de reiniciar
        reset_usb_boot(0,0);  // Reinicia o Raspberry Pi Pico W e entra no modo de gravação
    }
}
