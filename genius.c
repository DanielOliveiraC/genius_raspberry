#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "inc/ssd1306.h"
#include "inc/ssd1306_i2c.h"
#include "inc/ssd1306_font.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include <ctype.h>
#include <string.h>
#include "matrix_led.h"

// Function prototypes
void matrix_tutorial();
void matrix_win();
void matrix_lose();

// Define I2C pins
const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

// Define GPIO pins
#define BUTTON1_PIN 5
#define BUTTON2_PIN 6
#define BUZZER1_PIN 10
#define BUZZER2_PIN 21

#define LED_COUNT 25
#define LED_PIN 7

// Tone frequencies
#define TONE1_FREQ 440  // A4 note
#define TONE2_FREQ 523   // C5 note

// Game variables
int sequence[100];
int player_sequence[100];
int level = 1;
char level_str[15];

// Function to play a tone on a buzzer
void play_tone(uint pin, int frequency) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);
    uint channel = pwm_gpio_to_channel(pin);

    float clock_divider = 125.0f;
    uint32_t wrap_value = (uint32_t)(125000000 / (frequency * clock_divider));

    pwm_set_clkdiv(slice_num, clock_divider); // Divisor clock - 1 MHz
    pwm_set_wrap(slice_num, wrap_value); // Wrap value 
    pwm_set_chan_level(slice_num, channel, wrap_value / 2); // 50% duty cycle
    pwm_set_enabled(slice_num, true); // Enable PWM
    sleep_ms(500); // Sleep for 500 ms
    pwm_set_enabled(slice_num, false); // Disable PWM
}

// Generate a random sequence
void generate_sequence(int *seq, int length) {
    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        seq[i] = rand() % 2 + 1;  // 1 for button1, 2 for button2
    }
}

// Play the sequence using buzzers
void play_sequence(int *seq, int length) {
    for (int i = 0; i < length; i++) {
        if (seq[i] == 1) {
            play_tone(BUZZER1_PIN, TONE1_FREQ);
        } else {
            play_tone(BUZZER2_PIN, TONE2_FREQ);
        }
        sleep_ms(300);  // Delay between tones
    }
}

// Get player input
void get_player_input(int *player_seq, int length) {
    for (int i = 0; i < length; i++) {
        while (true) {
            if (!gpio_get(BUTTON1_PIN)) {  // Button 1 pressed
                play_tone(BUZZER1_PIN, TONE1_FREQ);
                player_seq[i] = 1;
                sleep_ms(300);  // Debounce delay
                break;
            }
            if (!gpio_get(BUTTON2_PIN)) {  // Button 2 pressed
                play_tone(BUZZER2_PIN, TONE2_FREQ);
                player_seq[i] = 2;
                sleep_ms(300);  // Debounce delay
                break;
            }
        }
    }
}

// Check if player's sequence matches the generated sequence
bool check_sequence(int *seq, int *player_seq, int length) {
    for (int i = 0; i < length; i++) {
        if (seq[i] != player_seq[i]) {
            return false;
        }
    }
    return true;
}

// Game over function
void game_over() {
    printf("Game Over! Your score: %d\n", level - 1);
    for (int i = 0; i < 3; i++) {
        play_tone(BUZZER1_PIN, 220);
        play_tone(BUZZER2_PIN, 220);
        matrix_lose();
        sleep_ms(200);
    }
    sleep_ms(1000);
    level = 1;
}

int getIndex(int x, int y)
{
  // Se a linha for par (0, 2, 4), percorremos da esquerda para a direita.
  // Se a linha for ímpar (1, 3), percorremos da direita para a esquerda.
  if (y % 2 == 0)
  {
    return 24 - (y * 5 + x); // Linha par (esquerda para direita).
  }
  else
  {
    return 24 - (y * 5 + (4 - x)); // Linha ímpar (direita para esquerda).
  }
};

// matrix led functions
// win matrix
void matrix_win()
{
  for (int i = 0; i < 2; i++)
  {
    int matrix1[5][5][3] = {
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {54, 255, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {54, 255, 0}, {0, 0, 0}},
        {{54, 255, 0}, {0, 0, 0}, {54, 255, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {54, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}};

    for (int linha = 0; linha < 5; linha++)
    {
      for (int coluna = 0; coluna < 5; coluna++)
      {
        int posicao = getIndex(linha, coluna);
        npSetLED(posicao, matrix1[coluna][linha][0], matrix1[coluna][linha][1], matrix1[coluna][linha][2]);
      }
    }
    npWrite();
    sleep_ms(1000);

    int matrix2[5][5][3] = {
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {54, 255, 0}, {0, 0, 0}, {54, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{54, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {54, 255, 0}},
        {{0, 0, 0}, {54, 255, 0}, {54, 255, 0}, {54, 255, 0}, {0, 0, 0}}};

    for (int linha = 0; linha < 5; linha++)
    {
      for (int coluna = 0; coluna < 5; coluna++)
      {
        int posicao = getIndex(linha, coluna);
        npSetLED(posicao, matrix2[coluna][linha][0], matrix2[coluna][linha][1], matrix2[coluna][linha][2]);
      }
    }
    npWrite();
    sleep_ms(1000);
  }
}

// lose matrix
void matrix_lose() {
  for (int i = 0; i < 2; i++)
  {
    int matrix3[5][5][3] = {
        {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}},
        {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},
        {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}}};

    for (int linha = 0; linha < 5; linha++)
    {
      for (int coluna = 0; coluna < 5; coluna++)
      {
        int posicao = getIndex(linha, coluna);
        npSetLED(posicao, matrix3[coluna][linha][0], matrix3[coluna][linha][1], matrix3[coluna][linha][2]);
      }
    }
    npWrite();
    sleep_ms(1000);

    int matrix4[5][5][3] = {
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {255, 0, 0}, {0, 0, 0}, {255, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {255, 0, 0}, {255, 0, 0}, {255, 0, 0}, {0, 0, 0}},
        {{255, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 0, 0}}};

    for (int linha = 0; linha < 5; linha++)
    {
      for (int coluna = 0; coluna < 5; coluna++)
      {
        int posicao = getIndex(linha, coluna);
        npSetLED(posicao, matrix4[coluna][linha][0], matrix4[coluna][linha][1], matrix4[coluna][linha][2]);
      }
    }
    npWrite();
    sleep_ms(1000);
  }
}

// tutorial matrix
void matrix_tutorial()
{
  for (int i = 0; i < 2; i++)
  {
    
    int matrix5[5][5][3] = {
        {{0, 0, 0}, {0, 0, 0}, {54, 255, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {54, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{54, 255, 0}, {0, 0, 0}, {54, 255, 0}, {54, 255, 0}, {54, 255, 0}},
        {{0, 0, 0}, {54, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {54, 255, 0}, {0, 0, 0}, {0, 0, 0}}};

    for (int linha = 0; linha < 5; linha++)
    {
      for (int coluna = 0; coluna < 5; coluna++)
      {
        int posicao = getIndex(linha, coluna);
        npSetLED(posicao, matrix5[coluna][linha][0], matrix5[coluna][linha][1], matrix5[coluna][linha][2]);
      }
    }
    play_tone(BUZZER1_PIN, TONE1_FREQ);
    npWrite();
    npClear();
    sleep_ms(1000);
    play_tone(BUZZER2_PIN, TONE2_FREQ);
    int matrix6[5][5][3] = {
        {{0, 0, 0}, {0, 0, 0}, {54, 255, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {54, 255, 0}, {0, 0, 0}},
        {{54, 255, 0}, {54, 255, 0}, {54, 255, 0}, {0, 0, 0}, {54, 255, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {54, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {54, 255, 0}, {0, 0, 0}, {0, 0, 0}}};

    for (int linha = 0; linha < 5; linha++)
    {
      for (int coluna = 0; coluna < 5; coluna++)
      {
        int posicao = getIndex(linha, coluna);
        npSetLED(posicao, matrix6[coluna][linha][0], matrix6[coluna][linha][1], matrix6[coluna][linha][2]);
      }
    }
    npWrite();
    play_tone(BUZZER2_PIN, TONE2_FREQ);
    sleep_ms(1000);
    npClear();
  }
}

void initialize(){
    matrix_tutorial();
}

// Main function
int main() {
    stdio_init_all();

    
    // Initialize I2C
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);


    // Initialize OLED display
    ssd1306_init();

    // Initialize matrix LED
    npInit(LED_PIN);
    npClear();
    npWrite();
    // Display
    struct render_area frame_area = {
        start_column : 0,
        end_column : ssd1306_width - 1,
        start_page : 0,
        end_page : ssd1306_n_pages - 1
    };

    calculate_render_area_buffer_length(&frame_area);

    // Clear the display
    uint8_t ssd[ssd1306_buffer_length];
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);

    // Initialize buttons
    gpio_init(BUTTON1_PIN);
    gpio_init(BUTTON2_PIN);
    gpio_set_dir(BUTTON1_PIN, GPIO_IN);
    gpio_set_dir(BUTTON2_PIN, GPIO_IN);
    gpio_pull_up(BUTTON1_PIN);
    gpio_pull_up(BUTTON2_PIN);

    // Initialize buzzers
    gpio_init(BUZZER1_PIN);
    gpio_init(BUZZER2_PIN);
    gpio_set_dir(BUZZER1_PIN, GPIO_OUT);
    gpio_set_dir(BUZZER2_PIN, GPIO_OUT);

    // Initialize game
    initialize();
    npClear();
    npWrite();
    // Main game loop
    while (true) {
        memset(ssd, 0, ssd1306_buffer_length);
        sprintf(level_str, "Level: %d", level);
        ssd1306_draw_string(ssd, 5, 16, level_str);
        render_on_display(ssd, &frame_area);
        generate_sequence(sequence, level);
        play_sequence(sequence, level);
        get_player_input(player_sequence, level);
        tight_loop_contents();

        if (check_sequence(sequence, player_sequence, level)) {
            matrix_win();
            level++;
            sleep_ms(1000);
        } else {
            game_over();
        }
        npClear();
        npWrite();
    }

    return 0;
}