// compile: g++ -o OFController.o -I./include -c OFController.cpp
#include "../include/OFController.h"

OFColor::OFColor(): r(0),  g(0),  b(0) {}

void OFColor::setColor(const int &colorCode) {
    const int R = (colorCode >> 24) & 0xff;
    const int G = (colorCode >> 16) & 0xff;
    const int B = (colorCode >> 8) & 0xff;
    const int A = (colorCode >> 0) & 0xff;

    float r_cal, g_cal, b_cal;
    if ((R + G + B) > 0) {
        float a = A / 255.0;
        
        r_cal = (1.0) * R / (R + G + B);
        g_cal = (1.0) * G / (R + G + B);
        b_cal = (1.0) * B / (R + G + B);

        r_cal *= a * Config::OF_MAX_BRIGHTNESS;
        g_cal *= a * Config::OF_MAX_BRIGHTNESS;
        b_cal *= a * Config::OF_MAX_BRIGHTNESS; 
    }
    else {
        r = g = b = 0;
    }
    r = int(r_cal);
    g = int(g_cal);
    b = int(b_cal);

}

int OFColor::getR() { return r; }
int OFColor::getG() { return g; }
int OFColor::getB() { return b; }

OFController::OFController() {}

int OFController::init() {
    printf("I2C Hardware Initialzed\n");

    // open I2C bus
    for (int i = 0; i < Config::NUMTLC; i++) {
        err_flag[i] = true; 
        if ((fd[i] = I2CInit()) < 0) {
            fprintf(stderr, "I2C of %d init fail.\n", i);
            return 1;
        }
        // printf("File descriptor of %d opened at %d.\n", i, fd[i]);

        if (ioctl(fd[i], I2C_SLAVE, Config::TLCAddr[i]) < 0) {
            fprintf(stderr, "Failed to acquire bus access and/or talk to slave %d", i);
            return 2;
        }
    }
    return 1;
}

int OFController::sendAll(const vector<int> &statusLists) {
    unsigned char buffer[16];
    buffer[0] = 0xA2;  //Auto increment PWMx
    int counter;
    OFColor Status;
    for (int i = 0; i < Config::NUMTLC; i++) {
        counter = 0;
        if(err_flag[i] == false) {
            for (int j = i * 5; j < 5 * (i + 1); j++) {
                Status.setColor(statusLists[j]);
                buffer[counter * 3 + 1] = Status.getR();
                buffer[counter * 3 + 2] = Status.getG();
                buffer[counter * 3 + 3] = Status.getB();
                counter++;
            }
            if(write(fd[i], buffer, 16) != 16) {
                fprintf(stderr, "Failed to write to the I2C bus %x.\n", Config::TLCAddr[i]);
                err_flag[i] = true;
            }
        }
        else {
            I2C_Specified_Init(i);
            if(!err_flag[i]) {
                for(int j = i * 5; j < 5 * (i + 1); j++) {
                    Status.setColor(statusLists[j]);
                    buffer[counter * 3 + 1] = Status.getR();
                    buffer[counter * 3 + 2] = Status.getG();
                    buffer[counter * 3 + 3] = Status.getB();
                    counter++;
                }
                if(write(fd[i], buffer, 16) != 16) {
                    fprintf(stderr, "Failed to write to the I2C bus %x.\n", Config::TLCAddr[i]);
                    err_flag[i] = true;
                } 
            }
        }
    }

    return 1;
}

int OFController::I2CInit() {
    int fileI2C;
    char *filename = (char *)"/dev/i2c-1";
    if ((fileI2C = open(filename, O_RDWR)) < 0) {
        fprintf(stderr, "Failed to open i2c bus. Exit.\n");
        return -1;
    }
    return fileI2C;
}

void OFController::I2C_Specified_Init(int i) {
    if (ioctl(fd[i], I2C_SLAVE, Config::TLCAddr[i]) < 0) {
        fprintf(stderr, "Failed to acquire bus access and/or talk to slave %d", i);
    }
    unsigned char buffer[25];
    //AUTO_INCREMENT_ALL_REGISTERS
    buffer[0] = 0x80;           
    //Mode 1
    buffer[1] = 0xA0;
    //Mode 2
    buffer[2] = 0x00;
    //set PWM0-PWM15 to 0
    for(int i = 0; i < 16; i++) 
        buffer[i+3] = 0x00;
    //GRPPWM
    buffer[19] = 0x00;
    //GRPFREQ
    buffer[20] = 0x00;
    //LEDOUT setup
    for(int i = 0; i < 4; i++)
        buffer[i+21] = 0xAA;
    //Write to TLC59116F
    if (write(fd[i], buffer, 25) != 25) {
        fprintf(stderr, "Failed to write to the I2C bus %x.\n", Config::TLCAddr[i]);
    }
    else {
        err_flag[i] = false;
    }
}
