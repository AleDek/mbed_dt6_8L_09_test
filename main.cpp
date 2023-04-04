/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "PwmOut.h"
#include "mbed.h"
#include "D6T_44L_06.h"
#include "D6T_8L_09.h"

/* thermal sensor*/
#define THERM_1_SDA PB_7
#define THERM_1_SCL PB_6
#define THERM_2_SDA PB_4
#define THERM_2_SCL PA_7

#define WAIT_TIME 50 //msec

Serial Debug(USBTX, USBRX);


DigitalOut led1(LED1);

//D6T_44L_06 tmp_16array(THERM_1_SDA, THERM_1_SCL); // SDA, SCL
//D6T_8L_09 tmp_8array(THERM_1_SDA, THERM_1_SCL); // SDA, SCL

I2C i2c(THERM_1_SDA, THERM_1_SCL);  

int ack;   
int address;  
void scanI2C() {
  for(address=1;address<127;address++) {    
    ack = i2c.write(address, "11", 1);
    if (ack == 0) {
        printf("hello\n");
       printf("\tFound at %3d -- %3x\r\n", address,address);
    }    
    wait(0.05);
  } 
}


int main()
{   
    //Debug.baud(115200);

    

    while (true)
    {
        led1 = !led1;
        //servo1.pulsewidth(0.0015);
        printf("hello\n");
        scanI2C();
        printf("hello\n");
        //tmp_8array.read_chip_temp();
        thread_sleep_for(WAIT_TIME);
    }
}
