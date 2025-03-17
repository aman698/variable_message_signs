#include <Arduino.h>
#include <SPI.h>
#include <EEPROM.h>
#include <Ethernet.h>
#include "bitmap.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "config.h"
#include "commands_helper.h"

//#include "commands_config.h"

#include "DMD_RGB.h"
#include <stdio.h>
#include "fonts/FONT8.h"
#include "fonts/FONT10.h"
#include "fonts/FONT12.h"
#include "fonts/FONT14.h"
#include "fonts/FONT16.h"
#include "fonts/FONT18.h"
#include "fonts/FONT20.h"
#include "fonts/FONT22.h"
#include "fonts/FONT24.h"
#include "fonts/FONT26.h"
#include "fonts/FONT28.h"
#include "fonts/FONT30.h"
#include "fonts/FONT32.h"
#include "fonts/FONT34.h"
#include "fonts/FONT36.h"
#include "fonts/FONT38.h"
#include "fonts/FONT40.h"
#include "fonts/FONT42.h"
#include "fonts/FONT44.h"
#include "fonts/FONT46.h"
#include "fonts/FONT48.h"
#include "fonts/FONT50.h"
#include "fonts/FONT52.h"
#include "fonts/FONT54.h"
#include "fonts/FONT56.h"
#include "fonts/FONT58.h"
#include "fonts/FONT60.h"
#include "fonts/FONT62.h"
#include "fonts/FONT64.h"
#include "fonts/FONT66.h"
#include "fonts/FONT68.h"
#include "fonts/FONT70.h"
#include "fonts/FONT86.h"
#include "fonts/FONT95.h"

#include "fonts/Bahnschrift_Condensed30_b_033_126.h"
#include "fonts/Bahnschrift_Condensed36_b_037_057.h"
#include "fonts/Bahnschrift_Condensed48_b_037_057.h"
#include "fonts/Microsoft_Sans_Serif84_033_126.h"
#include "gfx_fonts/GlametrixBold12pt7b.h"
#include "st_fonts/SystemFont5x7.h"
#include "fonts/Microsoft_Sans_Serif100_033_126.h"
unsigned long previousMillis = 0;  // Stores the last time the second was updated
const long interval = 1000;        // 1 second interval
int lightInit;  // initial value
int lightVal;   // light reading;
int timestamp;
const uint16_t* bitmaps[] = { flag };
int state;

struct adc {
  volatile uint32_t CS, RESULT,
    FCS, FIFO, DIV, INTR, INTE, INTF,
    INTS;
};
#define ADC ((struct adc*)0x4004C000)
int time_hour = 0, time_min = 0, time_sec = 0;  // Global time variables
EthernetClient client;
EthernetServer server = EthernetServer(SERVER_PORT);
String AliveN = "START,ALIVE,";

DMD_RGB<PANELTYPE, PANELCOLORMODE> PANEL(
  addressMuxList,
  PIN_nOE,
  PIN_SCLK,
  RGBPinsList,
  DISPLAYS_ACROSS,
  DISPLAYS_DOWN,
  ENABLE_DUAL_BUFFER);

DMD_Standard_Font font1(FONT8);
DMD_Standard_Font font2(FONT10);
DMD_Standard_Font font3(FONT12);
DMD_Standard_Font font4(FONT14);
DMD_Standard_Font font5(FONT16);
DMD_Standard_Font font6(FONT18);
DMD_Standard_Font font7(FONT20);
DMD_Standard_Font font8(FONT22);
DMD_Standard_Font font9(FONT24);
DMD_Standard_Font font10(FONT26);
DMD_Standard_Font font11(FONT28);
DMD_Standard_Font font12(FONT30);
DMD_Standard_Font font13(FONT32);
DMD_Standard_Font font14(FONT34);
DMD_Standard_Font font15(FONT36);
DMD_Standard_Font font16(FONT38);
DMD_Standard_Font font17(FONT40);
DMD_Standard_Font font18(FONT42);
DMD_Standard_Font font19(FONT44);
DMD_Standard_Font font20(FONT46);
DMD_Standard_Font font21(FONT48);
DMD_Standard_Font font22(FONT50);
DMD_Standard_Font font23(FONT52);
DMD_Standard_Font font24(FONT54);
DMD_Standard_Font font25(FONT56);
DMD_Standard_Font font26(FONT58);
DMD_Standard_Font font27(FONT60);
DMD_Standard_Font font28(FONT62);
DMD_Standard_Font font29(FONT64);
DMD_Standard_Font font30(FONT66);
DMD_Standard_Font font31(FONT68);
DMD_Standard_Font font32(FONT70);
DMD_Standard_Font font33(FONT86);
DMD_Standard_Font font34(FONT95);


DMD_Standard_Font fontHeadline(Bahnschrift_Condensed30_b_033_126);
DMD_Standard_Font font36(Bahnschrift_Condensed36_b_037_057);
DMD_Standard_Font font84(Microsoft_Sans_Serif84_033_126);
DMD_Standard_Font font100(Microsoft_Sans_Serif100_033_126);

//float getTemperature();
void HeartBeat();
void checkHardReset();
String getMessageEthernetk();
int parseCommand(String str);
void printAlive();
void writeToDisplay();
void drawImage(int imageSize);
void clearDisplay(int x1, int x2, int y1, int y2);

void clearDisplay(int x1, int y1, int x2, int y2) {
  int i = x1;
  while (y1 < y2) {
    while (i < x2) {
      PANEL.drawPixel(i, y1, BLACK);
      i++;
    }
    y1++;
    i = x1;
  }
}
void writeToDisplay(int x, int y, String text, int fontColour, int fontSize) {
  switch (fontSize) {
    case 1: PANEL.selectFont(&font1); break;
    case 2: PANEL.selectFont(&font2); break;
    case 3: PANEL.selectFont(&font3); break;
    case 4: PANEL.selectFont(&font4); break;
    case 5: PANEL.selectFont(&font5); break;
    case 6: PANEL.selectFont(&font6); break;
    case 7: PANEL.selectFont(&font7); break;
    case 8: PANEL.selectFont(&font8); break;
    case 9: PANEL.selectFont(&font9); break;
    case 10: PANEL.selectFont(&font10); break;
    case 11: PANEL.selectFont(&font11); break;
    case 12: PANEL.selectFont(&font12); break;
    case 13: PANEL.selectFont(&font13); break;
    case 14: PANEL.selectFont(&font14); break;
    case 15: PANEL.selectFont(&font15); break;
    case 16: PANEL.selectFont(&font16); break;
    case 17: PANEL.selectFont(&font17); break;
    case 18: PANEL.selectFont(&font18); break;
    case 19: PANEL.selectFont(&font19); break;
    case 20: PANEL.selectFont(&font20); break;
    case 21: PANEL.selectFont(&font21); break;
    case 22: PANEL.selectFont(&font22); break;
    case 23: PANEL.selectFont(&font23); break;
    case 24: PANEL.selectFont(&font24); break;
    case 25: PANEL.selectFont(&font25); break;
    case 26: PANEL.selectFont(&font26); break;
    case 27: PANEL.selectFont(&font27); break;
    case 28: PANEL.selectFont(&font28); break;
    case 29: PANEL.selectFont(&font29); break;
    case 30: PANEL.selectFont(&font30); break;
    case 31: PANEL.selectFont(&font31); break;
    case 32: PANEL.selectFont(&font32); break;
    case 33: PANEL.selectFont(&font84); break;
    case 34: PANEL.selectFont(&font34); break;
    case 35: PANEL.selectFont(&font36); break;
    case 36: PANEL.selectFont(&font100); break;

  }

  char buf[100];
  text.toCharArray(buf, text.length() + 1);
  int fclr = 0;
  //fclr = fontColour;

  switch (fontColour) {
    case 1: fclr = BLACK; break;
    case 2: fclr = BLUE; break;
    case 3: fclr = RED; break;
    case 4: fclr = GREEN; break;
    case 5: fclr = CYAN; break;
    case 6: fclr = MAGENTA; break;
    case 7: fclr = YELLOW; break;
    case 8: fclr = WHITE; break;
    case 9: fclr = ORANGE; break;
    default: fclr = fontColour; break;
  }

  PANEL.setTextColor(fclr, BLACK);
  PANEL.drawStringX(x, y, buf, fclr, 0);
}

void Headline() {
  PANEL.selectFont(&fontHeadline);
  PANEL.setTextColor(YELLOW, BLACK);
  PANEL.drawStringX(6, 2, "SPEED-KMph", YELLOW, 0);
  PANEL.swapBuffers(true);
}

void displaySpeed(int vehicleSpeed, int limit) {
  
  // For 4x4 panel
  unsigned long previousMillis = 0;
  const long interval = 500;
//  PANEL.clearScreen(true);
  //Headline();
 // PANEL.selectFont(&font34);

  int n = vehicleSpeed, digitCount = 0;
  do {
    n /= 10;
    ++digitCount;
  } while (n != 0);

  int x = 0, y = 0;
  n = vehicleSpeed;
  char s[20];
  sprintf(s, "%ld", n);
  int first_digit = s[0] - '0';

  if (digitCount == 1) {
    x = 45;
    y = 19;
  } else if (digitCount == 2) {
    x = 21;
    y = 19;
  } else if (digitCount == 3) {
    if (first_digit == 1) {
      x = 5;
      y = 19;
    } else if (first_digit > 1) {
      x = 0;
      y = 19;
    }
  }

  char sp[10] = "";
  sprintf(sp, "%d", vehicleSpeed);
  if (limit == 2){
    state == 2;
    PANEL.clearScreen(true);
    PANEL.selectFont(&font34);
    PANEL.setTextColor(YELLOW, BLACK);
    PANEL.drawStringX(x, y, sp, YELLOW, 0);
    PANEL.selectFont(&fontHeadline);
    PANEL.setTextColor(YELLOW, BLACK);
    //PANEL.drawStringX(6, 100, "UNDERSPEED", GREEN, 0);
    PANEL.swapBuffers(true);
  }
  else if (limit == 1) {
    state == 1;
    PANEL.clearScreen(true);
    PANEL.selectFont(&font34);
    PANEL.setTextColor(GREEN, BLACK);
    PANEL.drawStringX(x, y, sp, GREEN, 0);
    PANEL.selectFont(&fontHeadline);
    PANEL.setTextColor(GREEN, BLACK);
    PANEL.swapBuffers(true);

  } else if(limit == 0){
    state == 0;
    PANEL.clearScreen(true);
    PANEL.selectFont(&font34);
    PANEL.setTextColor(RED, BLACK);
    PANEL.drawStringX(x, y, sp, RED, 0);
    PANEL.selectFont(&fontHeadline);
    PANEL.setTextColor(RED, BLACK);
    PANEL.swapBuffers(true);
    }
  }

void checkHardReset() {
  static unsigned long st_time = millis();
  if (digitalRead(HARDRST) == LOW) {
    if (millis() - st_time > 10000) {
      if (digitalRead(HARDRST) == LOW) {
        EEPROM.write(0, 192);
        EEPROM.commit();
        EEPROM.write(1, 168);
        EEPROM.commit();
        EEPROM.write(2, 1);
        EEPROM.commit();
        EEPROM.write(3, 182);
        EEPROM.commit();
        Serial.print("Hogya");
      //  NVIC_SystemReset();
      }
    }
  }
}

String getMessageEthernet() {
  String str = "";
  size_t size;
  client = server.available();
  while ((size = client.available()) > 0) {
    char ch = client.read();
    str = str + String(ch);
  }
  str = str + "\0";
  return str;
}

int parseCommand(String str) {
  if (str != "") {
    int commaIndex = str.indexOf(',');
    int secondCommaIndex = str.indexOf(',', commaIndex + 1);
    String firstValue = str.substring(0, commaIndex);
    String secondValue = str.substring(commaIndex + 1);

    if (firstValue == "SET") {
      int commaIndex1 = str.indexOf(',');
      int secondCommaIndex1 = str.indexOf(',', commaIndex1 + 1);
      int thirdCommaIndex1 = str.indexOf(',', secondCommaIndex1 + 1);
      int fourthCommaIndex1 = str.indexOf(',', thirdCommaIndex1 + 1);
      int fifthCommaIndex1 = str.indexOf(',', fourthCommaIndex1 + 1);

      String firstValue1 = str.substring(0, commaIndex1);
      String secondValue1 = str.substring(commaIndex1 + 1, secondCommaIndex1);
      String thirdValue1 = str.substring(secondCommaIndex1 + 1, thirdCommaIndex1);
      String fourthValue1 = str.substring(thirdCommaIndex1 + 1, fourthCommaIndex1);
      String fifthValue1 = str.substring(fourthCommaIndex1 + 1, fifthCommaIndex1);

      EEPROM.write(0, secondValue1.toInt());
      EEPROM.commit();
      EEPROM.write(1, thirdValue1.toInt());
      EEPROM.commit();
      EEPROM.write(2, fourthValue1.toInt());
      EEPROM.commit();
      EEPROM.write(3, fifthValue1.toInt());
      EEPROM.commit();

   //   NVIC_SystemReset();
    } else if (firstValue == "SETS") {
      int commaIndex1 = str.indexOf(',');
      int secondCommaIndex1 = str.indexOf(',', commaIndex1 + 1);
      int thirdCommaIndex1 = str.indexOf(',', secondCommaIndex1 + 1);

      String firstValue1 = str.substring(0, commaIndex1);
      String secondValue1 = str.substring(commaIndex1 + 1, secondCommaIndex1);

      EEPROM.write(5, secondValue1.toInt());
      EEPROM.commit();

    //  NVIC_SystemReset();
    } else if (firstValue == "SETP") {
      int commaIndex1 = str.indexOf(',');
      int secondCommaIndex1 = str.indexOf(',', commaIndex1 + 1);
      int thirdCommaIndex1 = str.indexOf(',', secondCommaIndex1 + 1);

      String firstValue1 = str.substring(0, commaIndex1);
      String secondValue1 = str.substring(commaIndex1 + 1, secondCommaIndex1);

      EEPROM.write(4, secondValue1.toInt());
      EEPROM.commit();
    //  NVIC_SystemReset();
    }
    if (firstValue == "SPEED") {
      int commaIndex1 = str.indexOf(',');
      int secondCommaIndex1 = str.indexOf(',', commaIndex1 + 1);
      int thirdCommaIndex1 = str.indexOf(',', secondCommaIndex1 + 1);

      String firstValue1 = str.substring(0, commaIndex1);
      String secondValue1 = str.substring(commaIndex1 + 1, secondCommaIndex1);
      String thirdValue1 = str.substring(secondCommaIndex1 + 1, thirdCommaIndex1);

      int vehicle_speed = secondValue1.toInt();
      int limit = thirdValue1.toInt();
      state = thirdValue1.toInt();

      displaySpeed(vehicle_speed, limit);
      server.print(vehicle_speed);
      server.print(" ");
      server.print(limit);
    } else if(firstValue == "TIME"){
      int commaIndex1 = str.indexOf(',');
      int secondCommaIndex1 = str.indexOf(',', commaIndex1 + 1);
      int thirdCommaIndex1 = str.indexOf(',', secondCommaIndex1 + 1);
      int fourthCommaIndex1 = str.indexOf(',', thirdCommaIndex1 + 1);

      String firstValue1 = str.substring(0, commaIndex1);
      String secondValue1 = str.substring(commaIndex1 + 1, secondCommaIndex1);
      String thirdValue1 = str.substring(secondCommaIndex1 + 1, thirdCommaIndex1);
      String fourthValue1 = str.substring(thirdCommaIndex1 + 1, fourthCommaIndex1);

      time_hour = secondValue1.toInt();
      time_min = thirdValue1.toInt();
      time_sec = fourthValue1.toInt();
      server.print(time_hour);
      server.print(" ");
      server.print(time_min);
      server.print(" ");
      server.print(time_sec);
    } else if (firstValue == "TEXT") {
      int packetIndex1 = str.indexOf(',');
      int packetIndex2 = str.indexOf(',', packetIndex1 + 1);
      int packetIndex3 = str.indexOf(',', packetIndex2 + 1);
      int packetIndex4 = str.indexOf(',', packetIndex3 + 1);
      int packetIndex5 = str.indexOf(',', packetIndex4 + 1);
      int packetIndex6 = str.indexOf(',', packetIndex5 + 1);

      String packetValue1 = str.substring(0, packetIndex1);
      String packetValue2 = str.substring(packetIndex1 + 1, packetIndex2);
      String packetValue3 = str.substring(packetIndex2 + 1, packetIndex3);
      String packetValue4 = str.substring(packetIndex3 + 1, packetIndex4);
      String packetValue5 = str.substring(packetIndex4 + 1, packetIndex5);
      String packetValue6 = str.substring(packetIndex5 + 1, packetIndex6);

      int xCoord = packetValue2.toInt();
      int yCoord = packetValue3.toInt();
      String usrMessage = packetValue4;
      int fontColour = packetValue5.toInt();
      int fontSize = packetValue6.toInt();

      writeToDisplay(xCoord, yCoord, usrMessage, fontColour, fontSize);
    } else if (firstValue == "CLEAR") {
      int packetIndex1 = str.indexOf(',');
      int packetIndex2 = str.indexOf(',', packetIndex1 + 1);
      int packetIndex3 = str.indexOf(',', packetIndex2 + 1);
      int packetIndex4 = str.indexOf(',', packetIndex3 + 1);
      int packetIndex5 = str.indexOf(',', packetIndex4 + 1);

      String packetValue1 = str.substring(0, packetIndex1);
      String packetValue2 = str.substring(packetIndex1 + 1, packetIndex2);
      String packetValue3 = str.substring(packetIndex2 + 1, packetIndex3);
      String packetValue4 = str.substring(packetIndex3 + 1, packetIndex4);
      String packetValue5 = str.substring(packetIndex4 + 1, packetIndex5);

      int x1 = packetValue2.toInt();
      int y1 = packetValue3.toInt();
      int x2 = packetValue4.toInt();
      int y2 = packetValue5.toInt();

      int i = x1;
      while (y1 < y2) {
        while (i < x2) {
          PANEL.drawPixel(i, y1, BLACK);
          i++;
        }
        y1++;
        i = x1;
      }
    }
  }
  return -1;
}

void printAlive() {
  delay(50);
  //Date = String(day()) + ":" + String(month()) + ":" + String(year());
  //Times = String(hour()) + ":" + String(minute()) + ":" + String(second());
  AliveN = AliveN + ",";
  AliveN = AliveN + "E";
  AliveN = AliveN + "N";
  AliveN = AliveN + "D";
  AliveN = AliveN + "\0";

  server.println(AliveN);
  Serial.println(AliveN);
  AliveN = "START,ALIVE,";
}

void HeartBeat() {
  digitalWrite(HeartBeatLed, HIGH);
  delay(50);
  digitalWrite(HeartBeatLed, LOW);
  delay(50);
}

void drawImage(int imagesize, int startX, int startY, int x, int y) {
  //uint16_t* imageData = (uint16_t*)malloc(132000);
  uint16_t imageData[16385];
  for (int index = 0; index < 16385; index++) {
    imageData[index] = BLACK;
  }
  int ptr = imagesize, i = 0;
  String str = "";
  char* ch;
  do {
    str = getMessageEthernet();
    if (str != 0) {
      if (str == "!") {
        break;
      }
      char arr[str.length() + 1];
      strcpy(arr, str.c_str());
      imageData[i] = strtoul(arr, &ch, 16);
      //server.println(imageData[i]);
      server.println(i);
      //server.println(ptr);
      i++;
      ptr--;
    }
  } while (ptr);
  server.println("Done");
  PANEL.drawRGBBitmap((PANEL.width() - 32) + startX, 0 + startY, imageData, x, y);
}

void timee() {
    unsigned long currentMillis = millis();

    // Check if 1 second has passed
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;  // Update previous time

        // Increment time
        time_sec++;

        // Update minutes and hours
        if (time_sec >= 60) {
            time_sec = 0;
            time_min++;
        }
        if (time_min >= 60) {
            time_min = 0;
            time_hour++;
        }
        if (time_hour >= 24) {
            time_hour = 0;
        }

        // Clear display and update time
        clearDisplay(0, 0, 128, 16);  // Adjust based on screen size
        writeToDisplay(59, 0, String(time_hour) + ":" +
                              (time_min < 10 ? "0" : "") + String(time_min) + ":" +
                              (time_sec < 10 ? "0" : "") + String(time_sec), BLUE, 7);

        // Print time to Serial Monitor (for debugging)
        Serial.print("Time: ");
        Serial.print(time_hour);
        Serial.print(":");
        Serial.print(time_min < 10 ? "0" : ""); Serial.print(time_min);
        Serial.print(":");
        Serial.print(time_sec < 10 ? "0" : ""); Serial.println(time_sec);
    }
}

void LDR1(){
  
  /*if(lightVal - lightInit <  50)*/
  if(digitalRead(LDR) == HIGH){

    PANEL.setBrightness(MinPanelBrightness);
   // Serial.println("LED LOW");

  } 
  else {
    PANEL.setBrightness(MaxPanelBrightness);
    //Serial.println("LED HIGH");
  }
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(64);
  //lightInit = analogRead(LDR);
   for(int i = 0; i < 64; i++){
    EEPROM.write(i, 0xFF);
  }
  EEPROM.commit();

  PANEL.init();
  Ethernet.init(ETHERNET_SS_PIN);
  // Initialize I2C1
  
  Serial.print("PORT:");
  int port = SERVER_PORT;
  if (EEPROM.read(5) < 254) {
    port = EEPROM.read(5);
  }
  Serial.println(port);
  if (EEPROM.read(0) != 255 && EEPROM.read(1) != 255 && EEPROM.read(2) != 255 && EEPROM.read(3) != 255) {
    IPAddress SERVER_IP(EEPROM.read(0), EEPROM.read(1), EEPROM.read(2), EEPROM.read(3));
    Ethernet.begin(SERVER_MAC, SERVER_IP);
  } else {
    IPAddress SERVER_IP(ip_array[0], ip_array[1], ip_array[2], ip_array[3]);
    Ethernet.begin(SERVER_MAC, SERVER_IP);
  }
  server.begin();

  Serial.print("My IP:");
  server.println(Ethernet.localIP());
  Serial.println(Ethernet.localIP());

  pinMode(HeartBeatLed, OUTPUT);
  pinMode(HARDRST, INPUT_PULLUP);
  pinMode(LDR, INPUT_PULLUP);
 // ADC->CS = 0x400B;
  PANEL.drawRGBBitmap(PANEL.width() - 128, 0, bitmaps[0], 128, 128);
  delay(3000);
}

void loop() {
  if (digitalRead(HARDRST) == LOW) {
    checkHardReset(); // Trigger hard reset if pin is LOW
  } 
  HeartBeat();
//  DateTime now = rtc.now(); // Get current time
  LDR1();
  //commented by NC - start
  String str = getMessageEthernet();
  if (str != "") {
    server.println(str);
    parseCommand(str);
    str = "";
  }
  //printAlive();
  timee();
}
