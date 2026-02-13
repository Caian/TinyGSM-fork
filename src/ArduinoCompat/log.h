#pragma once

#include "esp_log.h"

#define log_d(...) ESP_LOGD("TinyGSM", __VA_ARGS__)
#define log_e(...) ESP_LOGE("TinyGSM", __VA_ARGS__)
#define log_w(...) ESP_LOGW("TinyGSM", __VA_ARGS__)
#define log_v(...) ESP_LOGV("TinyGSM", __VA_ARGS__)
