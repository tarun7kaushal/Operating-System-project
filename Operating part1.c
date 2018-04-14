#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <stdint.h>

#include <pthread.h>



/*

 * BITMAP Implementation

 */



#define BIT_SIZE 32



long long getBitmapSize(long long size) {

        return ( size/BIT_SIZE + (!!(size%BIT_SIZE)) );

}



void set_bit(uint32_t *bitmap, int index) {

    bitmap[index / BIT_SIZE] |= 1 << (index % BIT_SIZE);

}



void clear_bit(uint32_t *bitmap, int index) {

    bitmap[index / BIT_SIZE] &= ~(1 << (index % BIT_SIZE));

}



int get_bit(uint32_t *bitmap, int index) {

    return 1 & (bitmap[index / BIT_SIZE] >> (index % BIT_SIZE));

}