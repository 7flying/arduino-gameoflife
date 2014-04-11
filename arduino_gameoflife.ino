#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();
// 0:dead, 1:alive
uint8_t board [][8] = { {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0}
                      };
uint8_t die[][8] = {    {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0}
                   };
uint8_t birth[][8] = {  {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0}
                     };
void setup() {
 matrix.begin(0x70);
 randomSeed(analogRead(0));
}
void randomStart() {
 for(uint8_t i = 0; i < 5; i++)
   board[random(8)][random(8)] = 1;
}
void toZero() {
 for(uint8_t i = 0; i < 8; i++)
   for(uint8_t j = 0; j < 8; j++)
     board[j][i] = 0;
  
}
void paint() {
 matrix.clear();
 for(uint8_t i = 0; i < 8; i++){
  for(uint8_t j = 0; j < 8; j++){
    if(board[j][i] == 1)
      matrix.drawPixel(j,i,LED_GREEN);
  } 
 }
 matrix.writeDisplay();
}
void countNeighbors() {
 // TODO 
}

void loop() {
 randomStart();
 paint();
 delay(500);
 toZero();
}
