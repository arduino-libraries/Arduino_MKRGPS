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

#include "GPS.h"


GPSClass::GPSClass(HardwareSerial& serial, unsigned long baudrate, int extintPin) :
  _serial(&serial),
  _baudrate(baudrate),
  _extintPin(extintPin)
{
}

GPSClass::~GPSClass()
{
}

int GPSClass::begin()
{
  pinMode(_extintPin, OUTPUT);
  digitalWrite(_extintPin, HIGH);

  _serial->begin(_baudrate);

  return 1;
}

void GPSClass::end()
{
  _serial->end();

  digitalWrite(_extintPin, LOW);
  pinMode(_extintPin, INPUT);
}

GPSClass GPS(Serial1, 9600, 7);