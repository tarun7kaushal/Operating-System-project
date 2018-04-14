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



/*

 * PID Manager

 */



#define MIN 10

#define MAX 1000



// each thread data; so that it can passed to thread functions

typedef struct thread_data {

	pthread_t thread;

	int tid;

} THREAD;



uint32_t *pid_map;

pthread_mutex_t lock;
