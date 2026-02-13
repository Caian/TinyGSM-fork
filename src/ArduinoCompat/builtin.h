#pragma once

#if !defined(ARDUINO) && !defined(ARDUINO_DASH) && defined(ESP_PLATFORM)

#include <cstdint>

using byte = uint8_t;

#define INPUT 1
#define OUTPUT 0

#if !defined(TINY_GSM_DELAY)
#define TINY_GSM_DELAY tgsm_delay
#endif

#if !defined(TINY_GSM_MILLIS)
#define TINY_GSM_MILLIS tgsm_millis
#endif

#if !defined(TINY_GSM_ISDIGIT)
#define TINY_GSM_ISDIGIT tgsm_isdigit
#endif

#if !defined(TINY_GSM_CONSTRAIN)
#define TINY_GSM_CONSTRAIN tgsm_constrain
#endif

#ifndef TINY_GSM_YIELD
#define TINY_GSM_YIELD tgsm_yield
void tgsm_yield();
#endif

#define delay TINY_GSM_DELAY
#define millis TINY_GSM_MILLIS
#define isDigit TINY_GSM_ISDIGIT
#define constrain TINY_GSM_CONSTRAIN
#define _BV(bit) (1 << (bit))

void TINY_GSM_DELAY(unsigned long);
unsigned long TINY_GSM_MILLIS();
bool tgsm_isdigit(char);

auto tgsm_constrain(const auto& x, const auto& a , const auto& b) {
    return x <= a ? a : (x >= b ? b : x);
}

#endif
