#include <SevenSeg.h>

#define RESET_PIN 2
#define SENSOR_PIN 3
SevenSeg Display(10,1,6,7,8,9,5);
#define DIGITS_NUM 3
int digitPins[DIGITS_NUM]={11,4,0};
int count = 0;

void setup() {
  display_Init(&Display);

  pinMode(RESET_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(RESET_PIN), RESET_Handler, FALLING);
  
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), SENSOR_Handler, FALLING);
}
void SENSOR_Handler(){
  count++;  
}
void RESET_Handler(){
  count = 0;  
}
ISR(TIMER2_COMPA_vect){
  Display.interruptAction();
}
void display_Init(SevenSeg *display){
  display->setCommonAnode();                    // Set display with common anode
  display->setDigitPins(DIGITS_NUM,digitPins);  // Set digits pins
  display->setTimer(2);                         // Set Timera 2
  display->startTimer();                        // Start Timer 2
}
void loop(){
  Display.write(count);
}