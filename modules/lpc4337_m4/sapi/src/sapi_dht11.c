/*
 * dht11.c
 *
 *  Created on: Nov 13, 2017
 *      Author: Sebastian Pablo Bedin <sebabedin@gmail.com>
 */

#include "sapi_dht11.h"

#define DHT11_TIMEOUT_MAX			(1000)
#define DHT11_LEN_dht11_ticks_array	(82)
#define DHT11_LEN_dht11_byte		(5)

static uint32_t 	dht11_ticks_array[DHT11_LEN_dht11_ticks_array];
static uint8_t 		dht11_byte[DHT11_LEN_dht11_byte];

enum dht11_state_e {
	dht11_state_start,
	dht11_state_low,
	dht11_state_high,
	dht11_state_timeout,
	dht11_state_error,
	dht11_state_end,
};

static void dht11_GPIO_Low(void) {
	gpioConfig(DHT11_GPIO, GPIO_OUTPUT);
	gpioWrite(DHT11_GPIO, FALSE);
}

static void dht11_GPIO_High(void) {
	gpioConfig(DHT11_GPIO, GPIO_INPUT_PULLUP);
}

static bool_t dht11_GPIO_Read(void) {
	return gpioRead(DHT11_GPIO);
}

uint32_t dht11_timeout;
uint32_t dht11_timeout_max;
static void dht11_TimeOutReset(uint32_t max) {
	if(0 < max) {
		dht11_timeout_max = max;
	} else {
		dht11_timeout_max = DHT11_TIMEOUT_MAX;
	}
	dht11_timeout = dht11_timeout_max;
}

static bool_t dht11_TimeOutCheck(void) {
	if(0 < dht11_timeout) {
		dht11_timeout--;
		return TRUE;
	}
	dht11_TimeOutReset(0);
	return FALSE;
}

static bool_t dht11_StartRead(void) {
	uint8_t  state          = dht11_state_start;
	bool_t   flag_loop_end	= FALSE;
	bool_t   flag_timeout   = FALSE;
	bool_t   flag_error	   = FALSE;
	uint32_t n_tick         = 0;
	uint32_t n_bit          = 0;

	dht11_GPIO_Low();
	delay(20);
	dht11_GPIO_High();

	while(FALSE == flag_loop_end) {
		switch(state) {
		case dht11_state_start:

			dht11_TimeOutReset(DHT11_TIMEOUT_MAX);
			while(dht11_state_start == state) {
				if(dht11_GPIO_Read() == FALSE) {
					state = dht11_state_low;
				}
				if(!dht11_TimeOutCheck()) {
					state = dht11_state_timeout;
				}
			}
			break;

		case dht11_state_low:

			dht11_TimeOutReset(0);
			while(dht11_state_low == state) {
				n_tick++;
				if(dht11_GPIO_Read() == TRUE) {
					dht11_ticks_array[n_bit] = n_tick;
					n_bit++;
					n_tick = 0;
					state = dht11_state_high;
				}

				if(!dht11_TimeOutCheck()) {
					state = dht11_state_timeout;
				}
			}
			break;

		case dht11_state_high:

			dht11_TimeOutReset(0);
			while(dht11_state_high == state) {
				n_tick++;
				if(dht11_GPIO_Read() == FALSE) {
					dht11_ticks_array[n_bit] = n_tick;
					n_bit++;
					n_tick = 0;
					state = dht11_state_low;
				}

				if(!dht11_TimeOutCheck()) {
					state = dht11_state_timeout;
				}
			}
			break;

		case dht11_state_timeout:
			flag_timeout = TRUE;
			state = dht11_state_end;
			break;

		case dht11_state_end:
			flag_loop_end = TRUE;
			break;

		default:
		case dht11_state_error:
			flag_error = TRUE;
			state = dht11_state_end;
			break;
		}


		if(DHT11_LEN_dht11_ticks_array <= n_bit) {
			state = dht11_state_end;
		}
	}

	if(82 == n_bit) {
		return TRUE;
	}

	return FALSE;
}

static bool_t dht11_ProcessData(void) {
	int i, i_i, i_f, j;
	uint32_t valf, valt;

	valf = dht11_ticks_array[0];
	valt = dht11_ticks_array[1];
	for(i = 2; i < 81; i++) {
		if((valf <= dht11_ticks_array[i]) || (valt <= dht11_ticks_array[i])) {
			return FALSE;
		}
	}

	i_i = 2;
	for(j = 0; j < DHT11_LEN_dht11_byte; j++) {
		dht11_byte[j] = 0x00;
		i_f = i_i + 8 * 2 - 1;
		for(i = i_i; i < i_f; i = i + 2) {
			valf = dht11_ticks_array[i];
			valt = dht11_ticks_array[i+1];

			if(valt < valf) {
				dht11_byte[j] = (dht11_byte[j] << 1);
			} else {
				dht11_byte[j] = (dht11_byte[j] << 1) | 0x01;
			}
		}
		i_i = i_f + 1;
	}

	uint8_t crc;
	crc = dht11_byte[0] + dht11_byte[1] + dht11_byte[2] + dht11_byte[3];
	if(crc != dht11_byte[4]) {
		return FALSE;
	}

	return TRUE;
}

void dht11Config (void) {
	dht11_GPIO_High();
}

bool_t dht11Read (float *phum, float *ptemp) {
	if(TRUE == dht11_StartRead()) {
		if(TRUE == dht11_ProcessData()) {
			*phum 	= ((float)dht11_byte[0]) + ((float)dht11_byte[1])/10;
			*ptemp 	= ((float)dht11_byte[2]) + ((float)dht11_byte[3])/10;
			return TRUE;
		}
	}
	return FALSE;
}
