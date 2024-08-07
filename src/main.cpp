#include "mbed.h"
#include "usonic.hpp"

BufferedSerial pc(USBTX, USBRX,115200);
USonic usonic(PA_7, PA_6);
CAN can(PA_11, PA_12, (int)1e6);
CANMessage msg;
int16_t output[4] = {0};
int gain = 600;


int main() {
    int goal = 5;

    while(1) {
        int pos;
        int cm = usonic.distance();
        if (cm){
        pos = cm;
        
}

        
        output[0] = (pos - goal) * gain;
        printf("distance: %d cm, output: %d\n", pos,output[0]);
        CANMessage msg(4, (const uint8_t *)output, 8); //メッセージ構築
        can.write(msg); //CAN送信
    }
}