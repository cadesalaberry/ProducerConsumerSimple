#define NB_PROD_THREAD 10
#define NB_CONS_THREAD 10
#define MAX_QUEUE 99999999

typedef struct {
	
	int data[MAX_QUEUE];
	int start;
	int end;

} queue;

void init_queue(queue * q) {
	q->start = 0;
	q->end = 0;
}