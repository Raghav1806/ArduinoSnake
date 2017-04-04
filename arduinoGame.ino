#include<LiquidCrystal.h>

// Allocating LCD Control Pins
const int RS = 12;
const int Enable = 11;
const int D4 = 5;
const int D5 = 4;
const int D6 = 3;
const int D7 = 2;
const int Backlight = 9;

// Setting LCD Size
const int lcdRows = 2;
const int lcdCols = 16;

// Declaring LCD variable, with defined pins
LiquidCrystal lcd(RS,Enable,D4,D5,D6,D7);

const int YES = 1;
const int NO = 0;

// Define maximum length of snake
int maxLength = 12;

// Set the time taken by snake to move
long timeToMove = 200;

void setup(){
  
// Setting pins as output
pinMode(RS,OUTPUT);
pinMode(Enable,OUTPUT);
pinMode(D4,OUTPUT);
pinMode(D5,OUTPUT);
pinMode(D6,OUTPUT);
pinMode(D7,OUTPUT);
pinMode(Backlight,OUTPUT);

// Turning on the Back Light
digitalWrite(Backlight,HIGH);

}

void loop(){

// initialize LCD
int extend = NO;
lcd.begin(lcdRows,lcdCols);

// Define Snake Custom Character Numbers
const int Tail = 4;       // Tail is Custom Character 0
const int Head = 1;       // Head is Custom Character 1
const int Clear = 2;      // Custom Character 2 is used for Clear Space
const int Apple = 3;

// Defining Snake Character BitMaps
byte snakeHead[8]={
B10001,
B01010,
B11111,
B10101,
B11111,
B10101,
B10001,
B01110,
};

byte snakeTail[8]={
B00100,
B01110,
B01110,
B11011,
B11011,
B01110,
B01110,
B00100
};

byte noSnake[8]={
B00000,
B00000,
B00000,
B00000,
B00000,
B00000,
B00000,
B00000
};

byte apple[8]={
B00000,
B00000,
B00010,
B00100,
B01110,
B11011,
B11110,
B01100
};

// Create custom characters
lcd.createChar(Head,snakeHead);
lcd.createChar(Tail,snakeTail);
lcd.createChar(Clear,noSnake);
lcd.createChar(Apple,apple);

// Define arrays for LCD data - Columns by Rows
int lcdOutput [lcdCols][lcdRows];                 // Holds LCD output
int oldLcdOutput [lcdCols][lcdRows];              // Holds previous LCD Output

// Display Title Screen
lcd.setCursor(6,0);
lcd.print("SNAKE!");
delay(1000);

lcd.setCursor(7,1);
lcd.print("By RAGHAV");
delay(2000);

lcd.setCursor(2,0);
lcd.write(Head);
delay(500);

lcd.setCursor(1,0);
lcd.write(Tail);
delay(500);

lcd.setCursor(0,0);
lcd.write(Tail);
delay(5000);

// Set snake start position
for(int row=0;row<lcdRows;row++){               // Clearing the output LCD Array
  for(int col=0;col<lcdCols;col++){
    lcdOutput[col][row]=Clear;
  }
}

// Put the snake in Ist 3 positions on Row 0
lcdOutput[0][0] = Tail;
lcdOutput[1][0] = Tail;
lcdOutput[2][0] = Head;

int currentLength = 3;                          // Set current snake length
unsigned long previousMillis = 0;               // Will store last time the snake moved

while(1){                                       // Repeat this part forever!
  for(int row=0;row<lcdRows;row++){
    for(int col=0;col<lcdCols;col++){           // Render the output on LCD
      lcd.setCursor(col,row);                   
      lcd.write(lcdOutput[col][row]);
    }
  }
    
unsigned long currentMillis = millis();         // get current time

if(currentMillis - previousMillis > timeToMove){
  previousMillis = currentMillis;
  for(int oldrow = 0;oldrow < lcdRows;oldrow++){
     for(int oldcol = 0;oldcol < lcdCols; oldcol++){
         oldLcdOutput[oldcol][oldrow] = lcdOutput[oldcol][oldrow];
     }
  }
  
// Work out with snake's next position
for(int row = 0;row<lcdRows;row++){
    if(row == 0){
       for(int col = 1; col < lcdCols; col++){
          lcdOutput[col][0] = oldLcdOutput[col-1][0];
        }
       lcdOutput[0][row] = oldLcdOutput[0][row+1];
    }
    if(row > 0 && row < lcdRows-1){
        lcdOutput[0][row] = oldLcdOutput[0][row+1];
        lcdOutput[15][row] = oldLcdOutput[15][row-1];
    }
    if(row == lcdRows-1){
       for(int col = 0; col < 15; col++){
           if(oldLcdOutput[col][row] == Apple && oldLcdOutput[col+1][row] == Head && currentLength <= maxLength){
            extend = YES;
            lcd.setCursor(0,0);
            lcd.print("Yum, Yum!!!");
            delay(1000);
           }

          if(oldLcdOutput[col+1][row] != Apple){
             if(oldLcdOutput[col][row] != Apple){
                lcdOutput[col][row] = oldLcdOutput[col+1][row];
                  if(extend == YES && lcdOutput[col][row] == Clear && lcdOutput[col-1][row] == Tail && col != 0){
                     lcdOutput[col][row] = Tail;
                     currentLength++;
                     extend = NO;
                     }
                }
            if(oldLcdOutput[col+1][row] == Head){
              lcdOutput[col][row] = oldLcdOutput[col+1][row];
              }
          }
           
          if(oldLcdOutput[col][row] == Apple){
            lcdOutput[col-1][row] = Clear;
            }
            
      }
          
      lcdOutput[15][row] = oldLcdOutput[15][row-1];
    }
}

if(lcdOutput[0][0] == Head){
   int randomCol = random(3,13);
   if(lcdOutput[randomCol][lcdRows-1] == Clear){
      lcdOutput[randomCol][lcdRows-1] = Apple;
   }
}
      
}
}
}
