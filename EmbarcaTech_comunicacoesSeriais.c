#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "pio_matriz.pio.h"
#include "./headers/led_matriz.h"

// Defines
#define blue_pin 12
#define green_pin 13

void inicializar_pinos(){
    gpio_init(blue_pin);
    gpio_set_dir(blue_pin, GPIO_OUT);
    gpio_init(green_pin);
    gpio_set_dir(green_pin, GPIO_OUT);
}

int main(){
    PIO pio = pio0;
    uint sm = 0;
    uint offset = pio_add_program(pio, &pio_matriz_program);
    pio_matriz_program_init(pio, sm, offset, pino_matriz);

    inicializar_pinos();
    stdio_init_all();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
