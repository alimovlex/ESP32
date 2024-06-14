
#pragma once

#include <string>
#include <iostream>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"

#include "wifi_driver.hpp"

class Led final
{
private:
    //void run(void);
    //void setup(void);
    
public:
    static void blink();
    
};