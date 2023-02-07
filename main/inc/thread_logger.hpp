/*
    thread_logger.hpp
    ESP32
    Created by alimovlex.
    Copyright (c) 2023 alimovlex. All rights reserved.
*/

void print_thread_info(const char *extra = nullptr);
void thread_func_inherited();
void spawn_another_thread();
void thread_func_any_core();
void thread_func();
esp_pthread_cfg_t create_config(const char *name, int core_id, int stack, int prio);