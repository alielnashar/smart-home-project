/*
 * main_config.h
 *
 *  Created on: Feb 15, 2024
 *      Author: ali elnashar
 */

#ifndef APP_MAIN_CONFIG_H_
#define APP_MAIN_CONFIG_H_

#include "../MCAL/ADC.h"
#include"../HALL/LCD.h"
#include"../HALL/Keypad.h"
#include"../MCAL/TTWWII.h"
#include"../MCAL/uart.h"
#include "../MCAL/PLATFORM_TYPES.h"
#include<stdlib.h>
#define key_not_pressed  0
#define user_mode '2'
#define admin_mode '1'
#define max_name_length  4
#define pass_length 4
//Admin Addresses
#define name_address_ad (unsigned char)0x02
#define pass_address_ad (unsigned char)0x06
//Users Addresses
#define pass_address_u1 (unsigned char)0x0E
#define name_address_u1 (unsigned char)0x0A
#define users_address_add (unsigned char)0x00
#define remove_sign (unsigned char)0xFF
#define led_status_ad (unsigned char)0x80
#define led_status_u (unsigned char)0x41
#define max_trials (3)

#endif /* APP_MAIN_CONFIG_H_ */
