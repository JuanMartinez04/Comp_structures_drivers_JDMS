/*
 * Keypad.h
 *
 *  Created on: Nov 3, 2023
 *      Author: juand
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_
#include <stdint.h>
#include <stdbool.h>


void keypad_init(void); //init function

uint16_t KeyPad_handler(uint16_t key_event);//function for detec the key

#endif /* INC_KEYPAD_H_ */
