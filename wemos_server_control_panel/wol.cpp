#include <WiFiUdp.h>
WiFiUDP UDP;

#include <WakeOnLan.h>
WakeOnLan WOL(UDP); // Pass WiFiUDP class

// See https://github.com/a7md0/WakeOnLan

void wol(const char * mac) {
  WOL.sendMagicPacket(mac);
}

void wolInit() {
  WOL.setRepeat(3, 100);
  //WOL.calculateBroadcastAddress(WiFi.localIP(), WiFi.subnetMask());
}
