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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <speex/speex.h>
#include "voice.h"


// ----- prototypes -----------------------------------------------------------
void InitHUD(void);
void InitVoice(void);
void Speex_Init(void);
void DacInit(void);
void TimerInit(void);

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

#define FRAME_SIZE              160
#define ENCODED_FRAME_SIZE      20

// ----- variables ------------------------------------------------------------
//buffers for decoded data
__IO int16_t OUT_Buffer[2][FRAME_SIZE];
__IO int16_t *outBuffer = OUT_Buffer[0];

//decoding control
__IO uint8_t Start_Decoding = 0;

SpeexBits bits; // Holds bits so they can be read and written by the Speex routines
void *enc_state, *dec_state; // Holds the states of the encoder & the decoder
int quality = 4, complexity = 1, vbr = 0, enh = 1; // SPEEX PARAMETERS, MUST REMAINED UNCHANGED

//buffer for compressed data for decoder function
char input_bytes[ENCODED_FRAME_SIZE];

//decoded frames number
__IO uint16_t NB_Frames = 0;

#endif /* MAIN_H_ */
