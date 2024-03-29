// compile: g++ AllMain.cpp LEDController.o OFController.o -lws2811 -o test
#include <iostream>
#include <cstdint>
#include <vector>
using namespace std;

#include "../include/LEDController.h"
#include "../include/OFController.h"

int main() {
    OFController OF;
    LEDController strip;
    vector<vector<int>> LEDstatus;
    vector<int> status;

    OF.init();
    strip.init();

    status.resize(5*Config::NUMTLC);
    LEDstatus.resize(strip.num_channel);
    for (int i = 0; i < strip.num_channel; i++)
	    LEDstatus[i].resize(Config::WS2812_NUM_LED[i]);

    while(true) {
        for(int a = 1; a <= 255 ; a++) {
            for (int i = 0; i < 5*Config::NUMTLC; i++) {
                status[i] = 0xFF000000 + a;
            }
            for(int i = 0; i < strip.num_channel; i++)
	            for(int j = 0; j < Config::WS2812_NUM_LED[i]; j++)	
                    LEDstatus[i][j] = 0xFF000000 + a;
            strip.sendAll(LEDstatus);
            OF.sendAll(status);
            usleep(100);
        }

        for(int a = 255; a >= 1 ; a--) {
            for(int i = 0; i < 5*Config::NUMTLC; i++) {
                status[i] = 0xFF000000 + a;
            }
            for(int i = 0; i < strip.num_channel; i++)
	            for(int j = 0; j < Config::WS2812_NUM_LED[i]; j++)	
                    LEDstatus[i][j] = 0xFF000000 + a;
            strip.sendAll(LEDstatus);
            OF.sendAll(status);
            usleep(100);
        }
        for(int a = 1; a <= 255 ; a++) {
            for(int i = 0; i < 5*Config::NUMTLC; i++) {
                status[i] = 0x00FF0000 + a;
            }
            for(int i = 0; i < strip.num_channel; i++)
	            for(int j = 0; j < Config::WS2812_NUM_LED[i]; j++)	
                    LEDstatus[i][j] = 0x00FF0000 + a;
            strip.sendAll(LEDstatus);
            OF.sendAll(status);
            usleep(100);
        }
        for(int a = 255; a >= 1 ; a--) {
            for(int i = 0; i < 5*Config::NUMTLC; i++) {
                status[i] = 0x00FF0000 + a;
            }
            for(int i = 0; i < strip.num_channel; i++)
	            for(int j = 0; j < Config::WS2812_NUM_LED[i]; j++)	
                    LEDstatus[i][j] = 0x00FF0000 + a;
            strip.sendAll(LEDstatus);
            OF.sendAll(status);
            usleep(100);
        }
        for(int a = 1; a <= 255 ; a++) {
            for(int i = 0; i < 5*Config::NUMTLC; i++) {
                status[i] = 0x0000FF00 + a;
            }
            for(int i = 0; i < strip.num_channel; i++)
	            for(int j = 0; j < Config::WS2812_NUM_LED[i]; j++)	
                    LEDstatus[i][j] = 0x0000FF00 + a;
            strip.sendAll(LEDstatus);
            OF.sendAll(status);
            usleep(100);
        }

        for(int a = 255; a >= 1 ; a--) {
            for(int i = 0; i < 5*Config::NUMTLC; i++) {
                status[i] = 0x0000FF00 + a;
            }
            for(int i = 0; i < strip.num_channel; i++)
	            for(int j = 0; j < Config::WS2812_NUM_LED[i]; j++)	
                    LEDstatus[i][j] = 0x0000FF00 + a;
            strip.sendAll(LEDstatus);
            OF.sendAll(status);
        usleep(100);
        }
    }
    strip.finish();
    return 0;
}
