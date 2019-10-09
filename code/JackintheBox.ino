/*
  Runs a Jack in the Box
  Plays UFO theme
*/

#include "pitches.h"
#include <Servo.h> 

#define servoPin  10
#define switchPin 2

#define closePos  10
#define openPos   70

Servo servo;
int switchState;
int previousSwitchState;
int playCount = 0;

// Creepy sci-fi tune
int melody[] = {NOTE_AS6,NOTE_B6,NOTE_D6,0};
int noteDurations[] = {10,10,10};

void ToggleSwitch(int switchState)
{    
  if (switchState == HIGH) // If switch is pushed, open the box
  {
    servo.write(openPos);
  }
  else
  {
    servo.write(closePos);
  }
  previousSwitchState = switchState;  // Remember that the switch state has changed 
}

void setup() {

  pinMode(5,OUTPUT);
  digitalWrite(5,HIGH);
  
  // Start with the box closed and the switch in the off postion
  switchState = LOW;
  previousSwitchState = LOW;

  // Connect to our servo and make sure it is in the closed position
  servo.attach(servoPin);
  servo.write(closePos);

  pinMode(switchPin, INPUT); 
}

void loop() {
  int switchState = digitalRead(switchPin);
  
  if (switchState != previousSwitchState) {
    ToggleSwitch(switchState);

    // Only want to play audio once and not loop through continuously
    if (playCount == 0) {
      for (int thisNote = 0; thisNote < 3; thisNote++) {
        
        int noteDuration = 9000 / noteDurations[thisNote];
        tone(8, melody[thisNote], noteDuration);

        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
      
        // Stop the tone playing:
        noTone(8);
        playCount += 1;
      }
      
    ToggleSwitch(switchState);
    }
  }
  delay(20);
}
