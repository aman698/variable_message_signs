#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#pragma GCC diagnostic ignored "-Wnarrowing"
#pragma GCC diagnostic ignored "-Woverflow"
#pragma GCC diagnostic warning "-Wnarrowing"
#pragma GCC diagnostic warning "-Woverflow"

/*
   PIN DEFINES FOR PANEL
*/
#define PIN_A 6
#define PIN_B 7
#define PIN_C 8
#define PIN_D 9
#define PIN_E -1
#define PIN_nOE 10
#define PIN_SCLK 14
uint8_t addressMuxList[] = { PIN_A , PIN_B , PIN_C };
uint8_t RGBPinsList[] = { 11, 0, 1, 2, 3, 4, 5 }; // CLK, R0, G0, B0, R1, G1, B1

/*
 * Panel Specifications
 * Number of Panels in X Direction
 * Number of Panels in Y Direction
 * Dual Buffering Enable/Disable (Use swapBuffers(true) command)
 * 
 * Type of Panel Being Used
 * Colour Mode Used
 * Maximum Brightness
 * Minimum Brightness
 * 
 */
 
#define DISPLAYS_ACROSS 4
#define DISPLAYS_DOWN 3
#define ENABLE_DUAL_BUFFER false
#define PANELTYPE RGB32x32_S8_maxmurugan
#define PANELCOLORMODE COLOR_4BITS
#define MaxPanelBrightness 250
#define MinPanelBrightness 50
#define EEPROM_IP_START 0  // Define EEPROM starting address for IP storage
#define EEPROM_SIZE 512     // Define EEPROM size

/*
 * COLOUR DEFINES
 */
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFA00
#define WHITE    0xFFFF
#define ORANGE   0xFCBC

#define ETHERNET_SS_PIN 17
#define HeartBeatLed 22
#define HARDRST 15
#define LDR 25
/*
   ETHERNET CONFIGS
*/

#define SERVER_PORT 1000
byte SERVER_MAC[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
const int ip_array[4] = {192, 168, 1, 182};

/*
   SERIAL CONFIGS
*/
#define SERIAL_BAUDRATE 115200
#define SERIAL_INTERFACE Serial
#define COM_PORT Serial



#endif
