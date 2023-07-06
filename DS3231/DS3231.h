/*
 * DS3231.h
 *
 *  Created on: Jul 5, 2023
 *      Author: User
 */

#ifndef INC_DS3231_H_
#define INC_DS3231_H_

#include "i2c.h"

int DS3231_Read_0_6(uint8_t RegAddr);

void DS3231_Write_0_6(uint8_t RegAddr,uint8_t tx_buffer);

uint8_t DS3231_ConvertFromReg(uint8_t c);

uint8_t DS3231_ConvertToBin(uint8_t c);

int DS3231_Read_Seconds ();

int DS3231_Read_Minutes ();

int DS3231_Read_Hours ();

int DS3231_Read_Day ();

int DS3231_Read_Date ();

int DS3231_Read_Month ();

int DS3231_Read_Year ();

void DS3231_Write_Seconds (uint8_t Value);

void DS3231_Write_Minutes (uint8_t Value);

void DS3231_Write_Hours (uint8_t Value);

void DS3231_Write_Day (uint8_t Value);

void DS3231_Write_Date (uint8_t Value);

void DS3231_Write_Month (uint8_t Value);

void DS3231_Write_Year (uint8_t Value);

#endif /* INC_DS3231_H_ */
