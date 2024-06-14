/*
    WifiCommunicator.cpp
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


using namespace std;
using namespace chrono;

const auto sleep_time = seconds
{
    5
};

WifiCommunicator App;

void WifiCommunicator::run(void)
{
    wifiState = Wifi.GetState();

    switch (wifiState)
    {
    case WIFI::Wifi::state_e::READY_TO_CONNECT:
        cout << "Wifi Status: READY_TO_CONNECT" << endl;
        Wifi.Begin();
        break;
    case WIFI::Wifi::state_e::DISCONNECTED:
        cout << "Wifi Status: DISCONNECTED" << endl;
        Wifi.Begin();
        break;
    case WIFI::Wifi::state_e::CONNECTING:
        cout << "Wifi Status: CONNECTING" << endl;
        break;
    case WIFI::Wifi::state_e::WAITING_FOR_IP:
        cout << "Wifi Status: WAITING_FOR_IP" << endl;
        break;
    case WIFI::Wifi::state_e::ERROR:
        cout << "Wifi Status: ERROR" << endl;
        break;
    case WIFI::Wifi::state_e::CONNECTED:
        cout << "Wifi Status: CONNECTED" << endl;
        break;
    case WIFI::Wifi::state_e::NOT_INITIALIZED:
        cout << "Wifi Status: NOT_INITIALIZED" << endl;
        break;
    case WIFI::Wifi::state_e::INITIALIZED:
        cout << "Wifi Status: INITIALIZED" << endl;
        break;
    }
}

void WifiCommunicator::setup(void)
{
    esp_event_loop_create_default();
    nvs_flash_init();
    Wifi.SetCredentials(App.SSID,App.PASSWORD);
    Wifi.Init();
}

void WifiCommunicator::connect() {
     App.setup();
     while (true) {
        App.run();
        this_thread::sleep_for(sleep_time);
    }
}