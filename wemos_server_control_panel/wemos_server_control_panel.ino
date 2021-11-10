#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "private.h"
#include "Html.hpp"
#include "wol.hpp"
#include "Server.hpp"

#ifndef HOST_NAME
#define HOST_NAME "esp8266" /// Hostname used by dynamic DNS. e.g. esp8266.local
#endif

extern SCP_Server private_wol[]; /// A list of names and mac addresses.
extern SCP_Server private_ilo[]; /// A list of names and ilo IP addresses.

#define LED_PIN LED_BUILTIN /// IO Pin used for LED
#define LED_OFF 1           /// Off state for LED
#define LED_ON 0            /// On state for LED

const char* ssid = PRIVATE_STASSID;     /// The SSID for the WiFi network. (Add PRIVATE_STASSID to private.h)
const char* password = PRIVATE_STAPSK;  /// The password for the WIFI network. (Add PRIVATE_STAPSK to private.h)

ESP8266WebServer server(80);  /// Web server class.Server starts on port provided.
Html html(&server);           /// HTML service started on server.

/**
 * handleRoot()
 * Server Control panel home page.
 */
void handleRoot() {
  digitalWrite(LED_PIN, LED_ON);  
  HtmlPage page = HtmlPage(
    HtmlTitle("Server Control Panel"),
    HtmlHeader("Server Control Panel","1") + HtmlLink("Wake On LAN","wol.html") + HtmlLink("iLo","ilo.html")
  );
  html.send(page);
  digitalWrite(LED_PIN, LED_OFF);
}

/**
 * handleWol()
 * Wake On LAN 'static' page.
 */
void handleWol() {
  digitalWrite(LED_PIN, LED_ON);
  // Create a list of servers.
  int i = 0;
  String list("");
  while(private_wol[i].name) {
    list = list + HtmlLink(private_wol[i].name,String("/wol.cgi?MAC=") + private_wol[i].address);
    list += HtmlBr();
    i++;
  }
  HtmlPage page = HtmlPage(
    HtmlTitle("Wake On LAN"),
      HtmlHeader("Wake On LAN","1") + list +
 //     HtmlLink("Test wake on LAN","/wol.cgi?MAC=01:02:03:04:05:06:07:08") +
      HtmlBr() +
      HtmlLink("Home","/")
  );
  html.send(page);
  digitalWrite(LED_PIN, LED_OFF);
}


/**
 * handleIlo()
 *  
 *  iLo 'static' page.
 */
void handleIlo() {
  digitalWrite(LED_PIN, LED_ON);
  // Create a list of servers.
  int i = 0;
  String list("");
  String list2("");
  while(private_ilo[i].name) {
    list += HtmlLink(private_ilo[i].name,String("http://") + private_ilo[i].address + "/xmldata?item=all" );
    list += HtmlBr();

    list2 += HtmlLink(private_ilo[i].name,String("http://") + private_ilo[i].address);
    list2 += HtmlBr();
    i++;
  }
  HtmlPage page = HtmlPage(
    HtmlTitle("iLo"),
      HtmlHeader("iLo XML","1") + list +
      HtmlBr() +
      HtmlHeader("iLo Administration","1") + list2 +
      HtmlBr() +
      HtmlLink("Home","/")
  );
  html.send(page);
  digitalWrite(LED_PIN, LED_OFF);
}

/*
 * handleWolCgi()
 * Handle a WOL request.
 */
void handleWolCgi() {
  digitalWrite(LED_PIN, LED_ON);
  String param = "";
  for (uint8_t i = 0; i < server.args(); i++) {
    if(server.argName(i).equals("MAC")) {
      param += server.arg(i);
    }
  }

  if(!param.equals("")) {
    HtmlPage page = HtmlPage(
      HtmlTitle("Wake On LAN sent!"),
      HtmlHeader("Wake On LAN sent!","1") +
      "A Wake On Lan massage was sent to " +
      param + 
      HtmlBr() +
      HtmlLink("Wake On LAN","/wol.html")
    );
    wol(param.c_str());
    html.send(page);
  }
  else
  {
    HtmlPage page = HtmlPage(
      HtmlTitle("Error:Wake On LAN"),
        HtmlHeader("Error:Wake On LAN","1") + 
        HtmlBr() +
        HtmlLink("Wake On LAN","/wol.html")
    );
    html.send(page);
  }
  
  digitalWrite(LED_PIN, LED_OFF);
}

/*
 * handleNotFound()
 * Handle not found page.
 */
void handleNotFound() {
  digitalWrite(LED_PIN, LED_ON);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(LED_PIN, LED_OFF);
}

void setup(void) {
  int led_state = LED_ON;
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN,led_state);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(LED_PIN, led_state); // Flash LED while connecting.
    led_state = !led_state;
  }
  digitalWrite(LED_PIN, LED_OFF);
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin(HOST_NAME)) {
    Serial.println("MDNS responder started");
  }

  // Setup wol
  wolInit();

  server.on("/", handleRoot);
  server.on("/wol.html",handleWol);
  server.on("/wol.cgi",handleWolCgi);
  server.on("/ilo.html",handleIlo);
  
  /*
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
 */
  server.on("/gif", []() {
    static const uint8_t gif[] PROGMEM = {
      0x47, 0x49, 0x46, 0x38, 0x37, 0x61, 0x10, 0x00, 0x10, 0x00, 0x80, 0x01,
      0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x2c, 0x00, 0x00, 0x00, 0x00,
      0x10, 0x00, 0x10, 0x00, 0x00, 0x02, 0x19, 0x8c, 0x8f, 0xa9, 0xcb, 0x9d,
      0x00, 0x5f, 0x74, 0xb4, 0x56, 0xb0, 0xb0, 0xd2, 0xf2, 0x35, 0x1e, 0x4c,
      0x0c, 0x24, 0x5a, 0xe6, 0x89, 0xa6, 0x4d, 0x01, 0x00, 0x3b
    };
    char gif_colored[sizeof(gif)];
    memcpy_P(gif_colored, gif, sizeof(gif));
    // Set the background to a random set of colors
    gif_colored[16] = millis() % 256;
    gif_colored[17] = millis() % 256;
    gif_colored[18] = millis() % 256;
    server.send(200, "image/gif", gif_colored, sizeof(gif_colored));
  });

  server.onNotFound(handleNotFound);

  /////////////////////////////////////////////////////////
  // Hook examples

  server.addHook([](const String & method, const String & url, WiFiClient * client, ESP8266WebServer::ContentTypeFunction contentType) {
    (void)method;      // GET, PUT, ...
    (void)url;         // example: /root/myfile.html
    (void)client;      // the webserver tcp client connection
    (void)contentType; // contentType(".html") => "text/html"
    Serial.printf("A useless web hook has passed\n");
    Serial.printf("(this hook is in 0x%08x area (401x=IRAM 402x=FLASH))\n", esp_get_program_counter());
    return ESP8266WebServer::CLIENT_REQUEST_CAN_CONTINUE;
  });

  server.addHook([](const String&, const String & url, WiFiClient*, ESP8266WebServer::ContentTypeFunction) {
    if (url.startsWith("/fail")) {
      Serial.printf("An always failing web hook has been triggered\n");
      return ESP8266WebServer::CLIENT_MUST_STOP;
    }
    return ESP8266WebServer::CLIENT_REQUEST_CAN_CONTINUE;
  });

  server.addHook([](const String&, const String & url, WiFiClient * client, ESP8266WebServer::ContentTypeFunction) {
    if (url.startsWith("/dump")) {
      Serial.printf("The dumper web hook is on the run\n");

      // Here the request is not interpreted, so we cannot for sure
      // swallow the exact amount matching the full request+content,
      // hence the tcp connection cannot be handled anymore by the
      // webserver.
#ifdef STREAMSEND_API
      // we are lucky
      client->sendAll(Serial, 500);
#else
      auto last = millis();
      while ((millis() - last) < 500) {
        char buf[32];
        size_t len = client->read((uint8_t*)buf, sizeof(buf));
        if (len > 0) {
          Serial.printf("(<%d> chars)", (int)len);
          Serial.write(buf, len);
          last = millis();
        }
      }
#endif
      // Two choices: return MUST STOP and webserver will close it
      //                       (we already have the example with '/fail' hook)
      // or                  IS GIVEN and webserver will forget it
      // trying with IS GIVEN and storing it on a dumb WiFiClient.
      // check the client connection: it should not immediately be closed
      // (make another '/dump' one to close the first)
      Serial.printf("\nTelling server to forget this connection\n");
      static WiFiClient forgetme = *client; // stop previous one if present and transfer client refcounter
      return ESP8266WebServer::CLIENT_IS_GIVEN;
    }
    return ESP8266WebServer::CLIENT_REQUEST_CAN_CONTINUE;
  });

  // Hook examples
  /////////////////////////////////////////////////////////

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
