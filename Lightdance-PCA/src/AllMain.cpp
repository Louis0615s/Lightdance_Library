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
    status.resize(5*Config::NUMPCA);

    //LED strip set up
    LEDController strip;
    vector<vector<int>> LEDstatus;
    vector<int> shape;
    int num_strip = 8;
    shape.clear();
    shape.resize(num_strip);
    for (int i = 0; i < num_strip; i++) shape[i] = 3;
    strip.init(shape); 
    LEDstatus.resize(num_strip);
    for (int i = 0; i < num_strip; i++)
	    LEDstatus[i].resize(shape[i]);

	
    while (true)
    {
	//breathe
	for (int a = 0; a <= 255; a++) //brightness increment from 0 to 255
        {
	    //OF
            for (int i = 0; i < 5 * Config::NUMPCA; i++)
            {
                if ( i%2 == 0 )
	            status[i] = 0xFFFFFF00 + a; 
		else
		    status[i] = 0xFFFFFF00 ;
	    }
	    OF.sendAll(status);
	    
	    //LED strip
            for (int i = 0; i < num_strip; i++)
	    {
                for (int j = 0; j < shape[i]; j++) 
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
		if ( i%2 == 0 )
	            status[i] = 0xFFFFFF00 + a; 
		else
		    status[i] = 0xFFFFFF00 ;
	    }
	    OF.sendAll(status);
	    
	    //LED strip
            for (int i = 0; i < num_strip; i++)
	    {
                for (int j = 0; j < shape[i]; j++)
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
