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
    void run(void);
    void setup(void);
    WIFI::Wifi::state_e wifiState { WIFI::Wifi::state_e::NOT_INITIALIZED };
    WIFI::Wifi Wifi;
    const char* SSID = "WIFI_SSID";
    const char* PASSWORD = "WIFI_PASSWORD";
public:
    static void connect();
    
};
