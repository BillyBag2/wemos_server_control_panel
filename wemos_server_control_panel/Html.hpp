#include <ESP8266WebServer.h>
#include "TempString.hpp"

/*
 * class Html
 * Send Html via a ESP8266WebServer
 */
class Html {
private:
  ESP8266WebServer * m_server;
  
public:
  Html(ESP8266WebServer * server);
  void send(char * html) ;
};
