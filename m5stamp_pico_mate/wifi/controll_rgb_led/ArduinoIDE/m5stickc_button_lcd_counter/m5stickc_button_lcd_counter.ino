#include <Bounce2.h>
#include <M5StickC.h>

//Taster A,  mit der Auschrift "M5" am GPIO 37 angeschlossen
#define btnA G37

//Taster B,  am GPIO 39 angeschlossen
#define btnB G39

//Pause in Millisekunden zwischen zwei Signalen
const int PAUSE = 50;

//initialisieren der Bounce Objekte für die Taster
Bounce btnAbounce = Bounce(btnA, PAUSE);
Bounce btnBbounce = Bounce(btnB, PAUSE);

//der Zähler welcher manipuliert werden soll
int counter = 0;

void setup() {
  //Taster als Eingang über den internen Pullup Widerstand
  pinMode(btnA, INPUT_PULLUP);
  pinMode(btnB, INPUT_PULLUP);

  //für das LCD Display
  M5.begin();
  //Bildschirm in Schwarz
  M5.Lcd.fillScreen(BLACK);
  //um 90° drehen
  M5.Lcd.setRotation(1);
}

void loop() {
  //aktualisieren des Tasters
  btnAbounce.update();
  btnBbounce.update();

  //Wenn der Taster A betätigt wird dann...
  if (btnAbounce.rose()) {
    //Zähler um eins erhöhen
    ++counter;
    //Ausgabe des Wertes des Zählers
    displayCounter();
  }

  //Wenn der Taster B wird wird dann...
  if (btnBbounce.rose()) {
    //Zähler um eins verringern
    --counter;
    //Ausgabe des Werstes des Zählers
    displayCounter();
  }
}

//Ausgeben des Wertes des Zählers
//auf dem LCD Display des M5StickC
void displayCounter() {
  //Display löschen und Schwarz einfärben
  M5.Lcd.fillScreen(BLACK);
  //Positionieren des Textes an den Koordinaten
  M5.Lcd.setCursor(20, 40);
  //Schriftfarbe weiß
  M5.Lcd.setTextColor(WHITE);
  //Schriftgröße 3
  M5.Lcd.setTextSize(3);

  //den Integer Wert in ein String umwandeln
  String text = String(counter, DEC);
  //Umwandeln des Strings in ein char* und ausgeben auf dem LCD Display
  M5.Lcd.printf(text.c_str());
}
