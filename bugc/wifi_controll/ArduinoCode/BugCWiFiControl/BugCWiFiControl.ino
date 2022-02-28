#include <M5StickC.h>
#include <WiFi.h>
#include <WebServer.h>
#include "bugC.h"

#define debug

//SSID aus dem Router
const char* ssid = "";
//Passwort für den Zugang zum WLAN
const char* password = "";

//Port auf welchem der Server laufen soll.
WebServer server(80);
//Servlet welches aufgerufen werden muss
//um die Funktionen als GET-Parameter
//zu übergeben
const String SERVLET = "/move";

//Funktionen
const String FORWARD = "forward";
const String BACKWARD = "backward";
const String LEFT = "left";
const String RIGHT = "right";
const String STOPP = "stop";

BUGC BugC;
//Farben für die LEDs
uint32_t COLOR_RED = 0x100000;
uint32_t COLOR_BLACK = 0x000000;


void callHandleAction();
String getPage();

void setup() {
  M5.begin();
  M5.Lcd.setTextColor(TFT_GREEN);
  M5.Lcd.setRotation(1);

  BugC.Init();

  // if add battery, need increase charge current
  M5.Axp.SetChargeCurrent(CURRENT_360MA);

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  // Warten auf die WiFi Verbindung
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }

  //Wenn erfolgreich verbunden
  //die Daten auf der seriellen Schnittstelle ausgeben
  Serial.println("");
  Serial.print("Erfolgreich verbunden zu ");
  Serial.println(ssid);
  Serial.print("IP Adresse: ");
  Serial.println(WiFi.localIP());

  //Ausgeben der Adresse auf dem Display
  M5.Lcd.setTextSize(1);
  M5.Lcd.drawCentreString(WiFi.localIP().toString() + SERVLET, 45, 30, 2);

  //Server starten und warten auf Verbindungen
  server.begin(); // Starten des Servers.
  server.on(SERVLET, callHandleAction);
}

void loop() {
  server.handleClient();
}

void callHandleAction() {
  //behandeln der GET-Parameter
  Serial.println("callHandleAction");
  for (int i = 0; i < server.args(); i++) {
    String parameterName = server.argName(i);
    String parameterValue = server.arg(i);

#ifdef debug
    Serial.print("paramName: ");
    Serial.print(parameterName);
    Serial.print(" paramValue:");
    Serial.println(parameterValue);
#endif
    //Funktion abhandlen
    if (parameterValue == FORWARD) {
      drawText("F");
      lightUpLeds(COLOR_RED, COLOR_RED);
      moveBugC(100, 100, 100, 100);
    } else if (parameterValue == BACKWARD) {
      drawText("B");
      lightUpLeds(COLOR_RED, COLOR_RED);
      moveBugC(-100, -100, -100, -100);
    } else if (parameterValue == LEFT) {
      drawText("L");
      lightUpLeds(COLOR_RED, COLOR_BLACK);
      moveBugC(100, -100, 100, -100);
    } else if (parameterValue == RIGHT) {
      drawText("R");
      lightUpLeds(COLOR_BLACK, COLOR_RED);
      moveBugC(-100, 100, -100, 100);
    } else if (parameterValue == STOPP) {
      drawText("S");
      lightUpLeds(COLOR_BLACK, COLOR_BLACK);
      moveBugC(0, 0, 0, 0);
    }
  }
  M5.update();
  //Zum Schluss noch die Seite ausliefern
  server.send(200, "text/html", getPage());
}

void drawText(String text) {
  M5.Lcd.setRotation(0);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(3);
  M5.Lcd.drawCentreString(text, 45, 75, 2);
}

void lightUpLeds(uint32_t left, uint32_t right) {
  BugC.BugCSetColor(left, right);
}

void moveBugC(int speed0, int speed1, int speed2, int speed3) {
  BugC.BugCSetAllSpeed(speed0, speed1, speed2, speed3);
}

String getPage() {
  return "<html><head><script src='https://progs.draeger-it.blog/bugc/js/jquery.js'></script><script src='https://progs.draeger-it.blog/bugc/js/function.js'></script><link rel='stylesheet' type='text/css' href='https://progs.draeger-it.blog/bugc/css/styles.css'/></head><script>var ipAdresse='192.168.178.55';</script><body><h1 style='text-align:center;'>M5Stack BugC - WiFi Control</h1><table style='width:400px; height: 400px;margin:0 auto;'><tr><td></td><td><center><button type='button' id='topBtn'>&#8593;</button></center></td><td></td></tr><tr><td><center><button type='button' id='leftBtn'>&#8592;</button></center></td><td><center><button type='button' id='stopBtn'>&#9723;</button></center></td><td><center><button type='button' id='rightBtn'>&#8594;</button></center></td></tr><tr><td></td><td><center><button type='button' id='bottomBtn'>&#8595;</button></center></td><td></td></tr></table></body></html>";
}
