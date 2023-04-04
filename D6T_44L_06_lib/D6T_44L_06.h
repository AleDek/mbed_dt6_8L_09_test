/*
 * mbed library program
 *  D6T-44L-06: D6T MEMS Thermal Sensors
 *  --- High Sensitivity Enables Detection of Stationary Human Presence
 *  https://www.components.omron.com/web/en/product-detail?partNumber=D6T
 *
 * Copyright (c) 2020 Kenji Arai / JH1PJL
 *  http://www7b.biglobe.ne.jp/~kenjia/
 *  https://os.mbed.com/users/kenjiArai/
 *      Created:    February  16th, 2020
 *      Revised:    February  18th, 2020
 */

/*
    Refrence documentation:
    https://omronfs.omron.com/ja_JP/ecb/products/pdf/CDSC-019.pdf

    Tested on:
        GR-MANGO(beta version) with 2JCIE-EV01 board
 */

#ifndef D6T_44L_06_H
#define D6T_44L_06_H

#include "mbed.h"

//  D6T_44L_06 Address
//  7bit address = 0x0a
#define D6T_44L_06_ADDR     (0x0a << 1)
//   D6T_44L_06 Command
#define D6T_44L_06_CMD      0x4c

/** D6T MEMS Thermal Sensors by OMRON
 *      Chip: D6T_44L_06
 *
 * @code
 * #include "mbed.h"
 *
 * // I2C Communication 
 * D6T_44L_06 tmp_16array(D14, D15); // SDA, SCL
 *
 * int main() {
 *   float f[16];
 *   while(true){
 *      tmp_16array.read_data(f);
 *      ThisThread::sleep_for(300); // minimum updating cycle
 *   }
 * }
 * @endcode
 */

class D6T_44L_06
{
public:
    /** Configure data pin (with other devices on I2C line)
      * @param I2C PinName SDA &SDL
      */
    D6T_44L_06(PinName p_sda, PinName p_scl);

    /** Configure data pin (with other devices on I2C line)
      * @param I2C previous definition
      */
    D6T_44L_06(I2C& p_i2c);

    /** Read a float type data from acc
      * @param float type of three arry's address, e.g. 16bit data dt_i[16];
      * @return CRC check result / true=passed, false=failed
      */
    bool read_16bit_data(int16_t *dt);

    /** Read a float type data from sensor
      * @param float type of three arry's address, e.g. float dt_f[16];
      * @return CRC check result / true=passed, false=failed
      */
    bool read_float_data(float *dt);

    /** Read sensor chip temperatue
      * @param none
      * @return temperature
      */
    float read_chip_temp(void);

protected:
    void initialize(void);
    bool read_data(void);
    uint8_t calc_crc(uint8_t dt);
    bool check_crc(void);

    I2C *_i2c_p;
    I2C &_i2c;

private:
    float _chip_temp;       // Sensor temperature
    char _dt[64];           // I2C buffer
    int16_t _arry[16];      // DT6T sensor raw data
    uint8_t _addr;          // sensor I2C addr

};

#endif      // D6T_44L_06_H