//
// Created by Ludin Nento on 22/07/21.
//

#ifndef ESP32T_SYSTEMINFO_H
#define ESP32T_SYSTEMINFO_H

#include <stdio.h>
#include "esp_system.h"
#include "esp_spi_flash.h"

class esp_system_info {

private:
    esp_chip_info_t chip_info;

public:
    void print();

};

#endif //ESP32T_SYSTEMINFO_H
