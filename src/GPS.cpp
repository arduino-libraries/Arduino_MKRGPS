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

// Useful info. on NMEA data: https://www.gpsinformation.org/dale/nmea.htm

extern "C" {
  #include "minmea/minmea.h"
}

// #define GPS_DEBUG

#include "GPS.h"

#define GPS_MASK_RMC 0x01
#define GPS_MASK_GGA 0x02

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

  _available = 0;
  _index = 0;

  return 1;
}

void GPSClass::end()
{
  _serial->end();

  digitalWrite(_extintPin, LOW);
  pinMode(_extintPin, INPUT);
}

int GPSClass::available()
{
  poll();

  if (_available == (GPS_MASK_RMC | GPS_MASK_GGA)) {
    _available = 0x00;

    return 1;
  }

  return 0;
}

float GPSClass::latitude()
{
  if (isnan(_latitude)) {
    return NAN;
  }

  return toDegrees(_latitude);
}

float GPSClass::longitude()
{
  if (isnan(_longitude)) {
    return NAN;
  }

  return toDegrees(_longitude);
}

float GPSClass::speed()
{
  return _speed;
}

float GPSClass::course()
{
  return _course;
}

float GPSClass::variation()
{
  if (isnan(_variation)) {
    return NAN;
  }

  return toDegrees(_variation);
}

float GPSClass::altitude()
{
  return _altitude;
}

int GPSClass::satellites()
{
  return _satellites;
}

unsigned long GPSClass::getTime()
{
  return _ts.tv_sec;
}

void GPSClass::standby()
{
  byte payload[48];

  memset(payload, 0x00, sizeof(payload));

  payload[0] = 0x02; // version 2
  // flags:
  //       extintSel    = EXTINT0
  //       extintWake   = enabled, keep receiver awake as long as selected EXTINT pin is 'high'
  //       extintBackup = enabled, force receiver into BACKUP mode when selected EXTINT pin is 'low' 
  payload[4] = 0x60;

  sendUbx(0x06, 0x3b, payload, sizeof(payload));

  _serial->end();
  digitalWrite(_extintPin, LOW);

  _available = 0;
  _index = 0;
}

void GPSClass::wakeup()
{
  _serial->begin(_baudrate);

  digitalWrite(_extintPin, HIGH);

  _available = 0;
  _index = 0;
}

void GPSClass::poll()
{
  if (_serial->available()) {
    char c = _serial->read();

#ifdef GPS_DEBUG
    Serial.print(c);
#endif

    if (c == '$') {
      _index = 0;
    }

    if (_index < ((int)sizeof(_buffer) - 1)) {
      _buffer[_index++] = c;

      if (c == '\n' && _buffer[0] == '$') {
        _buffer[_index++] = '\0';

        parseBuffer();
      }
    }
  }
}

void GPSClass::parseBuffer()
{
  int sentenceId = minmea_sentence_id(_buffer, false);

  switch (sentenceId) {
    case MINMEA_SENTENCE_RMC: {
      struct minmea_sentence_rmc frame;
      
      if (minmea_parse_rmc(&frame, _buffer) && frame.valid) {
        _latitude = minmea_tofloat(&frame.latitude);
        _longitude = minmea_tofloat(&frame.longitude);
        _speed = minmea_tofloat(&frame.speed);
        _course = minmea_tofloat(&frame.course);
        _variation = minmea_tofloat(&frame.variation);

        minmea_gettime(&_ts, &frame.date, &frame.time);

        _available |= GPS_MASK_RMC;
      }

      break;
    }

    case MINMEA_SENTENCE_GGA: {
      struct minmea_sentence_gga frame;
      
      if (minmea_parse_gga(&frame, _buffer) && frame.fix_quality != 0) {
        _latitude = minmea_tofloat(&frame.latitude);
        _longitude = minmea_tofloat(&frame.longitude);
        _altitude = minmea_tofloat(&frame.altitude);
        _satellites = frame.satellites_tracked;

        _available |= GPS_MASK_GGA;
      }

      break;
    }

    default:
      break;
  }
}

void GPSClass::sendUbx(uint8_t cls, uint8_t id, uint8_t payload[], uint16_t length)
{
  uint8_t ckA = 0;
  uint8_t ckB = 0;
  uint8_t prefix[] = { cls, id, (uint8_t)(length & 0xff), (uint8_t)(length >> 8) };

  for (unsigned int i = 0; i < sizeof(prefix); i++) {
    ckA += prefix[i];
    ckB += ckA;
  }

  for (unsigned int i = 0; i < length; i++) {
    ckA += payload[i];
    ckB += ckA;
  }

  _serial->write(0xb5);
  _serial->write(0x62);
  _serial->write(cls);
  _serial->write(id);
  _serial->write((uint8_t*)&length, sizeof(length));
  _serial->write(payload, length);
  _serial->write(ckA);
  _serial->write(ckB);
  _serial->flush();
}

float GPSClass::toDegrees(float f)
{
  float degrees = (int)(f / 100.0);
  float minutes = f - (100.0 * degrees);

  return (degrees + (minutes / 60.0));
}

GPSClass GPS(Serial1, 9600, 7);