#include "sandbox.hpp"
int LED_BUILTIN = 2;
void setup() 
{
pinMode (LED_BUILTIN, OUTPUT);
wifi();
}
void loop() 
{
//printLocalTime();
LED();
}
