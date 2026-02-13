#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <ctime>

#include "log.h"
#include "HardwareSerial.h"
#include "hal/uart_ll.h"

HardwareSerial::HardwareSerial(uart_port_t uart_nr)
  : _uart_nr(uart_nr), _has_peek(false), _peek_byte(0)
{
}

HardwareSerial::~HardwareSerial() {
}

int HardwareSerial::available(void) {
  size_t available;
  uart_get_buffered_data_len(_uart_nr, &available);
  if (_has_peek) {
    available++;
  }
  return available;
}
int HardwareSerial::availableForWrite(void) {
  uint32_t available = uart_ll_get_txfifo_len(UART_LL_GET_HW(_uart_nr));
  size_t txRingBufferAvailable = 0;
  if (ESP_OK == uart_get_tx_buffer_free_size(_uart_nr, &txRingBufferAvailable)) {
    available = txRingBufferAvailable == 0 ? available : txRingBufferAvailable;
  }
  return available;
}

int HardwareSerial::peek(void) {
  uint8_t c = 0;
  if (_has_peek) {
    c = _peek_byte;
  } else {
    int len = uart_read_bytes(_uart_nr, &c, 1, 20 / portTICK_PERIOD_MS);
    if (len <= 0) {  // includes negative return from IDF in case of error
      c = 0;
    } else {
      _has_peek = true;
      _peek_byte = c;
    }
  }
  return c;
}

int HardwareSerial::read(void) {
  uint8_t c = 0;
  if (uartReadBytes(&c, 1, 0) == 1) {
    return c;
  } else {
    return -1;
  }
}

// read characters into buffer
// terminates if size characters have been read, or no further are pending
// returns the number of characters placed in the buffer
// the buffer is NOT null terminated.
size_t HardwareSerial::read(uint8_t *buffer, size_t size) {
  return uartReadBytes(buffer, size, 0);
}

// Overrides Stream::readBytes() to be faster using IDF
size_t HardwareSerial::readBytes(uint8_t *buffer, size_t length) {
  return uartReadBytes(buffer, length, (uint32_t)getTimeout());
}

void HardwareSerial::flush(void) {
  flush(true);
}

void HardwareSerial::flush(bool txOnly) {
  while (!uart_ll_is_tx_idle(UART_LL_GET_HW(_uart_nr)));

  if (!txOnly) {
    ESP_ERROR_CHECK(uart_flush_input(_uart_nr));
  }
}

size_t HardwareSerial::write(uint8_t c) {
  uart_write_bytes(_uart_nr, &c, 1); // TODO proper return
  return 1;
}

size_t HardwareSerial::write(const uint8_t *buffer, size_t size) {
  if (buffer != NULL && size != 0) { // TODO proper return
    uart_write_bytes(_uart_nr, buffer, size);
  }

  return size;
}

size_t HardwareSerial::uartReadBytes(uint8_t *buffer, size_t size, uint32_t timeout_ms) {
  if (size == 0 || buffer == NULL) {
    return 0;
  }

  size_t bytes_read = 0;

  if (_has_peek) {
    _has_peek = false;
    *buffer++ = _peek_byte;
    size--;
    bytes_read = 1;
  }

  if (size > 0) {
    int len = uart_read_bytes(_uart_nr, buffer, size, pdMS_TO_TICKS(timeout_ms));
    if (len < 0) {
      len = 0;  // error reading UART
    }
    bytes_read += len;
  }

  return bytes_read;
}
