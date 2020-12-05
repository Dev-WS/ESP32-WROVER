
#ifndef MAIN_H
#define MAIN_H


#include <string.h>

#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/task.h"

#include "sdkconfig.h" // generated by "make menuconfig"

#include "ssd1366.h"
#include "functionsLCD.h"

#include "font8x8_basic.h"
#include "./BME280/bme280.h"
#include "init_bme280.h"


#endif