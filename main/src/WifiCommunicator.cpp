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
        cout << "Wifi Status: READY_TO_CONNECT\n";
        Wifi.Begin();
        break;
    case WIFI::Wifi::state_e::DISCONNECTED:
        cout << "Wifi Status: DISCONNECTED\n";
        Wifi.Begin();
        break;
    case WIFI::Wifi::state_e::CONNECTING:
        cout << "Wifi Status: CONNECTING\n";
        break;
    case WIFI::Wifi::state_e::WAITING_FOR_IP:
        cout << "Wifi Status: WAITING_FOR_IP\n";
        break;
    case WIFI::Wifi::state_e::ERROR:
        cout << "Wifi Status: ERROR\n";
        break;
    case WIFI::Wifi::state_e::CONNECTED:
        cout << "Wifi Status: CONNECTED\n";
        break;
    case WIFI::Wifi::state_e::NOT_INITIALIZED:
        cout << "Wifi Status: NOT_INITIALIZED\n";
        break;
    case WIFI::Wifi::state_e::INITIALIZED:
        cout << "Wifi Status: INITIALIZED\n";
        break;
    }
}

void WifiCommunicator::setup(void)
{
    esp_event_loop_create_default();
    nvs_flash_init();

    Wifi.SetCredentials("your ssid", "Your password");
    Wifi.Init();
}

void WifiCommunicator::connect() {
     App.setup();
     while (true) {
        print_thread_info("HELLO FROM THE CPP METHOD!!!");
        cout<<"Printing from the console output" << endl;
        App.run();
        this_thread::sleep_for(sleep_time);
    }
}