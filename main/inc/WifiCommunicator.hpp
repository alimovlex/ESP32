/*
    WifiCommunicator.hpp
    ESP32
    Created by alimovlex.
    Copyright (c) 2023 alimovlex. All rights reserved.
*/

#pragma once

#include <string>
#include <iostream>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"

#include "wifi_driver.hpp"

class WifiCommunicator final
{
private:
public:
    void run(void);
    void setup(void);
    static void connect();
    WIFI::Wifi::state_e wifiState { WIFI::Wifi::state_e::NOT_INITIALIZED };
    WIFI::Wifi Wifi;
};