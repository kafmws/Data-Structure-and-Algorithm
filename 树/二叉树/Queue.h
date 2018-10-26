#pragma once
#include"pch.h"
#include"BinaryTree.h"

#define QueueSize 100

/*
*	—≠ª∑∂”¡–
*	create	by    kafm
*	2018.10.26
*/

typedef BinaryTree QueueElement;

typedef struct {
	QueueElement queue[QueueSize];
	int maxSize, front, rear;
}Queue;

void initQueue(Queue **pq);

int enterQueue(Queue *q, QueueElement e);

int quitQueue(Queue *q, QueueElement *e);

int cntQueue(Queue *q);