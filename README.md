# Genius para Raspberry Pi Pico W <img src="https://github.com/user-attachments/assets/03013913-1149-4ae5-9c10-378c22b11763" width="40"></img>
Este projeto é uma implementação do clássico jogo Genius (também conhecido como Simon) para o Raspberry Pi Pico W. O jogo desafia a
memória do jogador, que deve repetir uma sequência de cores e sons gerada aleatoriamente. A cada nível, a sequência aumenta, tornando o jogo mais difícil.
Contudo, neste projeto, o jagador deve se atentar aos sons e conseguir reproduzir a sequência aleatória de cada uma das rodadas! 

## Componentes Utilizados <img src="https://github.com/user-attachments/assets/6e97c3dd-0d8c-4a28-872a-81dd4c81e9bd" width="40"></img> 
- Placa BitDogLab (equipada com Raspberry Pi Pico W: Microcontrolador principal).
- Matriz de LEDs 5x5: Para exibir os resultados (errado ou correto)
- Buzzers: Para gerar os tons à cada botão correspondente.
- Botões: Para a interação do jogador.
- Display OLED SSD1306 (opcional): Para exibir informações como o level atual.

## Funcionalidades do Jogo <img src="https://github.com/user-attachments/assets/d9818565-10d8-4555-874a-46773732866f" width="40"></img> 

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

## Como Compilar e Executar <img src="https://github.com/user-attachments/assets/602d7534-e8cc-48f0-8690-d66580b68210" width="40"></img> 

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

## Configuração dos Pinos <img src="https://github.com/user-attachments/assets/4bf5420f-6c61-426e-b869-d695d575b9be" width="40"></img>
|     | Componentes              | GPIO                                           |
| --- | ------------------------ | ---------------------------------------------- |
| 1   | Display OLED             | A-GPIO14<br>SCL-GPIO15                         |
| 2   | Botões                   | GPIO5<br>GPIO6                                 |
| 3   | Buzzer                   | GPIO10<br>GPIO21                               |
| 4   | Matriz de LEDs Coloridos | GPIO7, 5x5                                     |

##  Como Jogar <img src="https://github.com/user-attachments/assets/0a3b23c0-7b92-410b-9c41-2cd3e9980f54" width="40"></img> 
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

## Demonstração <img src="https://github.com/user-attachments/assets/b880eec2-464d-48a9-8f4b-db69884e587c" width="40"></img> 

<p align="center">
  <a href="https://www.youtube.com/watch?v=wu3_sKCZTDc">
    <img src="https://www.youtube.com/watch?v=wu3_sKCZTDc.jpg" alt="Vídeo do Projeto" width="560" height="315">
  </a>
</p>

