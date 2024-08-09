#include "mbed.h"
#include "usonic.hpp"


BufferedSerial pc(USBTX, USBRX,115200);
USonic usonic(PA_7, PA_6);
CAN can(PA_11, PA_12, (int)1e6);
CANMessage msg;
int16_t output[4] = {0};
float gain[3] = {700, 0.01, 100};

int clamp(int value, int min, int max) {
    if (value < min) {
        return min;
    } else if (value > max) {
        return max;
    } else {
        return value;
    }
}


int main() {
    int goal = 15;
    int pre_error = 0;
    int integral = 0;

    while(1) {
        int pos;
        int cm = usonic.distance();
        if (cm){
        pos = cm;
        }
        int error = (pos - goal);
        integral += error;
        int deriv = error - pre_error;
        output[0] = error * gain[0] + integral * gain[1] + deriv * gain[2];
        output[0] = clamp(output[0], -16000, 16000);
        pre_error = error;

        printf("distance: %d cm, output: %d\n", pos,output[0]);
        CANMessage msg(4, (const uint8_t *)output, 8); //メッセージ構築
        can.write(msg); //CAN送信
    }
}