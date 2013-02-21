#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <bsd/stdlib.h>
#include <sys/time.h>
#include "factory.h"

queue q;

int nb_prod = 50;
int sync_on = 1;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static void * producer();
static void * consumer();

int main(int argc, char *argv[]) {
	
	// Initiates random seed
	srand(time(NULL));

	// Deals with extra arguments
	if(argc > 1) {

		if(!strcmp(argv[1], "-async")) {
			// Disables sync mode
			sync_on = 0;
		} else {
			nb_prod = atoi(argv[1]);
		}

		if(argc == 3) {
			nb_prod = atoi(argv[2]);
		}

	} else {
		return 1;
	}

	init_queue(&q);
	
	pthread_t prod_thread[NB_PROD_THREAD];
	pthread_t cons_thread[NB_CONS_THREAD];

	int id;

	for(id = 0; id < NB_PROD_THREAD; id++) {
		
		// Creates the producer threads
		if(pthread_create(&prod_thread[id], NULL, producer, "")) {
			
			printf("Error creating producer thread #%d\n", id);
			return 1;
		}

		// Joins the producer threads
		if(id != 0 && pthread_join(prod_thread[id], NULL))
		{
			printf("Error joining producer thread #%d\n", id);
			return 1;
		}
	}

	
	for(id = 0; id < NB_PROD_THREAD; id++) {
		
		// Creates the consumer threads
		if(pthread_create(&cons_thread[id], NULL, consumer, "")) {
			
			printf("Error creating customer thread\n");
			return 1;
		}
	}

	printf("Produced: %d\nConsumed: %d\n", q.end, q.start);

	exit(0);
	return 0;
}


static void * producer() {
	
	int i;
	for(i = 0; i < nb_prod; i++) {
		
		int item = rand() % 6969;
		
		if(sync_on) {
			pthread_mutex_lock(&mutex);
		}

		q.data[q.end] = item;
		//printf("@%i: %i produced\n", q.end - nb_prod + i, item);
		q.end++;

		if(sync_on) {
			pthread_cond_signal(&cond);
			pthread_mutex_unlock(&mutex);
		}
	}
	return NULL;
}

static void * consumer() {

	while(1) {
		if(sync_on){

			pthread_mutex_lock(&mutex);
			
			if(q.end == q.start) {
				pthread_cond_wait(&cond, &mutex);
			}

		} else {
			while(q.end == q.start);
		}

		//int item = q.data[q.start];
		//printf("@%i: %i consumed\n", q.start, item);
		q.start++;
		
		if(sync_on) {
			pthread_mutex_unlock(&mutex);
		}
	}
	return NULL;
}