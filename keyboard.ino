#include <Keyboard.h>

byte inputs[] = {2,3,4}; //declaring inputs
byte outputs[] = {5,6,7,8};
int spam = 400; //spam speed
int longPress = 700; //delay
const int incount = 3;
const int outcount = 4;

char layout[4][3] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7','8','9'},
  {'0', 0xB0, 0xB2},
};
int keyDown[4][3];
int keyLong[4][3];

void setup() {
 for(int i = 0; i < outcount; i++)
 {
  pinMode(outputs[i], OUTPUT);
  digitalWrite(outputs[i], HIGH);
 }
 for(int i = 0; i < incount; i++)
 {
  pinMode(inputs[i], INPUT_PULLUP);
 }
 Serial.begin(9600);
 Serial.println("Connected");
 Keyboard.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(outputs[i], LOW);
    delayMicroseconds(5);

    for (int j = 0; j < 3; j++)
      {
      if(digitalRead(inputs[j]) == LOW)
      {
        keyPressed(i,j);
      }
      else if(keyDown[i][j] != 0)
      {
        resetKey(i,j);
      }
      }
    digitalWrite(outputs[i], HIGH);
    delayMicroseconds(500);
  }

}

void keyPressed(int row, int col)
{
  Serial.print("Output: ");
  Serial.print(row);
  Serial.print("Input: ");
  Serial.print(col);
  Serial.println(layout[row][col]);

  if(keyDown[row][col] == 0)
  {
    Keyboard.write(layout[row][col]);
  }
  else if(keyLong[row][col] && keyDown[row][col] > spam)
  {
    Keyboard.write(layout[row][col]);
    keyDown[row][col] = 1;
  }
  else if(keyDown[row][col] > longPress)
  {
    keyLong[row][col] = true;
  }
  keyDown[row][col]++;
}

void resetKey(int row, int col)
{
  keyDown[row][col] = 0;
  keyLong[row][col] = false;
}