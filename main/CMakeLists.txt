#include_directories(./../include)

set(SOURCES
        "main.cpp"
        "systeminfo.cpp"
        "gpio.cpp"
        "nvs32.cpp"
        )


idf_component_register(SRCS ${SOURCES}
        INCLUDE_DIRS "" "./../include/")