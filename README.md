# led-strip-esp8266

### This is a simple program for an ESP8266 to control a led strip

Modes
--------
Three different modes are currently available.
* The one color mode allows you to select a simple color.
* The fade mode can be used to smoothly transition inbetween several selected colors.
* The changing colors mode switches between all selected colors.

Config
--------
esp12e:  
        ```platformio init --board esp12e```  
        ```pio lib install "arkhipenko/TaskScheduler"```  
        ```pio lib install "bblanchon/ArduinoJson"```  
        ```pio lib install "ayushsharma82/ElegantOTA"```  
        ```pio lib install "knolleary/PubSubClient"```          

Pull requests
--------
Pull requests are always welcome !

