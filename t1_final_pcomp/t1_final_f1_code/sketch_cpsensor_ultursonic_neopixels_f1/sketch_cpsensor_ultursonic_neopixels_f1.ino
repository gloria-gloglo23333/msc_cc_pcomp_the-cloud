#include <Adafruit_NeoPixel.h>
#define LEDPIN 2 // connect the Data from the strip to this pin on the Arduino
#define NUMBER_PIEXELS 15// the number of pixels in your LED strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIEXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

#include <CapacitiveSensor.h>

const int ledPin = 8;
const int trigPin = 9;
const int echoPin = 10;

long duration;
int distance;
int safetyDistance;

int i = 0;

CapacitiveSensor   cs_7_3 = CapacitiveSensor(7, 3);       // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_7_4 = CapacitiveSensor(7, 4);       // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
CapacitiveSensor   cs_7_5 = CapacitiveSensor(7, 5);       // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil
CapacitiveSensor   cs_7_6 = CapacitiveSensor(7, 6);

void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(ledPin, OUTPUT);

  strip.begin();
  // Display status
  Serial.println("Initialized");
  cs_7_3.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  Serial.begin(9600);

}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  //distance = abs (duration * 0.034) / 2;
  distance = abs(duration / 2) / 29.1;

  safetyDistance = distance;

  long start = millis();
  long total1 =  cs_7_3.capacitiveSensor(30);
  long total2 =  cs_7_4.capacitiveSensor(30);
  long total3 =  cs_7_5.capacitiveSensor(30);
  long total4 =  cs_7_6.capacitiveSensor(30);

  Serial.print(millis() - start);        // check on performance in milliseconds
  Serial.print("\t");                    // tab character for debug windown spacing
  Serial.print(total1);                  // print sensor output 1
  Serial.print("\t");
  Serial.print(total2);                  // print sensor output 2
  Serial.print("\t");
  Serial.print(total3);                  // print sensor output 1
  Serial.print("\t");
  Serial.println(total4);

  if (safetyDistance <= 500 && (total1 < 300 || total2 < 300 || total3 < 300 ||total4 < 300 )) {

    for (int i = 0; i < strip.numPixels(); i++) {
      // starting at i, draw the orange color cloud}
      void orange(uint16_t i, uint16_t wait) ;
      strip.setPixelColor(i, 200, 70, 0); // orange
      strip.show();
    }
    //delay(200);
    //strip.clear();
    //strip.show();}
    digitalWrite(ledPin, HIGH);

    delay(100);

  }
  else if (safetyDistance <= 500 && (total1 >= 300 || total2 >= 300 || total3 >= 300 || total4 >= 300 )) {
    for (int i = 0; i < strip.numPixels(); i++) {
      void blue(uint16_t i, uint16_t wait) ;
      strip.setPixelColor(i , 50, 0, 150); // blue
      strip.show();
    }
    digitalWrite(ledPin, LOW);

    delay(100);
  }

  else if (safetyDistance > 500) {
    for (int i = 0; i < strip.numPixels() - 1; i++) {
      void off(uint16_t i, uint16_t wait) ;
      strip.setPixelColor(i , 0, 0, 0); // off
      strip.clear();
      strip.show();
      digitalWrite(ledPin, HIGH);
      delay(100);
    }

    Serial.print("Distance: ");
    Serial.println(safetyDistance);
  }
}
