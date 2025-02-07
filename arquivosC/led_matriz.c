#include "../headers/led_matriz.h"
#include "../headers/numeros.h"

uint32_t matriz_rgb(double r, double g, double b) {
    unsigned char R = r * 255;
    unsigned char G = g * 255;
    unsigned char B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

void limpar_todos_leds(PIO pio, uint sm) {
    for (int i = 0; i < num_pixels; i++) {
        pio_sm_put_blocking(pio, sm, matriz_rgb(0.0, 0.0, 0.0));
    }
}

void acender_leds(PIO pio, uint sm, double r, double g, double b) {
    for (int i = 0; i < num_pixels; i++) {
        pio_sm_put_blocking(pio, sm, matriz_rgb(b, r, g));
    }
}

void mostrar_num(char caracter, PIO pio, uint sm){
    switch (caracter){
    case '0':
        num0(pio, sm);
        break;
    case '1':
        num1(pio, sm);
        break;
    case '2':
        num2(pio, sm);
        break;
    case '3':
        num3(pio, sm);
        break;
    case '4':
        num4(pio, sm);
        break;
    case '5':
        num5(pio, sm);
        break;
    case '6':
        num6(pio, sm);
        break;
    case '7':
        num7(pio, sm);
        break;
    case '8':
        num8(pio, sm);
        break;
    case '9':
        num9(pio, sm);
        break;
    }
}