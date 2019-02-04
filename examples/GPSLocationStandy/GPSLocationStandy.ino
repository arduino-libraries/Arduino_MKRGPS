/*
  GPS Location Standy

  This sketch uses the GPS to determine the location of the board
  and prints it to the Serial monitor.

  It puts the GPS to in standby mode every 10 seconds, then wakes it up.

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
  Serial.println("standy");
  GPS.standby();

  Serial.print("delay ");
  for (int i = 0; i < 10; i++) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("wakeup");
  GPS.wakeup();

  Serial.print("wait location ... ");
  
  unsigned long startMillis = millis();
  while (!GPS.available());
  unsigned long endMillis = millis();

  Serial.print(endMillis - startMillis);
  Serial.println(" ms");

  Serial.println();
  Serial.print("Location: ");
  Serial.print(GPS.latitude(), 7);
  Serial.print(", ");
  Serial.println(GPS.longitude(), 7);

  Serial.print("Altitude: ");
  Serial.print(GPS.altitude());
  Serial.println("m");

  Serial.print("Number of satellites: ");
  Serial.println(GPS.satellites());

  Serial.println();

}
