#  Genius para Raspberry Pi Pico W 
Este projeto é uma implementação do clássico jogo Genius (também conhecido como Simon) para o Raspberry Pi Pico W. O jogo desafia a
memória do jogador, que deve repetir uma sequência de cores e sons gerada aleatoriamente. A cada nível, a sequência aumenta, tornando o jogo mais difícil.
Contudo, neste projeto, o jagador deve se atentar aos sons e conseguir reproduzir a sequência aleatória de cada uma das rodadas! 

## Componentes Utilizados 🛠️

- Raspberry Pi Pico W: Microcontrolador principal.
- Matriz de LEDs 5x5: Para exibir os resultados (errado ou correto)
- Buzzers: Para gerar os tons à cada botão correspondente.
- Botões: Para a interação do jogador.
- Display OLED SSD1306 (opcional): Para exibir informações como o level atual.

## Funcionalidades do Jogo 🎮

#### 1. Geração de Sequência:
  - O jogo gera uma sequência aleatória de sons.
  - A cada nível, a sequência aumenta em tamanho.

#### 2. Reprodução da Sequência:
- A sequência é reproduzida nos buzzers.
- O jogador deve repetir a sequência corretamente.

#### 3. Feedback Visual e Sonoro:
- Os buzzers emitem tons correspondentes às cores.

#### 4. Game Over:
- Se o jogador errar a sequência, o jogo exibe uma animação de "Game Over" e reinicia.

#### 5. Vitória:
- A cada nível concluído com sucesso, o jogo exibe uma animação de vitória e avança para o próximo nível.

## Como Compilar e Executar 🚀

### Pré-requisitos
- Ferramentas de Desenvolvimento:
- Raspberry Pi Pico SDK
- Compilador arm-none-eabi-gcc
- CMake (versão 3.12 ou superior)

### Passos para Compilar
##### 1. Clone o repositório:
   ```bash
   git clone https://github.com/seu-usuario/genius-pico-w.git
   cd genius-pico-w
  ```
##### 2. Configure o projeto com CMake:
```bash
   mkdir build
  cd build
  cmake ..
  ```
##### 3. Compile o projeto:
```bash
   make
  ```
##### 4. Conecte o Raspberry Pi Pico W ao computador no modo de bootloader (segure o botão BOOTSEL enquanto conecta o USB).

##### 5. Copie o arquivo genius-pico-w.uf2 para o dispositivo:
```bash
   cp genius-pico-w.uf2 /media/seu-usuario/RPI-RP2/
  ```

## Configuração dos Pinos 
|     | Componentes              | GPIO                                           |
| --- | ------------------------ | ---------------------------------------------- |
| 1   | Display OLED             | A-GPIO14<br>SCL-GPIO15                         |
| 2   | Botões                   | GPIO5<br>GPIO6                                 |
| 3   | Buzzer                   | GPIO10<br>GPIO21                               |
| 4   | Matriz de LEDs Coloridos | GPIO7, 5x5                                     |

## Como Jogar 🕹️
#### Inicialização:
- Ao ligar o jogo, a matriz de LEDs exibirá uma animação de tutorial.
- O jogo começará automaticamente após o tutorial.

#### Jogabilidade:
- O jogo gerará uma sequência de sons.
- Repita a sequência pressionando os botões correspondentes.
- A cada nível concluído com sucesso, a sequência aumentará.

#### Game Over:
- Se você errar a sequência, o jogo exibirá uma animação de "Game Over" e reiniciará.

#### Vitória:
- A cada nível concluído, o jogo exibirá uma animação de vitória e avançará para o próximo nível.
