// compile: g++ -o OFController.o -I./include -c OFController.cpp
#include "../inc/OFController.h"

OFColor::OFColor() : r(0), g(0), b(0) {}

void OFColor::setColor(const int &colorCode)
{
    const int R = (colorCode >> 24) & 0xff;
    const int G = (colorCode >> 16) & 0xff;
    const int B = (colorCode >> 8) & 0xff;
    const int A = (colorCode >> 0) & 0xff;

    float r_cal, g_cal, b_cal;
    if ((R + G + B) > 0)
    {
        float a = A / Config::OF_BRIGHTNESS_LEVEL * Config::OF_MAX_BRIGHTNESS_SCALING_FACTOR;

        r_cal = (1.0) * R / Config::OF_BRIGHTNESS_LEVEL * a;
        g_cal = (1.0) * G / Config::OF_BRIGHTNESS_LEVEL * a;
        b_cal = (1.0) * B / Config::OF_BRIGHTNESS_LEVEL * a;

        r_cal = pow(r_cal, Config::GAMMA_OF_R);
        g_cal = pow(g_cal, Config::GAMMA_OF_G);
        b_cal = pow(b_cal, Config::GAMMA_OF_B);

        r_cal *= Config::OF_MAX_BRIGHTNESS_R;
        g_cal *= Config::OF_MAX_BRIGHTNESS_G;
        b_cal *= Config::OF_MAX_BRIGHTNESS_B;

        r = int(r_cal);
        g = int(g_cal);
        b = int(b_cal);
    }
    else
    {
        r = g = b = 0;
    }
}

int OFColor::getR() { return r; }
int OFColor::getG() { return g; }
int OFColor::getB() { return b; }

OFController::OFController() {}

int OFController::init()
{
    printf("I2C Hardware Initialzed\n");

    // open I2C bus
    for (int i = 0; i < Config::NUMPCA; i++)
    {
        err_flag[i] = true;
        if ((fd[i] = I2CInit()) < 0)
        {
            fprintf(stderr, "I2C of %d init fail.\n", i);
            return 1;
        }

        if (ioctl(fd[i], I2C_SLAVE, Config::PCAAddr[i]) < 0)
        {
            fprintf(stderr, "Failed to acquire bus access and/or talk to slave %d", i);
            return 2;
        }
    }
    return 1;
}

int OFController::sendAll(const vector<int> &statusLists)
{
    unsigned char buffer[16];
    buffer[0] = 0x88; // Auto increment PWMx
    int counter;
    OFColor Status;
    for (int i = 0; i < Config::NUMPCA; i++)
    {
        counter = 0;
        if (err_flag[i] == false)
        {
            for (int j = 0; j < 5; j++)
            {
                Status.setColor(statusLists[j]);
                // fprintf(stderr, "r: %d, g: %d, b:%d\n", Status.getR(), Status.getG(), Status.getB());
                buffer[counter * 3 + 1] = Status.getR();
                buffer[counter * 3 + 2] = Status.getG();
                buffer[counter * 3 + 3] = Status.getB();
                counter++;
            }
            if (write(fd[i], buffer, 16) != 16)
            {
                // fprintf(stderr, "Failed to write to the I2C bus %x.\n", Config::PCAAddr[i]);
                err_flag[i] = true;
            }
        }
        else
        {
            I2C_Specified_Init(i);
            if (!err_flag[i])
            {
                for (int j = i * 5; j < 5 * (i + 1); j++)
                {
                    Status.setColor(statusLists[j]);
                    buffer[counter * 3 + 1] = Status.getR();
                    buffer[counter * 3 + 2] = Status.getG();
                    buffer[counter * 3 + 3] = Status.getB();
                    counter++;
                }
                if (write(fd[i], buffer, 16) != 16)
                {
                    // fprintf(stderr, "Failed to write to the I2C bus %x.\n", Config::PCAAddr[i]);
                    err_flag[i] = true;
                }
            }
        }
    }
    return 1;
}

int OFController::I2CInit()
{
    int fileI2C;
    char *filename = (char *)"/dev/i2c-1";
    if ((fileI2C = open(filename, O_RDWR)) < 0)
    {
        fprintf(stderr, "Failed to open i2c bus. Exit.\n");
        return -1;
    }
    return fileI2C;
}

void OFController::I2C_Specified_Init(int i)
{
    if (ioctl(fd[i], I2C_SLAVE, Config::PCAAddr[i]) < 0)
    {
        fprintf(stderr, "Failed to acquire bus access and/or talk to slave %d", i);
    }
    unsigned char buffer[2];
    buffer[0] = 0x45;
    buffer[1] = 0xFF;
    if (write(fd[i], buffer, 2) != 2)
    {
        fprintf(stderr, "failed to reconnect to I2C bus %x.\n", Config::PCAAddr[i]);
    }
    else
    {
        err_flag[i] = false;
    }
}
