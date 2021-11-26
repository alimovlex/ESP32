//
// Created by Ludin Nento on 30/07/21.
//

#include "gpio.h"

namespace gpio {
    esp_err_t gpio_base::init() {
        esp_err_t status{ESP_OK};

        status |= gpio_config(&_cfg);

        return status;
    }

    esp_err_t gpio_output::init() {
        esp_err_t  status{gpio_base::init()};

        if( ESP_OK == status) {
            status |= set(_inverted_logic);
        }

        return status;
    }

    esp_err_t gpio_output::set(const bool state) {
        _state = state;
        return gpio_set_level(_pin, _inverted_logic == !state);
    }
}