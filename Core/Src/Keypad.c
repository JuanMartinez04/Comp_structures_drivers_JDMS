
#include "Keypad.h"
#include "main.h"
#include <stdio.h>

/*
 * @breif: The function initialize the keypad
 * */

void keypad_init(void){
	/* Set the rows high to be detected in the columns by rising interrupt */
			  ROW_1_GPIO_Port->BSRR = ROW_1_Pin;
		      ROW_2_GPIO_Port->BSRR = ROW_2_Pin;
		      ROW_3_GPIO_Port->BSRR = ROW_3_Pin;
		      ROW_4_GPIO_Port->BSRR = ROW_4_Pin;
}


/*
 *@brief Keypad key detection function
 * @param column_event:  the column that has the event
 * @retval 0xFF -> invalid key. [0x00 - 0x0F] -> valid key.
 * */

uint16_t KeyPad_handler (uint16_t column_event){


	uint16_t key_pressed = 0xFF;//key value

	#define KEY_DEBOUNCE_MS 300 /*!> Minimum time required for since last press */
	static uint32_t last_pressed_tick = 0;

	if (HAL_GetTick() <= (last_pressed_tick + KEY_DEBOUNCE_MS)) {
		// less than KEY_DEBOUNCE_MS since last press. Probably noise
		return key_pressed; // return 0xFF
	}
	last_pressed_tick = HAL_GetTick();

	/*** Check in which column the event happened ***/
	  switch(column_event){

	  case COLUMN_1_Pin:
			ROW_1_GPIO_Port->BSRR = ROW_1_Pin;// turn on row 1
			ROW_2_GPIO_Port->BRR = ROW_2_Pin;// turn off row 2
			ROW_3_GPIO_Port->BRR = ROW_3_Pin;// turn off row 3
			ROW_4_GPIO_Port->BRR = ROW_4_Pin;// turn off row 4
			if(COLUMN_1_GPIO_Port->IDR & COLUMN_1_Pin) key_pressed =0x01;//if column 1 is still high
																		//-> column 1 + row 1 = key 1
			ROW_1_GPIO_Port->BRR = ROW_1_Pin;// turn off row 1
			ROW_2_GPIO_Port->BSRR = ROW_2_Pin;// turn on row 2
			if(COLUMN_1_GPIO_Port->IDR & COLUMN_1_Pin) key_pressed =0x04;//if column 1 is still high
																		//-> column 1 + row 2 = key 4

			ROW_2_GPIO_Port->BRR = ROW_2_Pin;// turn off row 2
			ROW_3_GPIO_Port->BSRR = ROW_3_Pin;// turn on row 3
			if(COLUMN_1_GPIO_Port->IDR & COLUMN_1_Pin) key_pressed =0x07;//if column 1 is still high
																		//-> column 1 + row 3 = key 7

			ROW_3_GPIO_Port->BRR = ROW_3_Pin;// turn off row 3
			ROW_4_GPIO_Port->BSRR = ROW_4_Pin;// turn on row 4
			if(COLUMN_1_GPIO_Port->IDR & COLUMN_1_Pin) key_pressed =0x0E;//if column 1 is still high
																		//-> column 1 + row 4 = key *

		   break;
	  case COLUMN_2_Pin:
			ROW_1_GPIO_Port->BSRR = ROW_1_Pin;// turn on row 1
			ROW_2_GPIO_Port->BRR = ROW_2_Pin;// turn off row 2
			ROW_3_GPIO_Port->BRR = ROW_3_Pin;// turn off row 3
			ROW_4_GPIO_Port->BRR = ROW_4_Pin;// turn off row 4
			HAL_Delay(2); // wait for voltage to establish
			if(COLUMN_2_GPIO_Port->IDR & COLUMN_2_Pin) key_pressed =0x02;//if column 2 is still high
																		//-> column 2 + row 1 = key 2
			ROW_1_GPIO_Port->BRR = ROW_1_Pin;// turn off row 1
			ROW_2_GPIO_Port->BSRR = ROW_2_Pin;// turn on row 2
			HAL_Delay(2); // wait for voltage to establish
			if(COLUMN_2_GPIO_Port->IDR & COLUMN_2_Pin) key_pressed =0x05;//if column 2 is still high
																		//-> column 2 + row 2 = key 4

			ROW_2_GPIO_Port->BRR = ROW_2_Pin;// turn off row 2
			ROW_3_GPIO_Port->BSRR = ROW_3_Pin;// turn on row 3
			HAL_Delay(2); // wait for voltage to establish
			if(COLUMN_2_GPIO_Port->IDR & COLUMN_2_Pin) key_pressed =0x08;//if column 2 is still high
																		//-> column 2+ row 3 = key 8

			ROW_3_GPIO_Port->BRR = ROW_3_Pin;// turn off row 3
			ROW_4_GPIO_Port->BSRR = ROW_4_Pin;// turn on row 4
			HAL_Delay(2); // wait for voltage to establish
			if(COLUMN_2_GPIO_Port->IDR & COLUMN_2_Pin) key_pressed =0x00;//if column 2 is still high
																		//-> column 2 + row 4 = key 0
			break;

	  case COLUMN_3_Pin:
			ROW_1_GPIO_Port->BSRR = ROW_1_Pin;// turn on row 1
			ROW_2_GPIO_Port->BRR = ROW_2_Pin;// turn off row 2
			ROW_3_GPIO_Port->BRR = ROW_3_Pin;// turn off row 3
			ROW_4_GPIO_Port->BRR = ROW_4_Pin;// turn off row 4
			HAL_Delay(2); // wait for voltage to establish
			if(COLUMN_3_GPIO_Port->IDR & COLUMN_3_Pin) key_pressed =0x03;//if column 3 is still high
																		//-> column 3 + row 1 = key 3
			ROW_1_GPIO_Port->BRR = ROW_1_Pin;// turn off row 1
			ROW_2_GPIO_Port->BSRR = ROW_2_Pin;// turn on row 2
			HAL_Delay(2); // wait for voltage to establish
			if(COLUMN_3_GPIO_Port->IDR & COLUMN_3_Pin)  key_pressed =0x06;//if column 3 is still high
																		//-> column 3 + row 2 = key 6

			ROW_2_GPIO_Port->BRR = ROW_2_Pin;// turn off row 2
			ROW_3_GPIO_Port->BSRR = ROW_3_Pin;// turn on row 3
			HAL_Delay(2); // wait for voltage to establish
			if(COLUMN_3_GPIO_Port->IDR & COLUMN_3_Pin)  key_pressed =0x09;//if column 3 is still high
																		//-> column 3 + row 3 = key 9

			ROW_3_GPIO_Port->BRR = ROW_3_Pin;// turn off row 3
			ROW_4_GPIO_Port->BSRR = ROW_4_Pin;// turn on row 4
			HAL_Delay(2); // wait for voltage to establish
			if(COLUMN_3_GPIO_Port->IDR & COLUMN_3_Pin)  key_pressed =0x0F;//if column 3 is still high
																		//-> column 3 + row 4 = key #
		   break;
	  case COLUMN_4_Pin:
			ROW_1_GPIO_Port->BSRR = ROW_1_Pin;// turn on row 1
			ROW_2_GPIO_Port->BRR = ROW_2_Pin;// turn off row 2
			ROW_3_GPIO_Port->BRR = ROW_3_Pin;// turn off row 3
			ROW_4_GPIO_Port->BRR = ROW_4_Pin;// turn off row 4
			HAL_Delay(2); // wait for voltage to establish
			if(COLUMN_4_GPIO_Port->IDR & COLUMN_4_Pin) key_pressed =0x0A;//if column 4 is still high
																		//-> column 4 + row 1 = key A
			ROW_1_GPIO_Port->BRR = ROW_1_Pin;// turn off row 1
			ROW_2_GPIO_Port->BSRR = ROW_2_Pin;// turn on row 2
			HAL_Delay(2); // wait for voltage to establish
			if(COLUMN_4_GPIO_Port->IDR & COLUMN_4_Pin) key_pressed =0x0B;//if column 4 is still high
																		//-> column 4 + row 2 = key B

			ROW_2_GPIO_Port->BRR = ROW_2_Pin;// turn off row 2
			ROW_3_GPIO_Port->BSRR = ROW_3_Pin;// turn on row 3
			HAL_Delay(2); // wait for voltage to establish
			if(COLUMN_4_GPIO_Port->IDR & COLUMN_4_Pin) key_pressed =0x0C;//if column 4 is still high
																		//-> column 4 + row 3 = key C

			ROW_3_GPIO_Port->BRR = ROW_3_Pin;// turn off row 3
			ROW_4_GPIO_Port->BSRR = ROW_4_Pin;// turn on row 4
			HAL_Delay(2); // wait for voltage to establish
			if(COLUMN_4_GPIO_Port->IDR & COLUMN_4_Pin) key_pressed =0x0D;//if column 4 is still high
																		//-> column 4 + row 4 = key D
		    break;
	  default:
		  	  /* This should not be reached */
		  	  printf("Unknown column: %x\r\n", column_event);//if something wrong print the key value
		  break;
	  }

		keypad_init();//set the columns high again for receive other key
		return key_pressed;//return the key value
}
