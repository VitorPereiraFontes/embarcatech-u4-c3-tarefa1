/**
 * Pino que realizará a comunicação do microcontrolador com a matriz
 */
#define LED_STRIP_PIN 7

/**
 * Definição de tipo da estrutura que irá controlar a cor dos LEDs
 */
typedef struct {
    double red;
    double green;
    double blue;
} Led_config;

typedef Led_config RGB_cod;

/**
 * Definição de tipo da matriz de leds
 */
typedef Led_config Matriz_leds_config[5][5];

uint configurar_matriz(PIO pio);

void imprimir_desenho(Matriz_leds_config configuracao, PIO pio, uint sm);

/**
 * Converte cor 24-bit (0-255 em cada banda) para RGB em double.
 */
RGB_cod cor_24bit_para_3double(uint8_t red, uint8_t green, uint8_t blue);

/**
 * Converte RGB em double para o formato e ordem utilizado pelo LED strip.
 */
uint32_t cor_3double_para_ledstrip(double red, double green, double blue);
