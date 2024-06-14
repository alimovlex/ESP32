//
// Created by Ludin Nento on 30/07/21.
//

#ifndef ESP32T_MAIN_H
#define ESP32T_MAIN_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "nvs_flash.h"

#include "gpio.h"
#include "sntp.h"

#define pdSECOND pdMS_TO_TICKS(1000)

class main final {

public:
    gpio::gpio_output led{GPIO_NUM_2, true};

public:

    esp_err_t setup();
    void loop();
};

#endif //ESP32T_MAIN_H
