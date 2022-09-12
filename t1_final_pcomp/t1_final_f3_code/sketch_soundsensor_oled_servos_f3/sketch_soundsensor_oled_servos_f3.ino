#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1
Adafruit_SH1106 display(OLED_RESET);

//include the Servo library
#include <Servo.h>
// Declare the Servo pin
int servoPin1 = 3;
int servoPin2 = 4;
Servo servo1, servo2;

//Define hardware connections
#define PIN_GATE_IN 2
#define IRQ_GATE_IN  0
#define PIN_LED_OUT 13
#define PIN_ANALOG_IN A0

//soundISR()
//This function is installed as an interrupt service routine for the pin
//change interrupt.  When digital input 2 changes state, this routine
//is called.
//It queries the state of that pin, and sets the onboard LED to reflect that
//pin's state.
void soundISR()
{
int pin_val;

pin_val = digitalRead(PIN_GATE_IN);
digitalWrite(PIN_LED_OUT, pin_val);
}

void setup()
{
Serial.begin(9600);
//Configure LED pin as output
pinMode(PIN_LED_OUT, OUTPUT);
//set servos pins
servo1.attach(servoPin1);
servo2.attach(servoPin2);
pinMode(A0, INPUT);
//configure input to interrupt
pinMode(PIN_GATE_IN, INPUT);
attachInterrupt(IRQ_GATE_IN, soundISR, CHANGE);
display.begin(SH1106_SWITCHCAPVCC, 0x3C);
display.clearDisplay();
// Display status
Serial.println("Initialized");
}

void loop()
{
int value;

// Check the envelope input
value = analogRead(PIN_ANALOG_IN);

// Convert envelope value into a message
Serial.print("Status: ");
if (value <= 30){
Serial.println("Quiet.");
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(1, 20);
display.print("Nice to meet you! :)");
display.display();
}
else if (value > 30){
Serial.println("Loud.");
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(1, 20);
display.print("That is really mean! :(");
display.display();
int j = 0;
for (j = 0; j <= 180; j ++) { // goes from 0 degrees to 180 degrees
// in steps of 1 degree
servo1.write(j);
servo2.write(j);  // tell servo to go to position in variable 'j'
delay(15);                       // waits 15ms for the servo to reach the position
}
for (j = 180; j >= 0; j -= 1) { // goes from 180 degrees to 0 degrees
servo1.write(j);
servo2.write(j);              // tell servo to go to position in variable 'j'
delay(15);                       // waits 15ms for the servo to reach the position
}
//  servo1.write(0);
//  servo2.write(0);
//  //delay(2000);
//  servo1.write(90);
//  servo2.write(90);
//  //delay(2000);
//  //delay(1000);
//  servo1.write(180);
//  servo2.write(180);
//  //delay(2000);
//  servo1.write(90);
//  servo2.write(90);
//  //delay(2000);
//  servo1.write(0);
//  servo2.write(0);
}

// pause for 0.1 second
delay(100);
}
