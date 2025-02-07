#include <stdio.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/i2c.h"
#include "hardware/clocks.h"
#include "pio_matriz.pio.h"
#include "./headers/led_matriz.h"
#include "./headers/numeros.h"
#include "./headers/ssd1306.h"
#include "./headers/font.h"

// Defines
#define blue_pin 12
#define green_pin 11
#define botaoA 5
#define botaoB 6

#define I2C_PORT i2c1
#define ADDR 0x3c
#define I2C_SDA 14
#define I2C_SCL 15
#define debounce_delay 200 // Debounce em ms

// Variáveis globais
volatile bool botaoA_pressionado = false;
volatile bool botaoB_pressionado = false;
ssd1306_t ssd;

// Função da interrupção dos botões
void botao_callback(uint gpio, uint32_t events){
    static absolute_time_t last_press = 0;
    absolute_time_t agora = get_absolute_time();

    if(absolute_time_diff_us(last_press, agora) > debounce_delay * 1e+3){ // Faz o tratamento do bouncing
        if(gpio == botaoA){
            botaoA_pressionado = !botaoA_pressionado;
            gpio_put(green_pin, botaoA_pressionado);
            if(gpio_get(green_pin)){
                printf("LED verde: ligado\n");

                ssd1306_fill(&ssd, false);
                ssd1306_draw_string(&ssd, "LED", 5, 30);
                ssd1306_draw_string(&ssd, "verde:", 35, 30);
                ssd1306_draw_string(&ssd, "ligado", 79, 30);
                ssd1306_send_data(&ssd);
            }
            else{
                printf("LED verde: desligado\n");

                ssd1306_fill(&ssd, false);
                ssd1306_draw_string(&ssd, "LED", 30, 25);
                ssd1306_draw_string(&ssd, "verde:", 60, 25);
                ssd1306_draw_string(&ssd, "desligado", 30, 40);
                ssd1306_send_data(&ssd);
            }
        }
        else{
            if(gpio == botaoB){
                botaoB_pressionado = !botaoB_pressionado;
                gpio_put(blue_pin, botaoB_pressionado);
                if(gpio_get(blue_pin)){
                    printf("LED azul: ligado\n");

                    ssd1306_fill(&ssd, false);
                    ssd1306_draw_string(&ssd, "LED", 8, 30);
                    ssd1306_draw_string(&ssd, "azul:", 37, 30);
                    ssd1306_draw_string(&ssd, "ligado", 73, 30);
                    ssd1306_send_data(&ssd);
                }
                else{
                    printf("LED azul: desligado\n");

                    ssd1306_fill(&ssd, false);
                    ssd1306_draw_string(&ssd, "LED", 35, 25);
                    ssd1306_draw_string(&ssd, "azul:", 65, 25);
                    ssd1306_draw_string(&ssd, "desligado", 30, 40);
                    ssd1306_send_data(&ssd);
                }
            }
        }
        last_press = agora;
    }
}

void inicializar_pinos(){
    // Inicialização do LED azul
    gpio_init(blue_pin);
    gpio_set_dir(blue_pin, GPIO_OUT);

    // Inicialização do LED verde
    gpio_init(green_pin);
    gpio_set_dir(green_pin, GPIO_OUT);

    // Inicialização do botão A
    gpio_init(botaoA);
    gpio_set_dir(botaoA, GPIO_IN);
    gpio_pull_up(botaoA);
    gpio_set_irq_enabled_with_callback(botaoA, GPIO_IRQ_EDGE_FALL, true, &botao_callback);
    
    // Inicialização do botão B
    gpio_init(botaoB);
    gpio_set_dir(botaoB, GPIO_IN);
    gpio_pull_up(botaoB);
    gpio_set_irq_enabled_with_callback(botaoB, GPIO_IRQ_EDGE_FALL, true, &botao_callback);

    // Inicializa o I2C
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SCL);

    // Inicializa o Display
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, ADDR, I2C_PORT);
    ssd1306_config(&ssd);
    ssd1306_send_data(&ssd);
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
}

int main(){
    PIO pio = pio0;
    uint sm = 0;
    uint offset = pio_add_program(pio, &pio_matriz_program);
    pio_matriz_program_init(pio, sm, offset, pino_matriz);

    inicializar_pinos();
    stdio_init_all();

    while (true) {
        if(stdio_usb_connected()){ // Verifica se o USB foi conectado
            char caracter = getchar(); // Lê caracter do monitor serial

            if(isdigit(caracter)){ // Verifica se foi um número ou caracter digitado
                mostrar_num(caracter, pio, sm); // Imprime número na matriz de LED's
                printf("Número: %c\n", caracter);

                ssd1306_fill(&ssd, false); 
                ssd1306_draw_char(&ssd, caracter, 64, 32); // Imprime no display
                ssd1306_send_data(&ssd);
            }
            else{
                printf("Caracter: %c\n", caracter);
                limpar_todos_leds(pio, sm); // Desliga LED's da matriz

                ssd1306_fill(&ssd, false);
                ssd1306_draw_char(&ssd, caracter, 64, 32); // Imprime no display
                ssd1306_send_data(&ssd);
            }
        }

        sleep_ms(10);
    }
}
