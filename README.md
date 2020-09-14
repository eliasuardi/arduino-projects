# ARDUINO README

## Shift Out Register - 74HC595

Shift out register is used to expand the number of arduino output pins.
It is possible to connect multiple registers in series.

**Project reference** <br/>
[projects/shift_out_register](projects/shift_out_register)

**Video** <br/>
https://www.youtube.com/watch?v=Ys2fu4NINrA&t=1355s

**Images**

* [Pin Description](images/shift_registers/so_pin_description.png)

* [Breadboard + Arduino](images/shift_registers/so_pins_1.jpg)

* [Breadboard closeup](images/shift_registers/so_pins_2.jpg)

* [Arduino](images/shift_registers/so_pins_3.jpg)

**Useful Info**

* Powered with 5 volts

* used 220 ohm resistor for each led


## Shift In Register - 74HC165

Shfit in register is used to expand the number of arduino input pins. Can connect multiple shift registers in series.

**Project reference** <br/>
[projects/shift_in_register](projects/shift_in_register)

**Video** <br/>
https://www.youtube.com/watch?v=Ys2fu4NINrA&t=1355s

**Images**

* [Pin Description](images/shift_registers/si_pin_description.png)

* [Breadboard + Arduino](images/shift_registers/si_pins_1.png)

* [Arduino](images/shift_registers/si_pins_2.jpg)

**Extras**

* Project that integrates both shift registers: [projects/shift_in_shift_out](projects/shift_in_shift_out)

**Useful Info**

* Powered with 5 volts

* Used 10k ohm resistor for each push button

## ESP8266-01

The ESP8266 module is used to connect Arduino to the internet. Particular thing is that it has its own flash in which a sketch is uploaded.

**Project References**

* [projects/esp_wifi_connection](projects/esp_wifi_connection) : simple project for esp connection to wifi

* [projects/esp_web_client](projects/esp_web_client) : use esp as web client

* [projects/esp_web_server](projects/esp_web_server) : use esp as web server

**Websites**

* [Flashing ESP8266](https://cordobo.com/2300-flash-esp8266-01-with-arduino-uno/)

* [ESP8266 Wiki](https://github.com/esp8266/esp8266-wiki)


**Images**

* [Pin Description](images/esp8266/esp8266_pin_description.png)

* [Pin Connections](images/esp8266/esp8266_pinout.png)

**Useful Info**

* In order to build sketches for the ESP8266 module follow these steps

  1. Add the following url to the *Arduino Preferences > Additional Boards Manager URLs*: <br/> https://arduino.esp8266.com/stable/package_esp8266com_index.json
  
  2. Open the Boards Manager in *Tools > Board > Boards Manager...* and install the **esp8266** board
  
  3. Before building the sketch select *Generic ESP8266 Module* under *Tools > Board*
  
* In order to reset the module the **RESET** pin of the module must be temporarily connected to **GROUND**. An efficient way is to insert a push button between the **RESET** pin and **GROUND**.


**Important**

* **Before uploading any sketch to the module make sure that a blank sketch is running on the Arduino**.

* The ESP8266 module runs on 3.3V but the TX and RX pins on the Arduino run on 5V so it is very important to use a voltage divider (3 resistors in series) as shown in the *Pin Connections* image.

* GPIO-0 pin must be connected to ground in order upload a sketch to the module. Remove this connection for normal execution.









