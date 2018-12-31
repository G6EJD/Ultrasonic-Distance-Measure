/*   Software serial multple serial test */
#define rxPin 255       // Not used, so set to invalid pin #
#define txPin 1         // Connect BPI/BPK's SER input to this pin.
#define inverted 1      // In setup, 1=inverted, 0=noninverted
#define trigPin 7       // Connect Trig on the module to pin 7 on the Arduino
#define echoPin 6       // Connect Echo on the module to pin 6 on the Arduino

#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 8, false); // RX, TX, inverted

void setup()
{
  // Open serial communications and wait for port to open:
  pinMode(trigPin, OUTPUT);    // Set the trigPin to output
  digitalWrite(trigPin, LOW);  // Set trigPin low to start
  pinMode(echoPin, INPUT);     // Set echoPin as an input
  Serial.begin(2400, SERIAL_8N2);
  clear_screen();
  Serial.write(254); Serial.write(192);
  Serial.print("Arduino Uno");
  Serial.write(254); Serial.write(148);
  Serial.print("ultrasonic distance");
  Serial.write(254); Serial.write(212);
  Serial.print("measuring in (cm)");
  delay(400);
  clear_screen;
}

void loop() // run over and over
{
  delay(300);
  measure();
}

void clear_screen() {
  Serial.write(254);
  Serial.write(1);
  delay(400);
}

void home_cursor() {
  Serial.write(254);
  Serial.write(128);
}

void measure()
{
  float distance = 0;
  digitalWrite(trigPin, HIGH);       // Set the trigPin high, to start the measurement
  delayMicroseconds(10);             // Wait 10 uS
  digitalWrite(trigPin, LOW);        // Set the trigPin low, module will send a pulse
  distance = pulseIn(echoPin, HIGH); // Read the pulse length from the module
  distance = distance / 59;
  home_cursor();
  Serial.print(distance, 1);
  Serial.print(" cm  ");             // Send the distance to the serial port / screen
}

/* LCD Commands
  254,1 Clear Display (must be followed by a ‘pause 30’ command)
  254,8 Hide Display
  254,12 Restore Display
  254,14 Turn on Cursor
  254,16 Move Cursor Left
  254,20 Move Cursor Right
  254,128 Move to line 1, position 1
  254,192 Move to line 1, position x (where y = 128 + x)
  254,148 Move to line 2, position 1
  254,212 Move to line 2, position x (where y = 192 + x)
*/
