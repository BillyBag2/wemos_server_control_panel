# Wemos Server Control Panel

## Instructions

Create your own private.h file and add...
```
#define PRIVATE_STASSID "your-ssid"
#define PRIVATE_STAPSK  "your-password"
```

Build and program device. LED flashes while connecting. The LED should be out when connected. LED flickers on access.

## Overview (WIP)

Wemos web portal to control servers. I have some HP gen 6 and gen 8 servers that are expensive to leave on. This project was created to provide web control over these.

Working...

 * Web interface.(WIP)

Wishlist...

 * Send Wake On Lan
 * iLO2/iL04 Power control.
 * iLO2/iL04 Power meter.
 * ssh commands, eg shutdown. 
 * File based config. (static to start with)

## Coding

I intend to create private.h and private.c that will contain private data. If stuff is not compiling then you may need to add items to your version of thsese files.

## About

I am starting by targeting a wemos D1 (esp-8266) using Mac arduno IDE. That is what I have. Happy to add portability changes to master if requested.

# IDE setup

* https://github.com/esp8266/Arduino#installing-with-boards-manager


# References

A random list of links that may or maynot be useful.

 * https://www.wemos.cc/en/latest/d1/d1_mini.html
 * https://github.com/esp8266/Arduino
 * https://en.wikipedia.org/wiki/Wake-on-LAN
 * iLo4 scripting https://support.hpe.com/hpesc/public/docDisplay?docId=c03334058

