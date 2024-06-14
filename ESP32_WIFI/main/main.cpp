/*
    main.cpp
    ESP32
    Created by alimovlex.
    Copyright (c) 2023 alimovlex. All rights reserved.
*/

#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include <string>
#include <sstream>
#include <esp_pthread.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include "thread_logger.hpp"
#include "WifiCommunicator.hpp"
#include "Led.hpp"

using namespace std;
using namespace chrono;

const auto sleep_time = seconds
{
    5
};

extern "C" void app_main(void)
{
    // Create a thread using deafult values that can run on any core
    auto cfg = esp_pthread_get_default_config();
    //esp_pthread_set_cfg(&cfg);
    //thread any_core(thread_func_any_core);

    WifiCommunicator *wifiManager = new WifiCommunicator;
    Led *led_blinker = new Led;
    // Create a thread on core 1.
    cfg = create_config("Wi-Fi Thread 1", 1, 3 * 1024, 5);
    esp_pthread_set_cfg(&cfg);
    thread thread_1(wifiManager->connect);


    cfg = create_config("LED GPIO thread", 1, 3 * 1024, 5);
    esp_pthread_set_cfg(&cfg);
    thread thread_2(led_blinker->blink);

    //delete wifiManager;
    // Let the main task do something too
    while (true) {
        stringstream ss;
        ss << "core id: " << xPortGetCoreID()
           << ", prio: " << uxTaskPriorityGet(nullptr)
           << ", minimum free stack: " << uxTaskGetStackHighWaterMark(nullptr) << " bytes.";
        ESP_LOGI(pcTaskGetTaskName(nullptr), "%s", ss.str().c_str());
        this_thread::sleep_for(sleep_time);
    }
}


/*
    // Create a thread on core 0 that spawns another thread, they will both have the same name etc.
    cfg = create_config("Thread 1", 0, 3 * 1024, 5);
    cfg.inherit_cfg = true;
    esp_pthread_set_cfg(&cfg);
    thread thread_1(spawn_another_thread);

    // Create a thread on core 1.
    cfg = create_config("Thread 2", 1, 3 * 1024, 5);
    esp_pthread_set_cfg(&cfg);
    thread thread_2(thread_func);
    */