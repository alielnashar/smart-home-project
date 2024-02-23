/*
 * eeprom.h
 *
 *  Created on: Dec 5, 2023
 *      Author: ali elnashar
 */

#ifndef HALL_EEPROM_H_
#define HALL_EEPROM_H_
#include "../MCAL/ADC.h"
#include"../HALL/LCD.h"
#include"../HALL/Keypad.h"
#include"../MCAL/TTWWII.h"
#include"../MCAL/uart.h"
#include "../MCAL/PLATFORM_TYPES.h"
#include<stdlib.h>
void write_eeprom(unsigned char address_eepromDEVICEandLASTbitFORwrite,unsigned char locationADDRESS_eeprom,unsigned char data_onEEPROM);
unsigned char read_fromEEPROM(unsigned char*data,unsigned char addressDEVICEeeprom,unsigned char locationADDRESSeeprom);


#endif /* HALL_EEPROM_H_ */
