#ifndef _IOTSAOLED_H_
#define _IOTSAOLED_H_
#include "iotsa.h"
#include "iotsaApi.h"

#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

class IotsaOLEDMod : IotsaApiMod {
public:
  IotsaOLEDMod(IotsaApplication &_app, int _pin_sda, int _pin_scl, int _width, int _height)
  : IotsaApiMod(_app),
    pin_sda(_pin_sda),
    pin_scl(_pin_scl),
    width(_width),
    height(_height),
    x(0),
    y(0),
    display(NULL)
  {}
  void setup();
  void serverSetup();
  void loop();
  String info();
protected:
  bool postHandler(const char *path, const JsonVariant& request, JsonObject& reply);
private:
  void handler();
  void printPercentEscape(String &src);
  void printString(String &src);
  int pin_sda;
  int pin_scl;
  int width;
  int height;
  int x;
  int y;
  Adafruit_SSD1306 *display;
};
#endif // _IOTSOLED_H_
