/*
 * LM75.c
 *
 *  Created on: Jul 5, 2023
 *      Author: User
 */
#include "LM75.h"

#define TEMP_SENSOR_ADDR 0x48 << 1
#define TEMP_REG_ADDR    0x00
#define CONF_REG_ADDR    0x01
#define THYST_REG_ADDR   0x02
#define TOS_REG_ADDR     0x03

int Check_Temperature()
{
	uint8_t rx_buffer_Temp[2];
	HAL_I2C_Mem_Read(&hi2c1, TEMP_SENSOR_ADDR, TEMP_REG_ADDR, I2C_MEMADD_SIZE_8BIT, &rx_buffer_Temp, 2, 1000);
    return rx_buffer_Temp;
}

int Check_Config()
{
	uint8_t rx_buffer_Conf;
	HAL_I2C_Mem_Read(&hi2c1, TEMP_SENSOR_ADDR, CONF_REG_ADDR, I2C_MEMADD_SIZE_8BIT, &rx_buffer_Conf, 1, 1000);
    return rx_buffer_Conf;
}

int Check_Thyst()
{
	uint8_t rx_buffer_Thyst[2];
	HAL_I2C_Mem_Read(&hi2c1, TEMP_SENSOR_ADDR, THYST_REG_ADDR, I2C_MEMADD_SIZE_8BIT, &rx_buffer_Thyst, 2, 1000);
    return rx_buffer_Thyst;
}

int Check_Tos()
{
	uint8_t rx_buffer_Tos[2];
	HAL_I2C_Mem_Read(&hi2c1, TEMP_SENSOR_ADDR, TOS_REG_ADDR, I2C_MEMADD_SIZE_8BIT, &rx_buffer_Tos, 2, 1000);
    return rx_buffer_Tos;
}

float Temp_convert_float (uint8_t *Temp_arr)
{
    float Temperature;
    //Проверка D10 0or1 +or-
    if ( (Temp_arr[0] >> 7) == 1)
    {
      Temperature = (((uint16_t)Temp_arr[0] << 3) + (Temp_arr[1] >> 5) - 2048) * 0.125;
    }
    else
    {
      Temperature = (((uint16_t)Temp_arr[0] << 3) + (Temp_arr[1] >> 5)) * 0.125;
    }
    return Temperature;
}

float TosThyst_convert_float (uint8_t *Tos_Thyst_arr)
{
    float TosThyst;
    //Проверка D8 0or1 +or-
    if ( (Tos_Thyst_arr[0] >> 7) == 1)
    {
      TosThyst = (((uint16_t)Tos_Thyst_arr[0] << 1) + (Tos_Thyst_arr[1] >> 7) - 512) * 0.5;
    }
    else
    {
      TosThyst = (((uint16_t)Tos_Thyst_arr[0] << 1) + (Tos_Thyst_arr[1] >> 7)) * 0.5;
    }
    return TosThyst;
}

void Edit_Config(uint8_t rx_buffer_Conf)
{
	HAL_I2C_Mem_Write(&hi2c1, TEMP_SENSOR_ADDR, CONF_REG_ADDR, I2C_MEMADD_SIZE_8BIT, &rx_buffer_Conf, 1, 1000);
}

void Edit_Thyst(uint8_t *rx_buffer_Thyst)
{
	HAL_I2C_Mem_Write(&hi2c1, TEMP_SENSOR_ADDR, THYST_REG_ADDR, I2C_MEMADD_SIZE_8BIT, rx_buffer_Thyst, 2, 1000);
}

void Edit_Tos(uint8_t *rx_buffer_Tos)
{
	HAL_I2C_Mem_Write(&hi2c1, TEMP_SENSOR_ADDR, TOS_REG_ADDR, I2C_MEMADD_SIZE_8BIT, rx_buffer_Tos, 2, 1000);
}

int TosThyst_convert_Regs (float TosThyst)
{
    uint8_t TosThystREG[2];
    uint16_t TosThystREGS;
    int TosThystDecimal;
    TosThystDecimal = TosThyst * 2;
    if (TosThystDecimal < 0)
    {
        TosThystREGS = TosThystDecimal + 512;
    }
    else
    {
        TosThystREGS = TosThystDecimal;
    }
    TosThystREG[0] = TosThystREGS >> 1;

    if ((TosThystREGS & 0b000000001) == 1)
    {
        TosThystREG[1] = 128;
    }
    else
    {
        TosThystREG[1] = 0;
    }

    return TosThystREG;
}

int EditCfgB0_1_2(uint8_t ConfReg, uint8_t Register012, uint8_t Value)
{
    if (Value == 0)
        ConfReg = ConfReg & ~(1 << Register012);
    if (Value == 1)
        ConfReg = ConfReg | (1 << Register012);
    return ConfReg;
}

int EditCfgB4_3(uint8_t ConfReg, uint8_t Value)
{
    if (Value == 0)
    {
        ConfReg = ConfReg & ~(1 << 3);
        ConfReg = ConfReg & ~(1 << 4);
    }
    if (Value == 1)
    {
        ConfReg = ConfReg | (1 << 3);
        ConfReg = ConfReg & ~(1 << 4);
    }
    if (Value == 2)
    {
        ConfReg = ConfReg & ~(1 << 3);
        ConfReg = ConfReg | (1 << 4);
    }
    if (Value == 3)
    {
        ConfReg = ConfReg | (1 << 3);
        ConfReg = ConfReg | (1 << 4);
    }
    return ConfReg;
}
