/*
  This file is part of the Arduino_MKRGPS library.
  Copyright (c) 2019 Arduino SA. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _GPS_H_
#define _GPS_H_

#include <Arduino.h>

#include "utility/SerialDDC.h"

enum
{
  GPS_MODE_UART,
  GPS_MODE_I2C,
  GPS_MODE_SHIELD = GPS_MODE_UART
};

class GPSClass {
public:
  GPSClass(HardwareSerial& serial, unsigned long baudrate, SerialDDC& serialDDC, unsigned long clockrate, int extintPin);
  virtual ~GPSClass();

  int begin(int mode = GPS_MODE_I2C);
  void end();

  int available();

  float latitude();
  float longitude();
  float speed(); // Speed over the ground in kph
  float course(); // Track angle in degrees
  float variation(); // Magnetic Variation
  float altitude();
  int satellites();

  unsigned long getTime();

  void standby();
  void wakeup();

private:
  void poll();
  void parseBuffer();
  void sendUbx(uint8_t cls, uint8_t id, uint8_t payload[], uint16_t length);

  static float toDegrees(float f);

private:
  HardwareSerial* _serial;
  unsigned long _baudrate;

  SerialDDC* _serialDDC;
  unsigned long _clockRate;

  int _extintPin;

  int _mode;
  Stream* _stream;

  int _available;
  char _buffer[82 + 1];
  int _index;

  float _latitude;
  float _longitude;
  float _speed;
  float _course;
  float _variation;
  float _altitude;
  int _satellites;

  struct timespec _ts;
};

extern GPSClass GPS;

#endif
