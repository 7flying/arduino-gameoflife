#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
#define STARTS_WITH 10 // Number of random alive cells to start with
Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();
// 0:dead, 1:alive
uint8_t board [][8] = { {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}
                      };
uint8_t neighbors [][8] = { {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}
                          };
void setup() {
 matrix.begin(0x70);
 randomSeed(analogRead(0));
 randomStart();
}
/* Initializes the board at random */
void randomStart() {
 for(uint8_t i = 0; i < STARTS_WITH; i++)
   board[random(8)][random(8)] = 1;
}
/* Paints the board */
void paint() {
 matrix.clear();
 for(uint8_t i = 0; i < 8; i++){
  for(uint8_t j = 0; j < 8; j++){
    if(board[i][j] == 1)
      matrix.drawPixel(i,j,LED_YELLOW);
  } 
 }
 matrix.writeDisplay();
}
/* Counts the neighbors of each cell */
void countNeighbors() {
 // Plan
 // |1|2|3|
 // |4|x|5|
 // |6|7|8|
 for(uint8_t i = 0; i<8; i++) {
   for(uint8_t j = 0; j<8; j++) {
     int x = i, y = j, markNX = 0, markNY = 0, markPX = 0;
     neighbors[i][j] = 0;
     // Negatives
     if(x - 1 >= 0) {
       markNX = 1;
       if(board[x-1][y])// plan 4
         neighbors[i][j]++;
     }
     if(y - 1 >= 0) {
       markNY = 1;
       if(board[x][y-1])// plan 2
         neighbors[i][j]++;
       if(markNX){
         if(board[x-1][y-1])// plan 1
            neighbors[i][j]++;
       }
     }
     // Positives
     if(x + 1 < 8) {
       markPX = 1;
       if(board[x+1][y])// plan 5
         neighbors[i][j]++;
       if(markNY) {
         if(board[x+1][y-1]) // plan 3
           neighbors[i][j]++;
      }
     }
     if(y + 1 < 8) {
       if(board[x][y+1])// plan 7
         neighbors[i][j]++;
       if(markPX){
         if(board[x+1][y+1])// plan 8
           neighbors[i][j]++;
       }
       if(markNX){
         if(board[x-1][y+1])// plan 6
           neighbors[i][j]++;
       }  
     }
   }
 }
}
/* Generates next generation */
void nextGeneration() {
  // Cell dies: four or more neighbors (overpopulation),one or none neighbor (isolation).
  // Cell survives: two or three neighbors
  // Birth: 3 neighbors
  for(uint8_t i = 0; i < 8; i++){
    for(uint8_t j = 0; j < 8; j++){
      if(neighbors[i][j] < 2 || neighbors[i][j] > 3)  
        board[i][j] = 0;
      else
        if(neighbors[i][j] == 3)
          board[i][j] = 1;
    }
  }
}

void loop() {
  paint();
  countNeighbors();
  delay(450);
  nextGeneration();
}
