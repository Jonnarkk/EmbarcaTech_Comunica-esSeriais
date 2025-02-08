# EmbarcaTech_ComunicaçõesSeriais

## Descrição
Este projeto manipula vários vértices da placa BitDogLab: LED's RGB, matriz de LED's 5x5, botões e display.

## Funcionalidades
- **Botão A**: Liga/desliga LED verde.
- **Botão B**: Liga/desliga LED azul.
- **Matriz de LED's 5x5**: Mostra números digitados no monitor serial. (0-9)
- **Display**: Mostra se os LED's foram ligados/desligados e imprime os caracteres, maiúsculos e minúsculos, digitados no monitor serial.

## Estrutura do Código
O código está organizado em diversas funções, dentre as quais vale a pena mencionar:

- `void botao_callback(uint gpio, uint32_t events)`: Realiza lógica da interrupção quando o botão A ou B for pressionado.
- `inicializar_pinos()`: Inicializa os pinos e configura todos os itens utilizados.
- `gpio_set_irq_enabled_with_callback(botaoA, GPIO_IRQ_EDGE_FALL, true, &botao_callback)`: Configura interrupção para o botão A.
- `gpio_set_irq_enabled_with_callback(botaoB, GPIO_IRQ_EDGE_FALL, true, &botao_callback)`: Configura interrupção para o botão B.
- `uint32_t matriz_rgb(double r, double g, double b)`: Inicializa matriz de LED's.
- `void limpar_todos_leds(PIO pio, uint sm)`: Desliga os LED's da matriz de LED's.
- `void mostrar_num(char caracter, PIO pio, uint sm)`: Apresenta o número digitado no monitor serial na matriz 5x5 de LED's.

## Estrutura dos arquivos
```
project/
│
├── arquivosC/
│   ├── led_matriz.c
│   ├── numeros.c
│   ├── ssd1306.c
│
├── headers/
│   ├── font.h
│   ├── led_matriz.h
│   ├── numeros.h
│   └── led_matriz.h
├── EmbarcaTech_comunicacoesSeriais.c
├── CMakeLists.txt
└── README.md
```

## Link com o vídeo explicativo
**https://drive.google.com/file/d/1MBkTqxq6mW5NhwG6e0net4AWur8FbwiG/view?usp=sharing**

## Desenvolvedor
Guilherme Miller Gama Cardoso