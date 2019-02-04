/*
  This file is part of the MKRGPS library.
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

class GPSClass {
public:
  GPSClass(HardwareSerial& serial, unsigned long baudrate, int extintPin);
  virtual ~GPSClass();

  int begin();
  void end();

  int available();

  float latitude();
  float longitude();
  float speed(); // Speed over the ground in knots
  float course(); // Track angle in degrees
  float variation(); // Magnetic Variation
  float altitude();
  int satellites();

  unsigned long getTime();

private:
  void poll();
  void parseBuffer();

  static float toDegrees(float f);

private:
  HardwareSerial* _serial;
  unsigned long _baudrate;
  int _extintPin;

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
