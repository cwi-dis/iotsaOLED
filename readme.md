# iotsaOLED - web server to drive an SSD1306 OLED display

![build-platformio](https://github.com/cwi-dis/iotsaOLED/workflows/build-platformio/badge.svg)
![build-arduino](https://github.com/cwi-dis/iotsaOLED/workflows/build-arduino/badge.svg)

iotsaDisplayServer is a web server that drives an SSD1306 OLED display. An atempt has been made to keep
it as compatible as possible with [iotsaDisplayServer](https://github.com/cwi-dis/iotsaDisplayServer).

Home page is <https://github.com/cwi-dis/iotsaOLED.
This software is licensed under the [MIT license](LICENSE.txt) by the   CWI DIS group, <http://www.dis.cwi.nl>.

## Software requirements

* Arduino IDE, v1.6 or later. Or PlatformIO.
* The iotsa framework, download from <https://github.com/cwi-dis/iotsa>.

## Hardware requirements

* a Wemos Lolin ESP32 OLED board.

## Operation

The first time the board boots it creates a Wifi network with a name similar to _config-iotsa1234_.  Connect a device to that network and visit <http://192.168.4.1>. Configure your device name (using the name _oled_ is suggested), WiFi name and password, and after reboot the iotsa board should connect to your network and be visible as <http://oled.local>.

Visit <http://oled.local/display> to show a message on the display.

Visit <http://lcd.local/buttons> to configure the URLs for the buttons. Whenever a button is pressed an _http GET_ request is sent to the corresponding URL.

There is a command-line tool (for Linux or MacOSX) in repository <https://github.com/cwi-dis/iotsaDisplayServer> file `extras/lcdecho` that allows you to show messages and control the other parameters programmatically, use

```
lcdecho --help
```

for help.