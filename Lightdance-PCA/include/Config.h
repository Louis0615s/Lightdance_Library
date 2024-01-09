#ifndef CONFIG_H
#define CONFIG_H

namespace Config {
    inline constexpr int NUMPCA = 7;                                                                                // number of PCA
    inline constexpr int PCAAddr[] = {0x1f, 0x20, 0x22, 0x23, 0x5b, 0x5c, 0x5e};                                    // PCA addresses  
    inline constexpr int OF_MAX_BRIGHTNESS = 255;                                                                   // OF led max brightness
    //Note: if the channel is not full, we should put 0 at the end of the array.                                     
    inline constexpr int WS2812_NUM_LED[] = {40, 40, 40, 40, 10, 10, 10, 10};                                       // number of led for each strip          
    inline constexpr int LED_MAX_BRIGHTNESS = 255;                                                                  // LED max brightness
}

#endif // CONFIG_H