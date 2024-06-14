#include_directories(./../include)

set(SOURCES
        "main.cpp"
        "../source/gpio.cpp"
        "../source/nvs32.cpp"
        )


idf_component_register(SRCS ${SOURCES}
        INCLUDE_DIRS "" "./../include/")