# Wemos Server Control Panel

## Instructions

* LED flashes while connecting to the wifi.
* The LED should be out when connected.
* LED flickers on access.
* Access via DHCP allocated IP address or at http://esp8266.local if dynamic DNS is supported by your browser's host.


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

Files private.h and private.c contain private data. You will need to add these. If stuff is not compiling then you may need to add items to your version of thsese files.

### private.h

```
#define PRIVATE_STASSID "your-ssid"
#define PRIVATE_STAPSK  "your-password"

// #define HOST_NAME "myhostname" // Optional dynamic DNS name.
```

### public.cpp

```
#include "Server.hpp"

SCP_Server private_ilo[] = {{"name1","hostname or ip1"},{"name2","hostname or ip2"},{0}};
SCP_Server private_wol[] = {{"name1","mac1"},{"name2","mac2"},{0}};
SCP_Server private_servers[] = {{"name1","hostname or ip1"},{"name2","hostname or ip2"},{0}};
```
## About

I am starting by targeting a wemos D1 (esp-8266) using Mac arduno IDE. That is what I have. Happy to add portability changes to master if requested.

# IDE setup

* https://github.com/esp8266/Arduino#installing-with-boards-manager
* WakeOnLan (Through library manager)

# Windows find MAC addresses

On windows use "ARP -A" in a cmd prompt to list all cached IP to MAC address mappings. To add a mapping turn on the target host and ping it. Then run the arp command again.

# References

A random list of links that may or maynot be useful.

 * https://www.wemos.cc/en/latest/d1/d1_mini.html
 * https://github.com/esp8266/Arduino
 * https://en.wikipedia.org/wiki/Wake-on-LAN
 * iLo4 scripting https://support.hpe.com/hpesc/public/docDisplay?docId=c03334058

