#ifndef LED_MATRIZ_H
#define LEd_MATRIZ_H

#include "hardware/pio.h"

#define pino_matriz 7
#define num_pixels 25

uint32_t matriz_rgb(double b, double r, double g);
void limpar_todos_leds(PIO pio, uint sm);
void acender_leds(PIO pio, uint sm, double r, double g, double b);
void mostrar_num(char caracter, PIO pio, uint sm);

#endif // LED_MATRIZ_H