/*
 * main.h
 *
 *  Created on: 24 рту. 2016 у.
 *      Author: gray
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <stm32f0xx.h>

//--- defines ---
#define GPIO_Pin_Led1 GPIO_Pin_13	//of GPIOC
#define GPIO_Pin_Led2 GPIO_Pin_14	//of GPIOC
#define GPIO_Pin_Led3 GPIO_Pin_15	//of GPIOC
#define GPIO_Pin_Led4 GPIO_Pin_0	//of GPIOF
#define GPIO_Pin_Led5 GPIO_Pin_1	//of GPIOF

#define GPIO_Pin_KeyT GPIO_Pin_0	//of GPIOA
#define GPIO_Pin_KeyPlus GPIO_Pin_1	//of GPIOA
#define GPIO_Pin_KeyMinus GPIO_Pin_2	//of GPIOA

#define GPIO_Pin_AMP_ON GPIO_Pin_5	//of GPIOA
#define GPIO_Pin_SLEEP_SCAN GPIO_Pin_6	//of GPIOA




#endif /* MAIN_H_ */
