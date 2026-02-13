/*
 HardwareSerial.h - Hardware serial library for Wiring
 Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

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
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

 Modified 28 September 2010 by Mark Sproul
 Modified 14 August 2012 by Alarus
 Modified 3 December 2013 by Matthijs Kooijman
 Modified 18 December 2014 by Ivan Grokhotkov (esp8266 platform support)
 Modified 31 March 2015 by Markus Sattler (rewrite the code for UART0 + UART1 support in ESP8266)
 Modified 25 April 2015 by Thomas Flayols (add configuration different from 8N1 in ESP8266)
 Modified 13 October 2018 by Jeroen Döll (add baudrate detection)
 Baudrate detection example usage (detection on Serial1):
   void setup() {
     Serial.begin(115200);
     delay(100);
     Serial.println();

     Serial1.begin(0, SERIAL_8N1, -1, -1, true, 11000UL);  // Passing 0 for baudrate to detect it, the last parameter is a timeout in ms

     unsigned long detectedBaudRate = Serial1.baudRate();
     if(detectedBaudRate) {
       Serial.printf("Detected baudrate is %lu\n", detectedBaudRate);
     } else {
       Serial.println("No baudrate detected, Serial1 will not work!");
     }
   }

 Pay attention: the baudrate returned by baudRate() may be rounded, eg 115200 returns 115201
 */

#ifndef HardwareSerial_h
#define HardwareSerial_h

#include <inttypes.h>
#include "Stream.h"
#include "driver/uart.h"

class HardwareSerial : public Stream {
private:
    size_t uartReadBytes(uint8_t *buffer, size_t size, uint32_t timeout_ms);

public:
  HardwareSerial(uart_port_t uart_nr);
  ~HardwareSerial();

  int available(void);
  int availableForWrite(void);
  int peek(void);
  int read(void);
  size_t read(uint8_t *buffer, size_t size);
  inline size_t read(char *buffer, size_t size) {
    return read((uint8_t *)buffer, size);
  }
  // Overrides Stream::readBytes() to be faster using IDF
  size_t readBytes(uint8_t *buffer, size_t length);
  size_t readBytes(char *buffer, size_t length) {
    return readBytes((uint8_t *)buffer, length);
  }
  void flush(void);
  void flush(bool txOnly);
  size_t write(uint8_t);
  size_t write(const uint8_t *buffer, size_t size);
  inline size_t write(const char *buffer, size_t size) {
    return write((uint8_t *)buffer, size);
  }
  inline size_t write(const char *s) {
    return write((uint8_t *)s, strlen(s));
  }
  inline size_t write(unsigned long n) {
    return write((uint8_t)n);
  }
  inline size_t write(long n) {
    return write((uint8_t)n);
  }
  inline size_t write(unsigned int n) {
    return write((uint8_t)n);
  }
  inline size_t write(int n) {
    return write((uint8_t)n);
  }
  operator bool() const;

protected:
  uart_port_t _uart_nr;
  bool _has_peek;
  uint8_t _peek_byte;
};

#endif  // HardwareSerial_h
