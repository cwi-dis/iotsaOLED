#include "iotsa.h"
#include "iotsaOLED.h"


#include <Wire.h>
#if 0
// The LiquidCrystal library needed is from
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads/LiquidCrystal_V1.2.1.zip
#include <LiquidCrystal_I2C.h>



LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
#endif
unsigned long clearTime;  // time at which to turn off backlight

#ifdef IOTSA_WITH_WEB
// LCD handlers
void IotsaOLEDMod::setup() {
  IFDEBUG IotsaSerial.print("oledSetup");
  Wire.begin(pin_sda, pin_scl);
#if 0
  lcd.begin(lcd_width, lcd_height);
  lcd.backlight();
  lcd.print(iotsaConfig.hostName);
  delay(200);
  lcd.noBacklight();
  lcd.clear();
#endif
  IFDEBUG IotsaSerial.println(" done");
}

void IotsaOLEDMod::handler() {
  String msg;
  bool any = false;
  bool didBacklight = false;
  bool didPos = false;

  if( server->hasArg("msg")) {
    msg = server->arg("msg");
    any = true;
  }
  if( server->hasArg("clear")) {
    if (atoi(server->arg("clear").c_str()) > 0) {
#if 0
      lcd.clear();
#endif
      if (!didPos) x = y = 0;
    }
    any = true;
  }
  if( server->hasArg("x")) {
    const char *arg = server->arg("x").c_str();
    if (arg && *arg) {
      didPos = true;
      x = atoi(arg);
    }
  }
  if( server->hasArg("y")) {
    const char *arg = server->arg("y").c_str();
    if (arg && *arg) {
      didPos = true;
      y = atoi(arg);
    }
  }
  if (server->hasArg("backlight")) {
    const char *arg = server->arg("backlight").c_str();
    if (arg && *arg) {
      int dur = atoi(arg);
      any = true;
      didBacklight = true;
      if (dur) {
        clearTime = millis() + dur*1000;
      } else {
        clearTime = 0;
      }
      any = true;
    }
  }

  if (any) {
#if 0
      lcd.setCursor(x, y);
//      IFDEBUG IotsaSerial.print("Show message ");
//      IFDEBUG IotsaSerial.println(msg);
      printPercentEscape(msg);
      if (!didBacklight) 
         clearTime = millis() + 5000; // 5 seconds is the default display time
      if (clearTime) {
        IFDEBUG IotsaSerial.println("backlight");
        lcd.backlight();
      } else {
        IFDEBUG IotsaSerial.println("nobacklight");
        lcd.noBacklight();
      }
#endif
  }
  String message = "<html><head><title>OLED Server</title></head><body><h1>LCD Server</h1>";
  message += "<form method='get'>Message: <input name='msg' value=''><br>\n";
  message += "Position X: <input name='x' value=''> Y: <input name='y' value=''><br>\n";
  message += "<input name='clear' type='checkbox' value='1'>Clear<br>\n";
  message += "Backlight: <input name='backlight' value=''> seconds<br>\n";
  message += "<input type='submit'></form></body></html>";
  server->send(200, "text/html", message);
  
}

String IotsaOLEDMod::info() {
  return "<p>See <a href='/display'>/display</a> to display messages or <a href='/api/display'>/api/display</a> for REST interface.</p>";
}
#endif // IOTSA_WITH_WEB

#ifdef IOTSA_WITH_API
bool IotsaOLEDMod::postHandler(const char *path, const JsonVariant& request, JsonObject& reply) {
  bool any = false;
  if (!request.is<JsonObject>()) return false;
  JsonObject& reqObj = request.as<JsonObject>();
  if (reqObj.get<bool>("clear")) {
    any = true;
#if 0
    lcd.clear();
#endif
  }
  if (reqObj.containsKey("x") || reqObj.containsKey("y")) {
    x = reqObj.get<int>("x");
    y = reqObj.get<int>("y");
#if 0
    lcd.setCursor(x, y);
#endif
    any = true;
  }
  int backlight = 5000;
  if (reqObj.containsKey("backlight")) {
    backlight = int(reqObj.get<float>("backlight") * 1000);
    any = true;
  }
  if (backlight) {
    clearTime = millis() + backlight;
    IFDEBUG IotsaSerial.println("backlight");
#if 0
    lcd.backlight();
#endif
  } else {
    IFDEBUG IotsaSerial.println("nobacklight");
#if 0
    lcd.noBacklight();
#endif
  }
  String msg = reqObj.get<String>("msg");
  if (msg != "") {
      printString(msg);
      any = true;
  }
  return any;
}
#endif // IOTSA_WITH_API

void IotsaOLEDMod::loop() {
  if (clearTime && millis() > clearTime) {
    clearTime = 0;
    IFDEBUG IotsaSerial.println("nobacklight");
#if 0
    lcd.noBacklight();
#endif
  }
}

void IotsaOLEDMod::serverSetup() {
#ifdef IOTSA_WITH_WEB
  server->on("/display", std::bind(&IotsaOLEDMod::handler, this));
#endif
#ifdef IOTSA_WITH_API
  api.setup("/api/display", false, false, true);
  name = "display";
#endif
}


void IotsaOLEDMod::printPercentEscape(String &src) {
#if 0
    const char *arg = src.c_str();
    while (*arg) {
      char newch;
      if (*arg == '+') newch = ' ';
      else if (*arg == '%') {
        arg++;
        if (*arg >= '0' && *arg <= '9') newch = (*arg-'0') << 4;
        if (*arg >= 'a' && *arg <= 'f') newch = (*arg-'a'+10) << 4;
        if (*arg >= 'A' && *arg <= 'F') newch = (*arg-'A'+10) << 4;
        arg++;
        if (*arg == 0) break;
        if (*arg >= '0' && *arg <= '9') newch |= (*arg-'0');
        if (*arg >= 'a' && *arg <= 'f') newch |= (*arg-'a'+10);
        if (*arg >= 'A' && *arg <= 'F') newch |= (*arg-'A'+10);
      } else {
        newch = *arg;
      }
      lcd.print(newch);
      x++;
      if (x >= lcd_width) {
        x = 0;
        y++;
        if (y >= lcd_height) y = 0;
        lcd.setCursor(x, y);
      }
      arg++;
    }
#endif
}

void IotsaOLEDMod::printString(String &src) {
#if 0
  if (src != "") {
    for (size_t i=0; i<src.length(); i++) {
      char newch = src.charAt(i);
      lcd.print(newch);
      x++;
      if (x >= lcd_width) {
        x = 0;
        y++;
        if (y >= lcd_height) y = 0;
        lcd.setCursor(x, y);
      }
    }
  }
#endif
}