# esp-idf-hello-word

esp-idf hello word project using clion


This code is sourced from youtube channel https://www.youtube.com/user/howroyd about esp and c++

### Running And Build

1. Build esp project
   
    In terminal running :
    ```shell
      . $HOME/esp/esp-idf/export.sh
    ```
   This command **. $HOME/esp/esp-idf/export.sh** is used for set up the environment variables
   
    Then Running :
    ```
    idf.py build
    ```
    This command **idf.py build** used for build esp project

2. Flash
     ```
     idf.py -p ESP-PORT -b 115200 flash 
     ```
    This command **idf.py build** used for flash program to esp device
   
3. Monitor
    ```
    idf.py -p ESP-PORT -b 115200 monitor  
    ```
    This command **idf.py build** used for monitor esp device by serial port
