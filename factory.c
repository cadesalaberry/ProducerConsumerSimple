#include "factory.h"

queue q;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static void * producer();
static void * consumer();

int main(int argc, char *argv[]) {
	
	//Setting up timer
	struct timeval start, end;
	gettimeofday(&start, NULL);

	// Initiates random seed
	srand(time(NULL));

	// Deals with extra arguments
	read_args(argc, argv);

	// Determines what to consume and what to produce
	to_consume = NB_PROD_THREAD / NB_CONS_THREAD * nb_prod;
	to_produce = nb_prod;
	init_queue(&q, NB_PROD_THREAD * nb_prod);
	
	pthread_t prod_thread[NB_PROD_THREAD];
	pthread_t cons_thread[NB_CONS_THREAD];

	int id;

	for(id = 0; id < NB_PROD_THREAD; id++) {
		
		// Creates the producer threads
		if(pthread_create(&prod_thread[id], NULL, producer, NULL)) {		
			printf("Error creating producer thread #%d\n", id);
			return 1;
		}

		// Joins the producer threads
		if(pthread_join(prod_thread[id], NULL)) {
			printf("Error joining producer thread #%d\n", id);
			return 1;
		}
	}
	
	for(id = 0; id < NB_CONS_THREAD; id++) {
		
		// Creates the consumer threads
		if(pthread_create(&cons_thread[id], NULL, consumer, NULL)) {
			printf("Error creating customer thread\n");
			return 1;
		}

		// Joins the consumer threads
		if(pthread_join(cons_thread[id], NULL)){
			printf("Error joining consumer thread #%d\n", id);
			return 1;
		}
	}
	
	// Ends Timer
	gettimeofday(&end, NULL);
	long long t_elapsed = (end.tv_sec - start.tv_sec) * 1000000LL;
	t_elapsed += end.tv_usec-start.tv_usec;

	if (profile) {

		printf("%llu\n", t_elapsed);

	} else {
	
		printf("Produced\t: %llu\n", q.end);
		printf("Consumed\t: %llu\n", q.start);
		printf("Time\t\t: %llu\n", t_elapsed);
	}

	return 0;
}


static void * producer() {

	int i;
	for(i = 0; i < to_produce; i++) {
		
		if(sync_on) {
			pthread_mutex_lock(&mutex);
		}

		q.data[q.end] = rand() % 6969;
		
		//PRINT_PROD
		q.end++;

		if(sync_on) {
			pthread_mutex_unlock(&mutex);
			pthread_cond_signal(&cond);
		}
	}
	return NULL;
}

static void * consumer() {
	
	// While there is still something to consume
	int i;
	for(i = 0; i < to_consume; i++) {

		if(sync_on){

			pthread_mutex_lock(&mutex);
			
			if(q.end == q.start) {
				pthread_cond_wait(&cond, &mutex);
			}
		} else {
			while(q.end == q.start);
		}

		//PRINT_CONS
		//q.data[q.start] = 0;
		q.start++;
		
		if(sync_on) {
			pthread_mutex_unlock(&mutex);
		}
	}
	return NULL;
}