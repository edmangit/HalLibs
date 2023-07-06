/*
 * DS3231.c
 *
 *  Created on: Jul 5, 2023
 *      Author: User
 */
#include "DS3231.h"

#define DS3231_ADDR      0x68 << 1
#define Seconds_REG_ADDR 0x00
#define Minutes_REG_ADDR 0x01
#define Hours_REG_ADDR   0x02
#define Day_REG_ADDR     0x03
#define Date_REG_ADDR    0x04
#define Month_REG_ADDR   0x05
#define Year_REG_ADDR    0x06

int DS3231_Read_0_6(uint8_t RegAddr)
{
	uint8_t rx_buffer;
	HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDR, RegAddr, I2C_MEMADD_SIZE_8BIT, &rx_buffer, 1, 1000);
    return rx_buffer;
}

void DS3231_Write_0_6(uint8_t RegAddr,uint8_t tx_buffer)
{
	HAL_I2C_Mem_Write(&hi2c1, DS3231_ADDR, RegAddr, I2C_MEMADD_SIZE_8BIT, &tx_buffer, 1, 1000);
}

uint8_t DS3231_ConvertFromReg(uint8_t c)
{
  uint8_t ch = ((c>>4)*10+(0x0F&c));
        return ch;
}

uint8_t DS3231_ConvertToBin(uint8_t c)
{
        uint8_t ch = ((c/10)<<4)|(c%10);
        return ch;
}

int DS3231_Read_Seconds ()
{
	return DS3231_ConvertFromReg(DS3231_Read_0_6(Seconds_REG_ADDR));
}

int DS3231_Read_Minutes ()
{
	return DS3231_ConvertFromReg(DS3231_Read_0_6(Minutes_REG_ADDR));
}

int DS3231_Read_Hours ()
{
	return DS3231_ConvertFromReg(DS3231_Read_0_6(Hours_REG_ADDR));
}

int DS3231_Read_Day ()
{
	return DS3231_ConvertFromReg(DS3231_Read_0_6(Day_REG_ADDR));
}

int DS3231_Read_Date ()
{
	return DS3231_ConvertFromReg(DS3231_Read_0_6(Date_REG_ADDR));
}

int DS3231_Read_Month ()
{
	return DS3231_ConvertFromReg(DS3231_Read_0_6(Month_REG_ADDR));
}

int DS3231_Read_Year ()
{
	return DS3231_ConvertFromReg(DS3231_Read_0_6(Year_REG_ADDR));
}

void DS3231_Write_Seconds (uint8_t Value)
{
	DS3231_Write_0_6(Seconds_REG_ADDR, DS3231_ConvertToBin(Value));
}

void DS3231_Write_Minutes (uint8_t Value)
{
	DS3231_Write_0_6(Minutes_REG_ADDR, DS3231_ConvertToBin(Value));
}

void DS3231_Write_Hours (uint8_t Value)
{
	DS3231_Write_0_6(Hours_REG_ADDR, DS3231_ConvertToBin(Value));
}

void DS3231_Write_Day (uint8_t Value)
{
	DS3231_Write_0_6(Day_REG_ADDR, DS3231_ConvertToBin(Value));
}

void DS3231_Write_Date (uint8_t Value)
{
	DS3231_Write_0_6(Date_REG_ADDR, DS3231_ConvertToBin(Value));
}

void DS3231_Write_Month (uint8_t Value)
{
	DS3231_Write_0_6(Month_REG_ADDR, DS3231_ConvertToBin(Value));
}

void DS3231_Write_Year (uint8_t Value)
{
	DS3231_Write_0_6(Year_REG_ADDR, DS3231_ConvertToBin(Value));
}
