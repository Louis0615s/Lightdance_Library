#ifndef CONFIG_H
#define CONFIG_H

namespace Config {
    inline constexpr int NUMPCA = 7;                                                                                // number of PCA
    inline constexpr int PCAAddr[] = {0x1f, 0x20, 0x22, 0x23, 0x5b, 0x5c, 0x5e};                                    // PCA addresses  
    
    //OF brightness level for brightness control
    inline constexpr int OF_BRIGHTNESS_LEVEL = 255;
    //OF max brightness scalling factor(0.0~1.0)
    inline constexpr float OF_MAX_BRIGHTNESS_SCALING_FACTOR = 1.0; 
    //OF MAX BRIGHTNESS for each channel
    inline constexpr int OF_MAX_BRIGHTNESS_R = 255;
    inline constexpr int OF_MAX_BRIGHTNESS_G = 255;
    inline constexpr int OF_MAX_BRIGHTNESS_B = 255;
    
    //Gamma Correction
    inline constexpr float GAMMA_R = 2.2;
    inline constexpr float GAMMA_G = 2.2;
    inline constexpr float GAMMA_B = 2.2;

    //Note: if the channel is not full, we should put 0 at the end of the array.                                     
    inline constexpr int WS2812_NUM_LED[] = {40, 40, 40, 40, 10, 10, 10, 10};                                       // number of led for each strip          
    inline constexpr int LED_MAX_BRIGHTNESS = 255;                                                                  // LED max brightness
}

#endif // CONFIG_H