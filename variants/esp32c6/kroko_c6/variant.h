#define I2C_SDA 22 // I2C pins for this board
#define I2C_SCL 23

// #define LED_POWER 8    // If defined we will blink this LED
// #define LED_STATE_ON 0 // State when LED is lit
// This is a LED_WS2812 not a standard LED
#define HAS_NEOPIXEL                         // Enable the use of neopixels
#define NEOPIXEL_COUNT 1                     // How many neopixels are connected
#define NEOPIXEL_DATA 8                      // gpio pin used to send data to the neopixels
#define NEOPIXEL_TYPE (NEO_GRB + NEO_KHZ800) // type of neopixels in use

#define LORA_SCK 6
#define LORA_MISO 4
#define LORA_MOSI 5
#define LORA_CS 7
#define LORA_RESET 10
#define USE_SX1262
#define SX126X_CS LORA_CS
#define SX126X_DIO1 12
#define SX126X_DIO2 16
#define SX126X_BUSY 11
#define SX126X_RESET LORA_RESET
#define SX126X_RXEN 21
#define SX126X_TXEN 20
// #define SX126X_DIO2_AS_RF_SWITCH
#define SX126X_DIO3_TCXO_VOLTAGE 1.8

#define SERIAL_PRINT_PORT 1