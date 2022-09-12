const int ledPin = 13;   //the number of the LED pin
const int ldrPin = A0;  //the number of the LDR pin

#include <SD.h>                      // need to include the SD library
//#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
#define SD_ChipSelectPin 2  //using digital pin 4 on arduino nano 328, can use other pins
#include <TMRpcm.h>           //  also need to include this library...
#include <SPI.h>
TMRpcm tmrpcm;

bool startPlaying = false;
bool isPlaying = false;

void setup() {

  Serial.begin(9600);
  tmrpcm.speakerPin = 9;
  pinMode(ledPin, OUTPUT);  //initialize the LED pin as an output
  pinMode(ldrPin, INPUT);   //initialize the LDR pin as an input

  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");
    return;   // don’t do anything more if not
  }
  //Serial.println(“File Playing”);
}

void loop() {

  int ldrStatus = analogRead(ldrPin);   //read the status of the LDR value

  //check if the LDR status is <= 300
  //if it is, the audio player will start palying

  if (ldrStatus > 300) {

    if (!isPlaying) {
      startPlaying = true;
    }
    //digitalWrite(ledPin, HIGH);               //turn LED on
    Serial.println("---------------");
    //delay(2000);
  }
  else if (ldrStatus <= 300) {
    //that means the ldr is dark
    if (isPlaying) {
      //digitalWrite(ledPin, LOW);          //turn LED off
      Serial.println("LDR is dark, start palying");
      tmrpcm.stopPlayback();
      isPlaying = false;
    }
  }
  if (startPlaying && !isPlaying) {
    //tmrpcm.play("1.wav"   //just for testing if the audio player workes
    int i;
    i = random(3);    //make it paly random songs
    if (i == 0) {
      tmrpcm.play("1.wav");
    }
    if (i == 1) {
      tmrpcm.play("2.wav");
    }
    if (i == 2) {
      tmrpcm.play("3.wav");
    }
    if (i == 3) {
      tmrpcm.play("4.wav");
    }       //list all possiblities
    startPlaying = false;
    isPlaying = true;
    delay(1000);

  }
}
