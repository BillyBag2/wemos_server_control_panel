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


class HtmlPage: TempString {
  public:
  HtmlPage(char* a, char * b):TempString("<html>\n<headers>",a,"\n</headers>\n<body>\n",b,"\n</body>\n</html>"){};
  char * page() {return s();};
};
