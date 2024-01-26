#ifndef OF_CONTROLLER
#define OF_CONTROLLER

#include <stdio.h>

#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

// library for PCA
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
        int fd[Config::NUMPCA];
        bool err_flag[Config::NUMPCA];
        void I2C_Specified_Init(int i);
};
#endif
