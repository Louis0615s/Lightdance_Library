// compile: g++ -o LEDController.o -I./include -c LEDController.cpp
#include "../inc/LEDController.h"

// LEDColor
LEDColor::LEDColor() : r(0), g(0), b(0), rgb(0) {}
void LEDColor::setColor(const int &colorCode) {
    const int R = (colorCode >> 24) & 0xff;
    const int G = (colorCode >> 16) & 0xff;
    const int B = (colorCode >> 8) & 0xff;
    const int A = (colorCode >> 0) & 0xff;

    float r_cal, g_cal, b_cal;
    if ((R + G + B) > 0) {
        float a = A / 255.0;
        
        r_cal = (1.0) * (R / 255.0) * a;
        g_cal = (1.0) * (G / 255.0) * a;
        b_cal = (1.0) * (B / 255.0) * a;

	r_cal = pow(r_cal, Config::GAMMA_LED_R);
	g_cal = pow(g_cal, Config::GAMMA_LED_G);
	b_cal = pow(b_cal, Config::GAMMA_LED_B);

        r_cal *= Config::LED_MAX_BRIGHTNESS;
        g_cal *= Config::LED_MAX_BRIGHTNESS;
        b_cal *= Config::LED_MAX_BRIGHTNESS; 
	r = int(r_cal);
    	g = int(g_cal);
    	b = int(b_cal);
    	rgb = (r << 16) + (g << 8) + b;
    }
    else {
        r = g = b = 0;
	rgb = 0;
    }
    
}
uint32_t LEDColor::getRGB() { return rgb; }

// LEDController
LEDController::LEDController() {
    num_channel = 0;
}
int LEDController::init(const std::vector<int> &shape) {
    close_gpio();
    
    // initialize WS2812B
    ws2811_return_t ret;
    for (int i = 0; i < num_channel; i++) {
	ledString[i].channel[0].count = shape[i];
        if ((ret = ws2811_init(&ledString[i])) != WS2811_SUCCESS) {
            fprintf(stderr, "ws2811_init %d failed: %s\n", i, ws2811_get_return_t_str(ret));
            return ret;
        }
    }
    // initialize GPIO_PIN
    gpioInit();
    for (int i = 0; i < num_channel; i++) {
        //let all LEDs off
        select_channel(i);
        for (int j = 0; j < ledString[i].channel[0].count; j++) {
            ledString[i].channel[0].leds[j] = 0;                                            
        }
        //render 
        if ((ret = ws2811_render(&ledString[i])) != WS2811_SUCCESS) {                           
            fprintf(stderr, "ws2811_render %d failed: %s\n", i, ws2811_get_return_t_str(ret));
            return ret;
        }
        usleep(ledString[i].channel[0].count * 30);
    }
    return WS2811_SUCCESS;
}
int LEDController::sendAll(const std::vector<std::vector<int>> &statusLists) {
    // Check if data size is consistent with stored during initialization
    for (int i = 0; i < num_channel; i++) {
        if (statusLists[i].size() > ledString[i].channel[0].count) {
            fprintf(stderr, "Error: Strip %d is longer then init settings: %d\n", (int)statusLists[i].size(), ledString[i].channel[0].count);
            return -1;
        }
    }
    // Push data to LED strips
    play(statusLists);
    return 0;
}
int LEDController::play(const std::vector<std::vector<int>> &statusLists) {
    ws2811_return_t ret;
    LEDColor led;
    for (int i = 0; i < num_channel; i++) {
        select_channel(i);
        for (int j = 0; j < ledString[i].channel[0].count; j++) {
            led.setColor(statusLists[i][j]);
            ledString[i].channel[0].leds[j] = led.getRGB();
        }

        if ((ret = ws2811_render(&ledString[i])) != WS2811_SUCCESS) {
            fprintf(stderr, "ws2811_render %d failed: %s\n", i, ws2811_get_return_t_str(ret));
            return ret;
        }
        usleep(ledString[i].channel[0].count * 30);
    }
    return 0;
}
void LEDController::gpioInit() {
    int fd_export = open("/sys/class/gpio/export", O_WRONLY);

    if (fd_export == -1) {
        perror("Unable to open /sys/class/gpio/export");
        exit(1);
    }

    if (write(fd_export, "23", 2) != 2) {
        perror("Error writing to /sys/class/gpio/export");
        exit(1);
    }

    if (write(fd_export, "24", 2) != 2) {
        perror("Error writing to /sys/class/gpio/export");
        exit(1);
    }

    if (write(fd_export, "25", 2) != 2) {
        perror("Error writing to /sys/class/gpio/export");
        exit(1);
    }

    close(fd_export);

    // Set the pin to be an output by writing "out" to
    // /sys/class/gpio/gpio24/direction

    int fd = open("/sys/class/gpio/gpio23/direction", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio23/direction");
        exit(1);
    }

    if (write(fd, "out", 3) != 3) {
        perror("Error writing to /sys/class/gpio/gpio23/direction");
        exit(1);
    }

    close(fd);

    // Set the pin to be an output by writing "out" to
    // /sys/class/gpio/gpio24/direction

    fd = open("/sys/class/gpio/gpio24/direction", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio24/direction");
        exit(1);
    }

    if (write(fd, "out", 3) != 3) {
        perror("Error writing to /sys/class/gpio/gpio24/direction");
        exit(1);
    }

    close(fd);

    // Set the pin to be an output by writing "out" to
    // /sys/class/gpio/gpio24/direction

    fd = open("/sys/class/gpio/gpio25/direction", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio25/direction");
        exit(1);
    }

    if (write(fd, "out", 3) != 3) {
        perror("Error writing to /sys/class/gpio/gpio25/direction");
        exit(1);
    }

    close(fd);

    A0 = open("/sys/class/gpio/gpio23/value", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio23/value");
        exit(1);
    }

    A1 = open("/sys/class/gpio/gpio24/value", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio24/value");
        exit(1);
    }

    A2 = open("/sys/class/gpio/gpio25/value", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio25/value");
        exit(1);
    }
}
void LEDController::select_channel(int channel) {
    switch (channel) {
        case 0:
            if (write(A0, "0", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio23/value");
                exit(1);
            }
            if (write(A1, "0", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio24/value");
                exit(1);
            }
            if (write(A2, "0", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio25/value");
                exit(1);
            }
            break;
        case 1:
            if (write(A0, "1", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio23/value");
                exit(1);
            }
            if (write(A1, "0", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio24/value");
                exit(1);
            }
            if (write(A2, "0", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio25/value");
                exit(1);
            };
            break;
        case 2:
            if (write(A0, "0", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio23/value");
                exit(1);
            }
            if (write(A1, "1", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio24/value");
                exit(1);
            }
            if (write(A2, "0", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio25/value");
                exit(1);
            }
            break;
        case 3:
            if (write(A0, "1", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio23/value");
                exit(1);
            }
            if (write(A1, "1", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio24/value");
                exit(1);
            }
            if (write(A2, "0", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio25/value");
                exit(1);
            }
            break;
        case 4:
            if (write(A0, "0", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio23/value");
                exit(1);
            }
            if (write(A1, "0", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio24/value");
                exit(1);
            }
            if (write(A2, "1", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio25/value");
                exit(1);
            };
            break;
        case 5:
            if (write(A0, "1", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio23/value");
                exit(1);
            }
            if (write(A1, "0", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio24/value");
                exit(1);
            }
            if (write(A2, "1", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio25/value");
                exit(1);
            };
            break;
        case 6:
            if (write(A0, "0", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio23/value");
                exit(1);
            }
            if (write(A1, "1", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio24/value");
                exit(1);
            }
            if (write(A2, "1", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio25/value");
                exit(1);
            }
            break;
        case 7:
            if (write(A0, "1", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio23/value");
                exit(1);
            }
            if (write(A1, "1", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio24/value");
                exit(1);
            }
            if (write(A2, "1", 1) != 1) {
                perror("Error writing to /sys/class/gpio/gpio25/value");
                exit(1);
            }
            break;
    }
}
void LEDController::finish() {
    for (int i = 0; i < num_channel; i++) ws2811_fini(&ledString[i]);
    printf("LED GPIO finished.\n");
    close(A0);
    close(A1);
    close(A2);
}
void LEDController::close_gpio() {
    int fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/unexport");
        exit(1);
    }

    if (write(fd, "23", 2) != 2) {
        fprintf(stderr, "Error writing to /sys/class/gpio/unexport: 23\n");
    }

    if (write(fd, "24", 2) != 2) {
        fprintf(stderr, "Error writing to /sys/class/gpio/unexport: 24\n");
    }

    if (write(fd, "25", 2) != 2) {
        fprintf(stderr, "Error writing to /sys/class/gpio/unexport: 25\n");
    }
}
