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

#ifndef _SERIAL_DDC_H_
#define _SERIAL_DDC_H_

#include <Arduino.h>

#include <Wire.h>

class SerialDDC : public Stream {
public:
  SerialDDC(TwoWire& wire, int address, uint8_t availableRegister, uint8_t readRegister);
  virtual ~SerialDDC();

  int begin(uint32_t clockFrequency);
  void end();

  // from Stream
  virtual int available();
  virtual int read();
  virtual int peek();

  // from Print
  virtual size_t write(uint8_t);
  virtual size_t write(const uint8_t *buffer, size_t size);
  virtual void flush();

private:
  TwoWire* _wire;
  int _address;
  uint8_t _availableRegister;
  uint8_t _readRegister;
};

#endif
