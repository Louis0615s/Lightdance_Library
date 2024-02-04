#ifndef CONFIG_H
#define CONFIG_H

namespace Config
{
    inline constexpr int NUMPCA = 8;                                                   // number of PCA
    inline constexpr int PCAAddr[] = {0x1f, 0x20, 0x22, 0x23, 0x5b, 0x5c, 0x5e, 0x5f}; // PCA addresses

    // OF brightness level for brightness control
    inline constexpr float OF_BRIGHTNESS_LEVEL = 255.0;
    // OF max brightness scalling factor(0.0~1.0)
    inline constexpr float OF_MAX_BRIGHTNESS_SCALING_FACTOR = 1.0;
    // OF MAX BRIGHTNESS for each channel
    inline constexpr int OF_MAX_BRIGHTNESS_R = 210;
    inline constexpr int OF_MAX_BRIGHTNESS_G = 200;
    inline constexpr int OF_MAX_BRIGHTNESS_B = 255;

    // Gamma Correction
    inline constexpr float GAMMA_OF_R = 2.65;
    inline constexpr float GAMMA_OF_G = 2.55;
    inline constexpr float GAMMA_OF_B = 2.65;

    // Note: if the channel is not full, we should put 0 at the end of the array.
    inline constexpr int WS2812_NUM_LED[] = {10, 0, 0, 0, 0, 0, 0, 0}; // number of led for each strip
    inline constexpr int LED_MAX_BRIGHTNESS = 50;                      // LED max brightness

    inline constexpr float GAMMA_LED_R = 3;
    inline constexpr float GAMMA_LED_G = 3;
    inline constexpr float GAMMA_LED_B = 3;
}

#endif // CONFIG_
       //
