#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <bsd/stdlib.h>
#include <sys/time.h>

#define NB_PROD_THREAD 10
#define NB_CONS_THREAD 1

#define PRINT_PROD if (!(q.end % 10000)) {printf("@%llu: %i produced\n", q.end, q.data[q.start]);}
#define PRINT_CONS if (!(q.start % 10000)) {printf("@%llu: %i consumed\n", q.start, q.data[q.start]);}


// Defaults units to produce to 50
unsigned long long nb_prod = 50;

int to_consume;
int to_produce;
int sync_on = 1, profile = 0;

typedef struct {
	
	int *data;
	unsigned long long start;
	unsigned long long end;

} queue;

// Initializes the queue to zero
void init_queue(queue * q, int size) {
	q->data = malloc(size * sizeof(int));
	q->start = 0;
	q->end = 0;
}

void read_args(int argc, char *argv[]) {

	int i;
	for (i = 1; i < argc; i++) {

		if(!strcmp(argv[i], "-async")) {
			// Disables sync mode
			sync_on = 0;
		} else if(!strcmp(argv[i], "-profile")) {
			// Only output runtime
			profile = 1;
		} else if(!strcmp(argv[i], "-produce")) {
			// Specifies how much to produce
			if (i++ > argc) {
				printf("Please specify how much to produce.\n");
				exit(1);
			} else {
				nb_prod = atol(argv[i]);
			}
		}
	}
}

