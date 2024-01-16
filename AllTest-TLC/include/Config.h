#ifndef CONFIG_H
#define CONFIG_H

namespace Config {
    inline constexpr int NUMTLC = 12;                                                                               // number of TLC59116(F)
    inline constexpr int TLCAddr[] = {0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x69, 0x6A, 0x6C, 0x6D };     // TLC59116(F) addresses  
    inline constexpr int OF_MAX_BRIGHTNESS = 255;                                                                   // OF led max brightness
    //Note: if the channel is not full, we should put 0 at the end of the array.                                     
    inline constexpr int WS2812_NUM_LED[] = {40, 40, 40, 40, 10, 10, 10, 10};                                       // number of led for each strip          
    inline constexpr int LED_MAX_BRIGHTNESS = 255;                                                                  // LED max brightness
}

#endif // CONFIG_H