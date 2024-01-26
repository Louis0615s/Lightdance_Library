// compile: g++ AllMain.cpp LEDController.o OFController.o -lws2811 -o test
#include <iostream>
#include <cstdint>
#include <vector>
using namespace std;

#include "../include/LEDController.h"
#include "../include/OFController.h"

int main()
{
    //Optical Fiber (OF) Set Up
    OFController OF;
    vector<int> status;
    OF.init();
    status.resize(5 * Config::NUMPCA);

    //LED strip set up
    vector<vector<int>> LEDstatus;
    LEDController strip;
    strip.init();
    LEDstatus.resize(strip.num_channel);
    for (int i = 0; i < strip.num_channel; i++)
        LEDstatus[i].resize(Config::WS2812_NUM_LED[i]);

	
    while (true)
    {
	//breathe
	for (int a = 0; a <= 255; a++) //brightness increment from 0 to 255
        {
	    //OF
            for (int i = 0; i < 5 * Config::NUMPCA; i++)
            {
                if ( i%2 == 1 )
	            status[i] = 0xFF000000 + a; 
		else
		    status[i] = 0xFFFFFF00 ;
	    }
	    OF.sendAll(status);
	    
	    //LED strip
            for (int i = 0; i < strip.num_channel; i++)
	    {
                for (int j = 0; j < Config::WS2812_NUM_LED[i]; j++) 
	        {
                    LEDstatus[i][j] = 0xFFFFFF00 + a;
		}
	    }
            strip.sendAll(LEDstatus);

            sleep(1/256); //sleep(<total time (sec)> / <range of a>)
        }

	sleep(1); //delay time when light up
      
	for (int a = 255; a >= 0; a--) //brightness decrement from 255 to 0
        {
	    //OF
            for (int i = 0; i < 5 * Config::NUMPCA; i++)
	    {
		if ( i%2 == 1 )
	            status[i] = 0xFF000000 + a; 
		else
		    status[i] = 0xFFFFFF00 ;
	    }
	    OF.sendAll(status);
	    
	    //LED strip
            for (int i = 0; i < strip.num_channel; i++)
	    {
                for (int j = 0; j < Config::WS2812_NUM_LED[i]; j++)
		{
                    LEDstatus[i][j] = 0xFFFFFF00 + a;
		}
	    }
            strip.sendAll(LEDstatus);
            
            sleep(1/256); //sleep(<total time (sec)> / <range of a>)
        }

	sleep(1); //delay time when light off
    }
    strip.finish();
    return 0;
}
