/*
  GPS Location

  This sketch uses the GPS to determine the location of the board
  and prints it to the Serial monitor.

  Circuit:
   - MKR board
   - MKR GPS shield attached

  This example code is in the public domain.
*/

#include <MKRGPS.h>

void setup() {
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  if (!GPS.begin()) {
    Serial.println("Failed to initialize GPS!");
    while (1);
  }
}

void loop() {
  if (GPS.available()) {
    Serial.print("Location: ");
    Serial.print(GPS.latitude(), 7);
    Serial.print(", ");
    Serial.println(GPS.longitude(), 7);

    Serial.print("Altitude: ");
    Serial.print(GPS.altitude());
    Serial.println("m");

    Serial.print("Ground speed: ");
    Serial.print(GPS.speed());
    Serial.println(" knots");

    Serial.print("Number of satellites: ");
    Serial.println(GPS.satellites());

    Serial.println();
  }
}
