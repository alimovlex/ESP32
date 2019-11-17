#include "sandbox.hpp"
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif
int LED_BUILTIN = 2;
void setup() 
{
pinMode (LED_BUILTIN, OUTPUT);
//wifi();

}
void loop() 
{
//printLocalTime();
//LED();
/* xTaskCreatePinnedToCore(TaskBlink, "TaskBlink",1024,NULL,2,NULL,ARDUINO_RUNNING_CORE);
 * 1) The first parameter is the name of the task defined in sandbox.cpp module
 * 2) The second parameter is the name of the task for humans in a char format
 * 3) The third parameter is the stack size allocated for the task
 * 4) NULL
 * 5) The priority of the task from 0 to 3 where 3 is the highest 
 */
xTaskCreatePinnedToCore(TaskBlink, "TaskBlink",1024,NULL,2,NULL,ARDUINO_RUNNING_CORE);

}
