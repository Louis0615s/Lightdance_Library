compile:
g++ -o OFController.o -I./include -c OFController.cpp
g++ -o LEDController.o -I./include -c LEDController.cpp
g++ AllMain.cpp LEDController.o OFController.o -lws2811 -o AllMain
sudo ./AllMain

g++ -o OFController.o -I./include -c OFController.cpp
g++ -o LEDController.o -I./include -c LEDController.cpp
g++ LightOff.cpp LEDController.o OFController.o -lws2811 -o LightOff
sudo ./LightOff
