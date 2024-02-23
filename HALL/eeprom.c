/*
 * eeprom.c
 *
 *  Created on: Dec 5, 2023
 *      Author: ali elnashar
 */

#include"../MCAL/TTWWII.h"

void write_eeprom(unsigned char address_eepromDEVICEandLASTbitFORwrite,unsigned char locationADDRESS_eeprom,unsigned char data_onEEPROM)
 {
	 //write
	 i2c_start();
	 i2c_write(address_eepromDEVICEandLASTbitFORwrite); //eeprom device address      0xA0
	 i2c_write(locationADDRESS_eeprom);//eeprom address register     0X01

//	 i2c_start();
//	 i2c_write(address_eepromDEVICEandLASTbitFORwrite);
	 i2c_write(data_onEEPROM);  // data
	 i2c_stop();
	 _delay_ms(50);
 }
unsigned char read_fromEEPROM(unsigned char* data,unsigned char addressDEVICEeeprom,unsigned char locationADDRESSeeprom)
{
	//unsigned char rece_data_eeprom=0;
	//read
	//*************
	i2c_start();
	i2c_write(addressDEVICEeeprom);  //last bit is to zero for write
	i2c_write(locationADDRESSeeprom);

	i2c_start();  //repeated start when read : no other master can pull line
	//within read no other master can pull line
	i2c_write(addressDEVICEeeprom|1);  //last bit is to 1 for read
	*data=i2c_read(1);  //1 is non ack that read only one byte
	i2c_stop();
	return *data;
}
