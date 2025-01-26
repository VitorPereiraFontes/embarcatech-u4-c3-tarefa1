#  Matriz de LEDs com Raspberry Pi Pico

Este projeto utiliza o microcontrolador **Raspberry Pi Pico** para controlar uma matriz de LEDs 5x5 (WS2812) e interagir com um teclado matricial 4x4. O sistema permite a execução de animações dinâmicas e ajustes personalizados.

---

##  Recursos

- **Matriz de LEDs (WS2812):**
  - Controle de 25 LEDs RGB em uma matriz 5x5.
  - Suporte para diferentes animações dinâmicas.
  - Controle de brilho ajustável.

- **Teclado Matricial 4x4:**
  - Permite interação em tempo real para seleção de animações e controle do sistema.

- **Fácil Extensibilidade:**
  - Arquitetura modular para adicionar novas animações ou expandir funcionalidades.

---

##  Requisitos do Sistema

### Hardware
- Raspberry Pi Pico.
- Matriz de LEDs WS2812 (5x5 ou similar).
- Teclado matricial 4x4.
- Fios de conexão e resistores (se necessário).

### Software
- **SDK do Raspberry Pi Pico**.
- **Compilador GCC para ARM**.
- **CMake** para gerenciar a build.

---

##  Conexões de Hardware

### Esquema de Conexões

| Componente         | Pino do Pico       |
|---------------------|--------------------|
| Dados LEDs WS2812   | GP7               |
| Linha 1 do teclado  | GP1               |
| Linha 2 do teclado  | GP2               |
| Linha 3 do teclado  | GP3               |
| Linha 4 do teclado  | GP4               |
| Coluna 1 do teclado | GP8               |
| Coluna 2 do teclado | GP9               |
| Coluna 3 do teclado | GP16              |
| Coluna 4 do teclado | GP17              |

---

##  Como Usar

### 1. Preparar o Hardware
- Conecte os LEDs e o teclado conforme o esquema acima.
- Certifique-se de que o Raspberry Pi Pico está corretamente alimentado.

### 2. Configurar o Ambiente de Desenvolvimento
- Clone o repositório:
  ```bash
  git clone <link-repositorio>
  cd <diretorio-repositorio>


## Execução do projeto

Ao iniciar, use o teclado para interagir:
- Tecla 1: Animação de fogos de artifício.
- Tecla 2: Animação "cobra".
- Tecla 3: LEDs em sequência.
- Outras teclas podem ser configuradas.

## Estrutura do projeto

```
.
├── main.c                 // Programa principal
├── bootsel.{c,h}          // Funções de reinicialização
├── keypad.{c,h}           // Definição de tipos e funções do teclado matricial
├── matriz_leds.{c,h}      // Definição de tipos e funções da matriz de LEDs
├── buzzer.{c,h}           // Definição de tipos e funções do buzzer
├── animacoes/             // Diretório para animações adicionais
│   ├── animacoes.h        // Declaração de animações
│   └── ...                // Outras animações
├── CMakeLists.txt         // Configuração para compilação com CMake
└── README.md              // Documentação do projeto
```

## Componentes

- Líder: Vítor
- Interface com matriz de LEDs: Vítor
- Diagrama do Wokwi: Yohanan
- Ajuste de intensidade (brilho) da matriz de LEDs: Yohanan
- Teclado matricial + reset para BOOTSEL: Fernando
- Vídeo: Fernando
- Documentação (README): Caio
- Animações: Todos
