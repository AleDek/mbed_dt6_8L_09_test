/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "PwmOut.h"
#include "mbed.h"
//#include "D6T_44L_06.h"
#include "D6T_8L_09.h"

/* thermal sensor*/
#define THERM_1_SDA PB_7
#define THERM_1_SCL PB_6
#define THERM_2_SDA PB_4
#define THERM_2_SCL PA_7

#define WAIT_TIME 500 //msec

Serial Debug(USBTX, USBRX);


DigitalOut led1(LED1);

//D6T_44L_06 tmp_16array(THERM_1_SDA, THERM_1_SCL); // SDA, SCL
//D6T_8L_09 tmp_fwd(THERM_1_SDA, THERM_1_SCL); // SDA, SCL
D6T_8L_09 tmp_8array(THERM_2_SDA, THERM_2_SCL); // SDA, SCL




int main()
{   
    //Debug.baud(115200);
    printf("hello\n");

    int16_t intbuff[8];
    float floatbuff[8];
    float chiptemp;
    
    while (true)
    {
        tmp_8array.read_float_data(floatbuff);
        chiptemp = tmp_8array.read_chip_temp();
        printf("ptat: %.2f temp: [",chiptemp);
        for(int i=0;i<8;i++){
            printf("%.2f, ",floatbuff[i]);
        }
        printf("]\n");
      
        tmp_8array.read_16bit_data(intbuff);
        chiptemp = tmp_8array.read_chip_temp();
        printf("ptat: %.2f temp: [",chiptemp);
        for(int i=0;i<8;i++){
            printf("%d, ",intbuff[i]);
        }
        printf("]\n");

        led1 = !led1;
        thread_sleep_for(WAIT_TIME);
    }
}
