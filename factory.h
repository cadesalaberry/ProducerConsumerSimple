#define NB_PROD_THREAD 10
#define NB_CONS_THREAD 1

#define PRINT_PROD if (!(q.end % 100000)) {printf("@%i: %i produced\n", q.end, item);}
#define PRINT_CONS if (!(q.start % 10000)) {printf("@%i: %i consumed\n", q.start, q.data[q.start]);}

typedef struct {
	
	int *data;
	int start;
	int end;

} queue;

void init_queue(queue * q, int size) {
	q->data = malloc(size * sizeof(int));
	q->start = 0;
	q->end = 0;
}