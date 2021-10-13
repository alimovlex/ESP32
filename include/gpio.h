//
// Created by Ludin Nento on 30/07/21.
//

#ifndef ESP32T_GPIO_H
#define ESP32T_GPIO_H

#include "driver/gpio.h"

namespace gpio {

    class gpio_base {
    protected:
        const gpio_num_t _pin;
        const gpio_config_t _cfg;
        const bool _inverted_logic = false;

    public:
        constexpr gpio_base(const gpio_num_t pin,
                            const gpio_config_t& config,
                            const bool _invert_logic = false)
        : _pin{pin},
          _cfg{config},
          _inverted_logic{_invert_logic}
        {

        }

        [[nodiscard]] esp_err_t init();

    public:
        virtual bool state() = 0;
        virtual esp_err_t set(const bool state) = 0;
    };



    class gpio_output : public gpio_base {
    private:
        bool _state = false;
    public:
        constexpr gpio_output(const gpio_num_t pin, const bool invert = false)
        : gpio_base{ pin,
                     gpio_config_t {
                                .pin_bit_mask = static_cast<uint64_t>(1) << pin,
                                .mode = GPIO_MODE_OUTPUT,
                                .pull_up_en = GPIO_PULLUP_DISABLE,
                                .pull_down_en = GPIO_PULLDOWN_ENABLE,
                                .intr_type = GPIO_INTR_DISABLE
                            },
                            invert
                    }

        {

        }

        esp_err_t init();
        esp_err_t set(const bool state);
        esp_err_t toggle();
        bool state() { return _state; }
    };


    class gpio_input {
    private:
        gpio_num_t _pin;
    public:
        esp_err_t init();
        bool state();
    };

} // namespace GPIO

#endif //ESP32T_GPIO_H
