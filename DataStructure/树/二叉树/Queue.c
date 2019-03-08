#include"pch.h"
#include"Queue.h"

void initQueue(Queue **pq) {
	*pq = (Queue *)malloc(sizeof(Queue));
	Queue *q = *pq;
	q->maxSize = 100;
	q->front = 0;
	q->rear = 0;
}

int enterQueue(Queue *q, QueueElement e) {
	if (q&&(q->rear + 1) % q->maxSize == q->front)//¶ÓÂú
		return 0;
	q->queue[q->rear] = e;
	q->rear = (q->rear + 1) % q->maxSize;
	return 1;
}

int quitQueue(Queue *q, QueueElement *e) {
	if (q&&(q->rear == q->front))//¶Ó¿Õ
		return 0;
	*e = q->queue[q->front];
	q->front = (q->front + 1) % q->maxSize;
	return 1;
}

int cntQueue(Queue *q) {
	return (q->rear + q->maxSize - q->front) % q->maxSize;
}

