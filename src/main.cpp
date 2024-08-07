#include "mbed.h"
#include "usonic.hpp"

BufferedSerial pc(USBTX, USBRX,115200);
USonic usonic(PA_7, PA_6);


int main() {

    while(1) {
        int cm = usonic.distance();
        if (cm)
        printf("distance: %d cm\n", cm);
    }
}