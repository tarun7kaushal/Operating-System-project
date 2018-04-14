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
42


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





// Creates and initializes a data structure for representing pids; returns —1 if unsuccessfull, 1 if successfull 

int allocate_map(long long);



// Allocates and returns a pid; returns —1 if unable to allocate a pid (all pids are in use)

int allocate_pid();



// Releases a pid

void release_pid(int);



// process func

void* processFunc(void*);





int main(int argc, char** arv) {



	if (allocate_map(MAX) == -1) {

		printf("\nUnable to allocate memory for PID Map");

		exit(-1);

	}



	int nThreads;

	printf("\nHow many threads? ");

	scanf("%d", &nThreads);



	THREAD *threads = (THREAD *)malloc(nThreads * sizeof(*threads));

	for(int i=0; i<nThreads; i++) threads[i].tid = i+1;



	pthread_attr_t attr;

	pthread_attr_init(&attr);

	

	for(int i=0; i<nThreads; i++)

		pthread_create(&threads[i].thread, &attr, processFunc, (void *)&threads[i]);



	for(int i=0; i<nThreads; i++)

		pthread_join(threads[i].thread, NULL);



	printf("\n\nAll threads executed\n");



	free(pid_map);

	free(threads);

	return 0;

}