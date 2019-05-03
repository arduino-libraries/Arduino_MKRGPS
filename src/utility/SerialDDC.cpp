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

#include "SerialDDC.h"

SerialDDC::SerialDDC(TwoWire& wire, int address, uint8_t availableRegister, uint8_t readRegister) :
  _wire(&wire),
  _address(address),
  _availableRegister(availableRegister),
  _readRegister(readRegister)
{
}

SerialDDC::~SerialDDC()
{
}

int SerialDDC::begin(uint32_t clockFrequency)
{
  _wire->begin();
  _wire->setClock(clockFrequency);

  _wire->beginTransmission(_address);
  if (_wire->endTransmission() != 0) {
    // failure
    end();

    return 0;
  }

  return 1;
}

void SerialDDC::end()
{
  _wire->end();
}

int SerialDDC::available()
{
  int avail = _wire->available();

  if (avail) {
    return avail;
  }

  _wire->beginTransmission(_address);
  _wire->write(_availableRegister);
  if (_wire->endTransmission(false) != 0) {
    return 0;
  }

  if (_wire->requestFrom(_address, 2) != 2) {
    return 0;
  }

  uint8_t availableHigh = _wire->read();
  uint8_t availableLow  = _wire->read();

  if (availableHigh == 0xff && availableLow == 0xff) {
    return 0;
  }

  avail = (availableHigh << 8) | availableLow;

  if (avail > 255) {
    avail = 255;
  }

  _wire->beginTransmission(_address);
  _wire->write(_readRegister);
  if (_wire->endTransmission(false) != 0) {
    return 0;
  }

  if (_wire->requestFrom(_address, avail) != avail) {
    return 0;
  }

  return _wire->available();
}

int SerialDDC::read()
{
  return _wire->read();
}

int SerialDDC::peek()
{
  return _wire->peek();
}

size_t SerialDDC::write(uint8_t b)
{
  return write(&b, sizeof(b));
}

size_t SerialDDC::write(const uint8_t *buffer, size_t size)
{
  if (size < 2) {
    return 0;
  }

  int result;

  _wire->beginTransmission(_address);
  result = _wire->write(buffer, size);
  if (_wire->endTransmission() != 0) {
    return 0;
  }

  return result;
}

void SerialDDC::flush()
{
  // no-op
}