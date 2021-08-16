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


class HtmlPage: public TempString {
  public:
  HtmlPage(char* headers, char * body):TempString(
    "<html>\n<headers>\n"
    "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n",
    headers,
    "\n</headers>\n<body style=\"font-family: monospace;\">\n",
    body,
    "\n</body>\n</html>\n"){};
};

class HtmlTitle: public TempString {
  public:
  HtmlTitle(char* a):TempString("\n<title>",a,"</title>\n"){};
};

class HtmlHeader: public TempString {
  public:
  HtmlHeader(char* a,char * n):TempString("\n<h",n,">",a,"</h",n,">\n"){};
};
