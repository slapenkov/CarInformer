#include "main.h"

// ----- main() ---------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int main(int argc, char* argv[]) {
	//Clock reconfigure

	// At this stage the system clock should have already been configured
	// at high speed.

	InitHUD();
	InitVoice();

	//debug
	//GPIO_SetBits(GPIOC, GPIO_Pin_Led1);
	//GPIO_SetBits(GPIOC, GPIO_Pin_Led2);
	//GPIO_SetBits(GPIOC, GPIO_Pin_Led3);
	//GPIO_SetBits(GPIOF, GPIO_Pin_Led4);
	//GPIO_SetBits(GPIOF, GPIO_Pin_Led5);
	//GPIO_SetBits(GPIOA, GPIO_Pin_SLEEP_SCAN);
	//GPIO_SetBits(GPIOA, GPIO_Pin_AMP_ON);

	// Infinite loop
	while (1) {
		// Add your code here.
		play_message(&male_voice[0], male_voice_frames);
		GPIO_WriteBit(GPIOC, GPIO_Pin_Led1,
				~GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_Led1)); //toggle of led 1
	}
}

// ------ IRQ Handlers --------------------------------------------------------

/**
 * @brief  This function handles TIM2 interrupt request.
 * @param  None
 * @retval : None
 */
void TIM2_IRQHandler(void) {
	TIM2->SR &= ~TIM_SR_UIF; //clear interrupt flag

	uint16_t tmp;
	//Read values from current buffer
	//decreasing its bits number and add 512 for signed value
	tmp = (uint16_t) (((*outBuffer >> 5)) + 0x200);
	DAC_SetChannel1Data(DAC_Align_12b_R, tmp);

	//If current buffer ends, change buffer pointer
	//and start to decode of data
	if (outBuffer == &OUT_Buffer[1][159]) {
		outBuffer = OUT_Buffer[0];
		Start_Decoding = 2;
	} else if (outBuffer == &OUT_Buffer[0][159]) {
		outBuffer++;
		Start_Decoding = 1;
	} else {
		outBuffer++;
	}

}

// ------ implementations -----------------------------------------------------
void InitHUD(void) {
	//configure ports
	RCC_AHBPeriphClockCmd(
			RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC
					| RCC_AHBPeriph_GPIOF, ENABLE); //enable ports clock

	GPIO_InitTypeDef gpio;

	//Port A
	//Keys
	gpio.GPIO_Pin = GPIO_Pin_KeyT | GPIO_Pin_KeyPlus | GPIO_Pin_KeyMinus;
	gpio.GPIO_Mode = GPIO_Mode_IN;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &gpio); //init port A Leds

	//AMP_ON & SLEEP_SCAN
	gpio.GPIO_Pin = GPIO_Pin_AMP_ON | GPIO_Pin_SLEEP_SCAN;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &gpio);

	//Port C
	gpio.GPIO_Pin = GPIO_Pin_Led1 | GPIO_Pin_Led2 | GPIO_Pin_Led3
			| GPIO_Pin_Led4 | GPIO_Pin_Led5;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &gpio);

}

void InitVoice(void) {
	//configure voice peripherals
	DacInit();
	TimerInit();

	//init codec
	Speex_Init();
}

//DAC init
void DacInit(void) {
	DAC_InitTypeDef DAC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	uint16_t tmp = 0;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);

	/* Enable DAC Channel1: Once the DAC channel1 is enabled, PA.04 is
	 automatically connected to the DAC converter. */
	DAC_Cmd(DAC_Channel_1, ENABLE);
	DAC_SetChannel1Data(DAC_Align_8b_R, tmp);
}

//Timer Init
void TimerInit(void) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	/* TIM2 configuration -------------------------------------------------------*/
	TIM_DeInit(TIM2);
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	/* TIM2 used for timing, the timing period depends on the sample rate */
	TIM_TimeBaseStructure.TIM_Prescaler = 0x00;
	TIM_TimeBaseStructure.TIM_Period = 3000; // 24M/8k
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	/* Output Compare Inactive Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Inactive;
	TIM_OCInitStructure.TIM_Pulse = 0x0;
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	NVIC_SetPriority(TIM2_IRQn, 15);
	NVIC_EnableIRQ(TIM2_IRQn);

	TIM_Cmd(TIM2, ENABLE);
}

//Speex decoder init
void Speex_Init(void) {
	speex_bits_init(&bits);

	/* speex decoding initialization */
	dec_state = speex_decoder_init(&speex_nb_mode);
	speex_decoder_ctl(dec_state, SPEEX_SET_ENH, &enh);

}

// @brief Play speex message
// @param array - voice data array
// @param frame_number - number of frames
void play_message(unsigned char const *array, uint16_t frame_number) {
	int i;
	uint16_t sample_index = 0;

	//Buffers initialization

	/* we prepare two buffers of decoded data: */
	/* the first one, */
	for (i = 0; i < ENCODED_FRAME_SIZE; i++) {
		input_bytes[i] = array[sample_index];
		sample_index++;
	}
	speex_bits_read_from(&bits, input_bytes, ENCODED_FRAME_SIZE);
	speex_decode_int(dec_state, &bits, (spx_int16_t*) OUT_Buffer[0]);

	/* and the second one. */
	for (i = 0; i < ENCODED_FRAME_SIZE; i++) {
		input_bytes[i] = array[sample_index];
		sample_index++;
	}

	speex_bits_read_from(&bits, input_bytes, ENCODED_FRAME_SIZE);
	speex_decode_int(dec_state, &bits, (spx_int16_t*) OUT_Buffer[1]);

	NB_Frames++;

	//Start of sound playing
	//reading data from main array
	//and decoding then needed
	while (NB_Frames < frame_number) {
		if (Start_Decoding == 1) /* we start decoding the first buffer */
		{
			for (i = 0; i < ENCODED_FRAME_SIZE; i++) {
				input_bytes[i] = array[sample_index];
				sample_index++;
			}

			speex_bits_read_from(&bits, input_bytes, ENCODED_FRAME_SIZE);
			speex_decode_int(dec_state, &bits, (spx_int16_t*) OUT_Buffer[0]);

			Start_Decoding = 0;
			NB_Frames++;
		}
		if (Start_Decoding == 2) /* we start decoding the second buffer */
		{
			for (i = 0; i < ENCODED_FRAME_SIZE; i++) {
				input_bytes[i] = array[sample_index];
				sample_index++;
			}

			speex_bits_read_from(&bits, input_bytes, ENCODED_FRAME_SIZE);
			speex_decode_int(dec_state, &bits, (spx_int16_t*) OUT_Buffer[1]);

			Start_Decoding = 0;
			NB_Frames++;
		}

	}    //end while

	sample_index = 0;

	NB_Frames = 0;
	outBuffer = OUT_Buffer[0];
}

#pragma GCC diagnostic pop
