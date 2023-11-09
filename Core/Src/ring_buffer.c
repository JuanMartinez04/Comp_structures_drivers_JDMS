

#include "ring_buffer.h"


/**
 * @brief This function initializes the control struct of the ring buffer
*/
void ring_buffer_init(ring_buffer_t *ring_buffer, uint8_t *buffer,uint16_t capacity)
{
	ring_buffer ->buffer = buffer;
	ring_buffer -> capacity= capacity;

	ring_buffer ->head = 0;
	ring_buffer ->tail = 0;
	ring_buffer ->is_full = 0;
}


/**
 * @brief this function adds the a data in the ring buffer
 *@Param data: value to write in the buffer
 */
uint8_t ring_buffer_put(ring_buffer_t *ring_buffer, uint8_t data)
{
	ring_buffer->buffer [ring_buffer->head] = data; /*put the data in the head position*/
	ring_buffer->head=(ring_buffer->head+1)% ring_buffer->capacity;/*move ahead the head*/

	if(ring_buffer->is_full!=0){	/*verify if the buffer is full*/
		ring_buffer->tail =(ring_buffer->tail+1)%ring_buffer->capacity;/*if it's full then move ahead the tail*/
		}
	if(ring_buffer->head==ring_buffer ->tail){/*if the position of the tail and the head is the same, the buffer is full*/
		ring_buffer ->is_full = 1;
		return 0;
	}
	return 1;
}


/**
 * @brief this function reads the data from the ring buffer
 *@Param data: pointer to the address to read the data
 */

uint8_t ring_buffer_get(ring_buffer_t *ring_buffer, uint8_t *data){

	if(ring_buffer_is_empty(ring_buffer)==0){

		*data = ring_buffer->buffer[ring_buffer->tail];
		ring_buffer->tail=(ring_buffer->tail +1)% ring_buffer->capacity;/*move ahead the tail for reading*/
		ring_buffer ->is_full = 0;/*the buffer isn't full*/
		return 1;
	}
	else{
		return 0;}

}
/**
 * @brief this function returns the size of the buffer
 *
 */
uint16_t ring_buffer_size(ring_buffer_t  *ring_buffer){

	uint16_t size = 0;
	if((ring_buffer->is_full==0) &&  ring_buffer->tail < ring_buffer ->head){
		size= ring_buffer->head-ring_buffer->tail;
	}

	else{
		size =ring_buffer->head +(ring_buffer->capacity -ring_buffer->tail);
	}
	return size;
}

/**
 * @brief this function checks if the buffer is empty
 *
 */

uint8_t ring_buffer_is_empty(ring_buffer_t  *ring_buffer)
{
	return ((ring_buffer->is_full ==0)&&(ring_buffer->head==ring_buffer->tail));
}
/**
 * @brief this function checks if the buffer is full
 *
 */
uint8_t ring_buffer_is_full(ring_buffer_t *ring_buffer){
	return ring_buffer->is_full;
}

/**
 * @brief this function resets the buffer to be empty
 *
 */
void ring_buffer_reset(ring_buffer_t *ring_buffer){
	ring_buffer->tail = 0;
	ring_buffer->head = 0;
	ring_buffer->is_full =0;
}









