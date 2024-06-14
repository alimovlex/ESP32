cmake_minimum_required(VERSION 3.5)


set(CMAKE_CXX_STANDARD 17)
#Change this to what you chose during install
set(ENV{IDF_PATH} "/home/robot/esp/esp-idf") #The ESP-IDF location
set(PYTHON "/home/robot/.espressif/python_env/idf4.4_py3.12_env/bin/python") #The systems python installation
set(GIT_PATH "/usr/bin/git") #The systems git location
set(DOT_EXPRESSIF "/home/robot/.espressif") #The expressif tools folder

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(esp32t)

include_directories("main")
