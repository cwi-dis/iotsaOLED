#ifndef _IOTSAOLED_H_
#define _IOTSAOLED_H_
#include "iotsa.h"
#include "iotsaApi.h"
#include "iotsaBLEServer.h"
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

class IotsaOLEDMod : public IotsaApiMod, public IotsaBLEApiProvider {
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
  void setup() override;
  void serverSetup() override;
  void loop() override;
  String info() override;
protected:
  bool postHandler(const char *path, const JsonVariant& request, JsonObject& reply) override;
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
#ifdef IOTSA_WITH_BLE
  IotsaBleApiService bleApi;
  bool blePutHandler(UUIDstring charUUID) override;
  bool bleGetHandler(UUIDstring charUUID) override;
  static constexpr UUIDstring serviceUUID = "736980F5-2F5A-4E6C-9509-103271B4AFDE";
  static constexpr UUIDstring messageUUID = "8ABAD996-486D-4074-8919-D41A5D1E96ED";
#endif // IOTSA_WITH_BLE

};
#endif // _IOTSOLED_H_
