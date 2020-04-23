#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define MAX_QUEUES 10 /* m=MAX_QUEUES=10 */
typedef struct {
	int key;/* other fields */
} element;

typedef struct queue* queue_ptr;
typedef struct queue {
	element item;
	queue_ptr link;
};

void insertq(queue_ptr* front, queue_ptr* rear, element x) {
	queue_ptr temp = (queue_ptr)malloc(sizeof(struct queue));
	if (!temp) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}
	temp->item = x;
	temp->link = NULL;
	if (*front) (*rear)->link = temp;
	else *front = temp;
	*rear = temp;
}

element deleteq(queue_ptr* front) {
	queue_ptr temp = *front;
	element x;
	if (!(*front)) {
		fprintf(stderr, "The queue is empty\n");
		exit(1);
	}
	x = temp->item;
	*front = temp->link;
	free(temp);
	return x;
}

int elementcount(queue_ptr front, queue_ptr rear)
{
	queue_ptr head;
	head = front;
	int cnt = 0;
	
	while (head!=NULL) {
		++cnt;
		head =  head->link;
	}
	return cnt;
}



int main()
{
	queue_ptr front = NULL, rear = NULL;
	element x; x.key = 50;
	insertq(&front, &rear, x);
	insertq(&front, &rear, x);
	insertq(&front, &rear, x);

	printf(" Begin Queue Test …\n");

	printf("큐의 원소의 수 : %d\n", elementcount(front, rear));
	while (!front == NULL)
	{
		x = deleteq(&front);
		printf("value = %d\n", x.key);
	}
}