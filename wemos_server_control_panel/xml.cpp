#include <Arduino.h>
#include <HardwareSerial.h>
#include <TinyXML.h>
#include "xml.hpp"

#define LED_PIN LED_BUILTIN /// IO Pin used for LED
#define LED_OFF 1           /// Off state for LED
#define LED_ON 0            /// On state for LED

#define BUFFER_SIZE 100

void XML_dump_callback(uint8_t statusflags, char* tagName,uint16_t tagNameLen, char* data, uint16_t dataLen)
{
  digitalWrite(LED_PIN, LED_ON);
  Serial.println(tagName);
  if(statusflags & STATUS_ATTR_TEXT)
  {
    char buffer[BUFFER_SIZE];
    int len = dataLen < (BUFFER_SIZE -1)?dataLen:(BUFFER_SIZE -1);
    strncpy(buffer,data,len);
    buffer[len] = '\0';
    
    Serial.print(":");
    Serial.println(buffer);
  }
}
