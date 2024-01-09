#ifndef OF_CONTROLLER
#define OF_CONTROLLER

#include <stdio.h>

#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

// library for TLC59116F
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "Config.h"

using namespace std;

class OFColor {
    public:
        OFColor();
        int getR();
        int getG();
        int getB();
        void setColor(const int &colorCode);
    private:
        int r, g, b;
};

class OFController {
    public:
        OFController();
        int init();
        int sendAll(const vector<int> &statusLists);
    private:
        int I2CInit();
        int fd[Config::NUMTLC];
        bool err_flag[Config::NUMPCA];
        void I2C_Specified_Init(int i);
};

#endif
