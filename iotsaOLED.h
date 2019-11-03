#ifndef _IOTSAOLED_H_
#define _IOTSAOLED_H_
#include "iotsa.h"
#include "iotsaApi.h"

class IotsaOLEDMod : IotsaApiMod {
public:
  IotsaOLEDMod(IotsaApplication &_app, int _pin_sda, int _pin_scl)
  : IotsaApiMod(_app),
    pin_sda(_pin_sda),
    pin_scl(_pin_scl),
    x(0),
    y(0)
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
  int x;
  int y;
};
#endif // _IOTSOLED_H_
