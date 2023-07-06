/*
 * LM75.h
 *
 *  Created on: Jul 5, 2023
 *      Author: User
 */

#ifndef INC_LM75_H_
#define INC_LM75_H_

#include "i2c.h"

int Check_Temperature();

int Check_Config();

int Check_Thyst();

int Check_Tos();

float Temp_convert_float (uint8_t *Temp_arr);

float TosThyst_convert_float (uint8_t *Tos_Thyst_arr);

void Edit_Config(uint8_t rx_buffer_Conf);

void Edit_Thyst(uint8_t *rx_buffer_Thyst);

void Edit_Tos(uint8_t *rx_buffer_Tos);

int TosThyst_convert_Regs (float TosThyst);

int EditCfgB0_1_2(uint8_t ConfReg, uint8_t Register012, uint8_t Value);

int EditCfgB4_3(uint8_t ConfReg, uint8_t Value);


#endif /* INC_LM75_H_ */
