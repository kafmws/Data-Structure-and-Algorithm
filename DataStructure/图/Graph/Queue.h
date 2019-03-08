#pragma once
#include"pch.h"

#define QueueSize 100

/*
*	—≠ª∑∂”¡–
*	create	by    kafm
*	2018.10.26
*/

typedef int QueueElement;

typedef struct {
	QueueElement queue[QueueSize];
	int maxSize, front, rear;
}Queue;

void initQueue(Queue **qq);

int enterQueue(Queue *q, QueueElement e);

int quitQueue(Queue *q, QueueElement *e);

int cntQueue(Queue *q);

int isEmpty(Queue * q);
