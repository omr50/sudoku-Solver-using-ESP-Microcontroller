// https://forum.pjrc.com/threads/66277-ILI9341_t3n-h-problem-on-SPI1
// check that site out for buttons

//#include "Adafruit_GFX.h"
//#include "Adafruit_ILI9341.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Wire.h>
// For the Adafruit shield, these are the default.
#define TFT_DC D4
#define TFT_CS D8
#define TS_CS D2
#include <Wire.h>
#include <XPT2046_Touchscreen.h>
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
//#define TFT_DC 2
//#define TFT_CS 15
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
XPT2046_Touchscreen ts(TS_CS);
//functions-------------------
bool checkRow(int board[][9]);
bool checkCol(int board[][9]);
bool checkBox(int board[][9]);
bool checkBoard(int board[][9]);
int emptySpace(int board[][9]);
void insertNum(int board[][9], int index, int num);
bool canPlace(int board[][9], int nextCoord, int num);
bool solve(int board[][9]);
void printBoard(int board[][9]);
void addRow(int board[][9], int arr[], int row);
void addCol(int board[][9], int arr[], int col);
void addBox(int board[][9], int arr[], int row, int col);
void fillIn(int board[][9]);
bool notInRow(int board[][9], int k, int row);
bool notInCol(int board[][9], int k, int col);
void boxDeduction(int board[][9], int row, int col, int& fillIn);
void displayBoard(int board[][9]);
void boardTouched(int board[][9]);
void loadOriginals(int board[][9], int original[]);
bool notOriginal(int board[][9], int original[], int x, int y);
void randomBoard(int board[][9]);
void loadNew(int board[][9], int newBoard[][9], int original[]);
int board[9][9] = {            
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0}
};
int spareBoard[9][9] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int board2[9][9] = {                // extra board for reset
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0}
};
int board3[9][9] = {                // extra board for reset
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0}
};
int original[81] = {0};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  tft.begin();
  loadOriginals(board, original);
  //fillIn(board);
  displayBoard(board);
  pinMode(TS_CS, OUTPUT);
  digitalWrite(TS_CS, HIGH);
  ts.begin();
//  calibrateTouchScreen();

}

int x = 0;
int y = 1;
int one = 0;
int z = 0;
void loop() {
  // put your main code here, to run repeatedly:
  
//if (one < 1){
//
//  if (solve(board)) {
//     printBoard(board);
//      one++;
//    }
//  displayBoard(board);
//}
boardTouched(board);
//
//
}

bool checkRow(int board[][9]) {
  for (int i = 0; i < 9; i++) {
    int arr[9] = {0};
    for (int j = 0; j < 9; j++) {
      if (board[i][j] != 0)
        if (arr[board[i][j] - 1] != 0 )
          return false;
        else
          arr[board[i][j] - 1] = board[i][j];
    }
  }
  return true;
}

// checks all nine columns to make sure they each have a valid combination of numbers
// otherwise returns false
bool checkCol(int board[][9]) {
  for (int i = 0; i < 9; i++) {
    int arr[9] = {0};
    for (int j = 0; j < 9; j++) {
      if (board[j][i] != 0)
        if (arr[board[j][i] - 1] != 0 )
          return false;
        else
          arr[board[j][i] - 1] = board[j][i];
    }
  }
  return true;
}
// checks all nine 3x3 boxes and makes sure they have valid combinations of numbers
//otherwise returns false
bool checkBox(int board[][9]) {
  for (int k = 0; k < 9; k++) {    // loops 9 times to check all 9 boxes  (each box is 3x3)
    int arr[9] = {0};
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        if (board[k / 3 * 3 + i][k % 3 * 3 + j] != 0)
          if (arr[board[k / 3 * 3 + i][k % 3 * 3 + j] - 1] != 0)
            return false;
          else
            arr[board[k / 3 * 3 + i][k % 3 * 3 + j] - 1] = board[k / 3 * 3 + i][k % 3 * 3 + j];
  }
  return true;
}

// returns true if the check box, check row, and check col (previous 3 functions) are all true
bool checkBoard(int board[][9]) {
  return (checkBox(board) && checkRow(board) && checkCol(board));
}

int emptySpace(int board[][9]) {
  for (int i = 0; i < 81; i++)
    if (board[i / 9][i % 9] == 0)
      return i;
  return -1;
}

// inserts number into board
void insertNum(int board[][9], int index, int num) {
  board[index / 9][index % 9] = num;
}

// checks if inserting a number will make the board invalid, if so then remove the added number.
bool canPlace(int board[][9], int nextCoord, int num) {
  insertNum(board, nextCoord, num);
  if (checkBoard(board)) return true;
  insertNum(board, nextCoord, 0);
  return false;
}

bool solve(int board[][9]) {
  int nextCoord = emptySpace(board);
  if (nextCoord == -1)
    return true;
  //printBoard(board);
  for (int i = 1; i <= 9; i++) {
    if (canPlace(board, nextCoord, i)) {
      insertNum(board, nextCoord, i);
      if (solve(board)) return true;
      else insertNum(board, nextCoord, 0);
    }
  }
  return false;
}
// Serial prints the board
void printBoard(int board[][9]) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++)
      Serial.print(board[i][j]);
    Serial.println("");
  }
}

void addRow(int board[][9], int arr[], int row) {
  for (int i = 0; i < 9; i++)
    if (board[row][i] != 0)
      arr[board[row][i] - 1] = board[row][i];
}

void addCol(int board[][9], int arr[], int col) {
  for (int i = 0; i < 9; i++)
    if (board[i][col] != 0)
      arr[board[i][col] - 1] = board[i][col];
}

void addBox(int board[][9], int arr[], int row, int col) {
  int boxnum = row / 3 * 3 + col / 3;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (board[boxnum / 3 * 3 + i][boxnum % 3 * 3 + j] != 0)
        arr[board[boxnum / 3 * 3 + i][boxnum % 3 * 3 + j] - 1] = board[boxnum / 3 * 3 + i][boxnum % 3 * 3 + j];
}

// checks if a certain value is in a row.
bool InRow(int board[][9], int k, int row) {
  for (int i = 0; i < 9; i++)
    if (board[row][i] == k)
      return true;
  return false;
}

//checks if a certain value is in a col.
bool InCol(int board[][9], int k, int col) {
  for (int i = 0; i < 9; i++)
    if (board[i][col] == k)
      return true;
  return false;
}

// Deduces square value by checking surrounding ones and making sure that they cannot be 
// the same value. For example if k = 9 and we are checking if coord (x, y) is k. We check all 
// surrounding boxes and check if they cannot be k. If they cannot = k then we know by 
// deduction that (x, y) = k. We do this by incrementing a counter everytime we come across
// a value that cannot = k. If the square is already filled or it is empty but has k in its
// row or column then by default it cannot = k. If counter reaches 8 then we know that 8 out of
// the 9 values in the box cannot equal to k so by deduction (x, y) is k.
void boxDeduction(int board[][9], int row, int col, int& fillIn) {
  int boxnum = row / 3 * 3 + col / 3;
  for (int k = 1; k <= 9 ; k++) {   // loop through all potential values
    int counter = 0;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (row == boxnum / 3 * 3 + i && col == boxnum % 3 * 3 + j)
          continue;
        else if (board[boxnum / 3 * 3 + i][boxnum % 3 * 3 + j] == k)
          counter = 9;
        else if (InRow(board, k, boxnum / 3 * 3 + i) || InCol(board, k, boxnum % 3 * 3 + j))
          counter++;
        else if (board[boxnum / 3 * 3 + i][boxnum % 3 * 3 + j] != 0)
          counter++;
      }
    }
    if (counter == 8) {
      fillIn++;
      board[row][col] = k;
    }
  }
}


void fillIn(int board[][9]) {

  // repeat until the number of fill ins is zero
  //(place a while loop around all this)
  // once the fill ins are zero
  // its time to do the back tracking
  int fillin = 1;
  while (fillin != 0) {  // keeps running until the board has no more coordinates that can be filled using these rules or until board is solved
    fillin = 0;
    for (int i = 0; i < 9; i++)
      for (int j = 0; j < 9; j++) {
        if (board[i][j] != 0) continue;
        int arr[9] = {0};
        addRow(board, arr, i);
        addCol(board, arr, j);
        addBox(board, arr, i, j);

        int index = -1;
        int counter = 0;
        for (int i = 0; i < 9; i++) {
          if (arr[i] == 0) {
            counter++;
            index = i;
          }
        }
        if (counter == 1) {
          board[i][j] = index + 1;
          fillin++;
        }
        else
          boxDeduction(board, i, j, fillin);   // if board location (i, j) isn't already filled try boxDeduction
      }
  }
  // check if there is only 1 zero element, get its index number and
  // then board[i][j] = index + 1;



}

void displayBoard(int board[][9]){
  tft.fillScreen(ILI9341_WHITE);
  int size1 = 234;
  int x = size1 / 9;
  for (int i = 0; i <= 9; i++)
    tft.drawLine(3 + x * i, 3, 3 + x * i, size1, ILI9341_BLACK);
  for (int i = 0; i <= 9; i++)
    tft.drawLine(3, 3 + x * i, size1, 3 + x * i, ILI9341_BLACK);
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++) {
      tft.setCursor(5 + x * i, 5 + x * j);
      tft.setTextColor(ILI9341_BLACK);
      tft.setTextSize(2);
//      tft.text(3 + x * i, 3, 3 + x * j, 3);
      if (board[j][i] != 0)
        tft.print(board[j][i]);
      else
        tft.print(" ");
    }
  tft.fillRect(4 + x * 6,4 + x * 9, x * 3,x-3, ILI9341_GREEN);  // check button
  tft.fillRect(4 + x * 6,4 + x * 10, x * 3,x-3, ILI9341_ORANGE); // solve button
  tft.fillRect(4 + x * 6,4 + x * 11, x * 2,x-3, ILI9341_RED); // reset button
  tft.fillRect(4 + x * 8,4 + x * 11, x * 1,x-3, ILI9341_LIGHTGREY); // random board (dice shape)
  tft.drawRect(4 + x * 8,4 + x * 11, x * 1,x-3, ILI9341_BLACK); 
  tft.fillCircle(8 + x * 8,8 + x * 11, 2, ILI9341_BLACK);  // two top circles
  tft.fillCircle(x * 9-1,8 + x * 11, 2, ILI9341_BLACK);
  
  tft.fillCircle(8 + x * 8,x * 12-6, 2, ILI9341_BLACK);  // two bottom circles
  tft.fillCircle(x * 9-1,x * 12-6, 2, ILI9341_BLACK);

  tft.fillCircle(x * 9-9,x * 12-12, 2, ILI9341_BLACK);//middle circle
  tft.setCursor(5 + x * 6,5 + x * 9);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.print("Check");
  tft.setCursor(5 + x * 6,5 + x * 10);
  tft.print("Solve");
  tft.setCursor(5 + x * 6,5 + x * 11);
  tft.setTextColor(ILI9341_WHITE);
  tft.print("  X");
  tft.setTextColor(ILI9341_BLACK);
  tft.fillRect(0, x * 10,130,55, ILI9341_CYAN);  // Number selector buttons
  for (int i = 0; i <= 9; i++){
    if (i < 5){
       tft.setCursor(x*i+5,5 + x * 10);
       tft.print(i);
    }
    else if (i <= 9){
      tft.setCursor(x*(i-5)+5,5 + x * 11);
       tft.print(i);
    }

  }
  for (int i = 0; i < 6; i++)
  tft.drawLine(x*i,x * 10, x*i, x*12, ILI9341_BLACK);
  tft.drawLine(0,x * 10, x*5, x*10, ILI9341_BLACK); // horizontal
  tft.drawLine(0,x * 11, x*5, x*11, ILI9341_BLACK); // horizontal
  tft.drawLine(0,x * 12, x*5, x*12, ILI9341_BLACK); // horizontal
}
TS_Point p = ts.getPoint();
int prev[2] = {-1};


void boardTouched(int board[][9]){
  boolean istouched = ts.touched();
  if (istouched) {
    TS_Point p = ts.getPoint();
    float X_div = ((float)(3790-290))/(float)9;
    float Y_div = ((float)(3835-1260))/(float)9;
    int x_coord = (p.y-290)/X_div;
    int y_coord = (3835-p.x)/Y_div;
    Serial.print("X = ");
    Serial.println(x_coord);
    Serial.print("Y = ");
    Serial.println(y_coord);
    int size1 = 234;
    int pr = size1 / 9;
    if(x_coord < 9 && y_coord < 9){   // sudoku board 
    if (prev[0] != -1){   // uncolor previous
      tft.fillRect(5 + pr * prev[0],5 + pr * prev[1],pr-3,pr-3, ILI9341_WHITE); 
      tft.setCursor(5 + pr * prev[0], 5 + pr * prev[1]);
      if (notOriginal(board, original, prev[1], prev[0]))
      tft.setTextColor(ILI9341_BLUE);
      else
      tft.setTextColor(ILI9341_BLACK);
      if (board[prev[1]][prev[0]] != 0)
      tft.print(board[prev[1]][prev[0]]);
    }
    if (notOriginal(board, original, y_coord, x_coord))
    tft.fillRect(5 + pr * x_coord,5 + pr * y_coord,pr-3,pr-3, ILI9341_BLUE); 
    else
    tft.fillRect(5 + pr * x_coord,5 + pr * y_coord,pr-3,pr-3, ILI9341_BLACK); 
    tft.setCursor(5 + pr * x_coord, 5 + pr * y_coord);
      tft.setTextColor(ILI9341_WHITE);
      if (board[y_coord][x_coord] != 0)
      tft.print(board[y_coord][x_coord]);
    prev[0] = x_coord;
    prev[1] = y_coord;
    }
   else if(y_coord == 9 && (x_coord >= 6 && x_coord < 9)) {  // Check
   for (int i = 0; i < 81; i++)
   spareBoard[i/9][i%9] = board[i/9][i%9];
   delay(50);
   fillIn(board);
   if (solve(board)){   // if board has valid answer
   bool correct = true;
   for (int i = 0; i < 81; i++)    // loop and check if all elements are same in both boards
   if (spareBoard[i/9][i%9] != board[i/9][i%9]){    // if not then print out wrong answer
    tft.setCursor(5, 9*pr+5);
    tft.setTextColor(ILI9341_RED);
    tft.fillRect(0, 5+pr * 9,pr*6+3,pr-5, ILI9341_WHITE); 
    tft.print("Wrong Answer");
    correct = false;
    break;
   }
    for (int i = 0; i < 81; i++)
    board[i/9][i%9] = board2[i/9][i%9];
   if (correct){
    tft.setCursor(5, pr * 9+5);
    tft.setTextColor(ILI9341_GREEN);
    tft.fillRect(0, 5+pr * 9,pr*6+3,pr-5, ILI9341_WHITE); 
    tft.print("Correct!");
   }
   }
   else{    //board isn't solvable so answer by default is false
    tft.setCursor(5, 9*pr+5);
    tft.setTextColor(ILI9341_RED);
    tft.fillRect(0, 5+pr * 9,pr*6+3,pr-5, ILI9341_WHITE); 
    tft.print("Wrong Answer");
   }
   

   
   }
   
   else if(y_coord == 10 && (x_coord >= 6 && x_coord < 9)){  // Solve
    fillIn(board);
    if (solve(board))
    displayBoard(board);
    else{
    tft.setCursor(5, pr * 9+5);
    tft.setTextColor(ILI9341_BLACK);
    tft.fillRect(0, pr * 9+5,pr*6+3,pr-5, ILI9341_WHITE); 
    tft.print("Invalid Board");
    }
   }
   else if(y_coord == 11 && (x_coord >= 6 && x_coord < 8)){  // clear
   loadNew(board, board3, original);
   displayBoard(board);
  }
  else if(y_coord == 11 && (x_coord == 8)){  // New Random board
   randomBoard(board, original);
   displayBoard(board);
  }
  else if ((y_coord == 10 || y_coord == 11) && (x_coord < 5)){    // selects from the number pad and adds to previously clicked position on board
    if (notOriginal(board, original, prev[1], prev[0])){
    board[prev[1]][prev[0]] = (y_coord-10)*5 + x_coord;   // only update if the square is not an original value on board
    tft.fillRect(5 + pr * prev[0],5 + pr * prev[1],pr-3,pr-3, ILI9341_BLUE); 
    tft.setCursor(5 + pr * prev[0], 5 + pr * prev[1]);
    tft.setTextColor(ILI9341_WHITE);
    if (board[prev[1]][prev[0]] != 0)
    tft.print(board[prev[1]][prev[0]]);
    }
  }
  delay(75);
  }
  

}



// loads the original array with the original numbers in the board so that the user cannot change them.
// This allows us to not only stop the user from changing them but to also identify them to make them 
// different colors then the ones the user inputs so that they can differentiate between them.
void loadOriginals(int board[][9], int original[]){
  for (int i = 0; i < 81; i++)
   if (board[i/9][i%9] != 0)
    original[i] = 1;   // now if we want to check if a square can be highlighted and changed we check if it is in this array. If it is then we cannot change it.
}

bool notOriginal(int board[][9], int original[], int x, int y){
  for (int i = 0; i < 81; i++){
  Serial.print(original[i]);}
  if (original[x*9 + y] == 0)
  return true;
  return false;
}
void loadNew(int board[][9], int newBoard[][9], int original[]){
  for (int i = 0; i < 81; i++)
    original[i] = 0;
  for (int i = 0; i < 81; i++){
    board[i/9][i%9] = newBoard[i/9][i%9];
    spareBoard[i/9][i%9] = newBoard[i/9][i%9];
    board2[i/9][i%9] = newBoard[i/9][i%9];
    original[i] = newBoard[i/9][i%9];
  }
}

void randomBoard(int board[][9], int original[]){
  
  int boardA1[9][9] = { // board 1               
  {0, 0, 0, 0, 0, 3, 1, 0, 5},
  {2, 0, 0, 5, 0, 1, 6, 4, 0},
  {0, 5, 0, 4, 0, 0, 9, 0, 0},
  {0, 0, 1, 0, 5, 0, 0, 9, 0},
  {0, 3, 0, 0, 6, 0, 0, 2, 0},
  {0, 7, 0, 0, 3, 0, 5, 0, 0},
  {0, 0, 2, 0, 0, 5, 0, 1, 0},
  {0, 9, 5, 3, 0, 2, 0, 0, 6},
  {4, 0, 7, 9, 0, 0, 0, 0, 0}};
int boardA2[9][9] = {  // board 2            
  {0, 9, 0, 0, 6, 0, 3, 2, 0},
  {0, 7, 0, 0, 3, 0, 0, 0, 0},
  {0, 0, 0, 8, 0, 5, 9, 0, 0},
  {6, 0, 0, 0, 5, 8, 2, 0, 0},
  {7, 3, 0, 0, 2, 0, 0, 4, 9},
  {0, 0, 2, 7, 9, 0, 0, 0, 8},
  {0, 0, 1, 3, 0, 9, 0, 0, 0},
  {0, 0, 0, 0, 8, 0, 0, 3, 0},
  {0, 2, 7, 0, 1, 0, 0, 9, 0}};
int boardA3[9][9] = {// board 3                
  {0, 0, 0, 7, 0, 9, 0, 0, 1},
  {9, 0, 0, 0, 0, 8, 2, 0, 0},
  {7, 0, 0, 3, 1, 0, 0, 0, 0},
  {5, 0, 8, 0, 2, 0, 0, 3, 7},
  {0, 0, 1, 0, 0, 0, 5, 0, 0},
  {2, 7, 0, 0, 3, 0, 8, 0, 6},
  {0, 0, 0, 0, 8, 3, 0, 0, 5},
  {0, 0, 5, 2, 0, 0, 0, 0, 3},
  {4, 0, 0, 6, 0, 7, 0, 0, 0}};
int boardA4[9][9] = {// board 4            
  {4, 0, 0, 2, 9, 0, 0, 0, 3},
  {0, 0, 6, 0, 0, 5, 0, 0, 0},
  {5, 0, 0, 8, 0, 4, 0, 0, 0},
  {0, 0, 0, 9, 0, 0, 8, 0, 2},
  {0, 9, 1, 6, 0, 7, 3, 5, 0},
  {3, 0, 2, 0, 0, 8, 0, 0, 0},
  {0, 0, 0, 5, 0, 2, 0, 0, 6},
  {0, 0, 7, 0, 1, 0, 0, 0, 0},
  {6, 0, 0, 0, 7, 9, 0, 0, 5}};
int boardA5[9][9] = {// board 5              
  {5, 0, 0, 0, 0, 0, 0, 6, 0},
  {0, 0, 0, 0, 0, 3, 2, 0, 9},
  {0, 0, 3, 6, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 9, 0},
  {3, 0, 0, 0, 2, 7, 5, 0, 0},
  {0, 5, 0, 0, 0, 0, 0, 1, 6},
  {0, 0, 7, 8, 0, 9, 0, 0, 0},
  {0, 1, 0, 0, 0, 6, 9, 0, 0},
  {0, 4, 6, 7, 0, 5, 0, 0, 0}};
int boardA6[9][9] = {//board 6            
  {6, 0, 0, 0, 0, 0, 0, 0, 9},
  {7, 0, 0, 0, 3, 0, 6, 8, 0},
  {3, 8, 0, 0, 9, 0, 0, 5, 0},
  {0, 0, 0, 3, 8, 2, 0, 0, 0},
  {0, 0, 0, 4, 0, 9, 7, 2, 3},
  {2, 9, 0, 7, 6, 0, 0, 0, 1},
  {8, 7, 2, 0, 0, 0, 1, 0, 5},
  {0, 0, 6, 0, 5, 0, 0, 0, 0},
  {0, 0, 4, 2, 0, 0, 0, 3, 0}};
int boardA7[9][9] = {//board 7
  {9, 0, 0, 8, 0, 0, 0, 4, 0},
  {0, 0, 5, 0, 0, 1, 0, 0, 0},
  {0, 1, 0, 3, 0, 4, 0, 6, 0},
  {0, 7, 0, 0, 0, 0, 6, 5, 3},
  {6, 0, 1, 0, 0, 0, 2, 0, 4},
  {2, 4, 3, 0, 0, 0, 0, 9, 0},
  {0, 6, 0, 1, 0, 5, 0, 7, 0},
  {0, 0, 0, 2, 0, 0, 5, 0, 0},
  {0, 9, 0, 0, 0, 6, 0, 0, 2}};
int boardA8[9][9] = {// board 8
  {0, 0, 2, 0, 0, 0, 0, 5, 0},
  {6, 0, 3, 0, 9, 1, 0, 0, 0},
  {0, 9, 0, 4, 0, 0, 0, 0, 0},
  {0, 0, 7, 0, 0, 0, 0, 0, 0},
  {0, 8, 0, 0, 3, 6, 4, 0, 0},
  {0, 0, 5, 0, 2, 4, 0, 0, 1},
  {0, 0, 0, 6, 1, 5, 0, 0, 8},
  {0, 0, 0, 0, 7, 0, 0, 2, 9},
  {0, 0, 0, 0, 0, 0, 0, 0, 0}};
int boardA9[9][9] = {// board 9
   {3, 0, 6, 5, 0, 8, 4, 0, 0},
   {5, 2, 0, 0, 0, 0, 0, 0, 0},  
   {0, 8, 7, 0, 0, 0, 0, 3, 1},
   {0, 0, 3, 0, 1, 0, 0, 8, 0},
   {9, 0, 0, 8, 6, 3, 0, 0, 5},
   {0, 5, 0, 0, 9, 0, 6, 0, 0},
   {1, 3, 0, 0, 0, 0, 2, 5, 0},
   {0, 0, 0, 0, 0, 0, 0, 7, 4},
   {0, 0, 5, 2, 0, 6, 3, 0, 0}};

  //transform board into one of the boards given

  int boardNumber = random(0, 9);
  Serial.println(boardNumber);
  if (boardNumber == 0)
    loadNew(board, boardA1, original);
  else if (boardNumber == 1)
    loadNew(board, boardA2, original);
  else if (boardNumber == 2)
    loadNew(board, boardA3, original);
  else if (boardNumber == 3)
    loadNew(board, boardA4, original);
  else if (boardNumber == 4)
    loadNew(board, boardA5, original);
  else if (boardNumber == 5)
    loadNew(board, boardA6, original);
  else if (boardNumber == 6)
    loadNew(board, boardA7, original);
  else if (boardNumber == 7)
    loadNew(board, boardA8, original);
  else if (boardNumber == 8)
    loadNew(board, boardA9, original);

  

  }
