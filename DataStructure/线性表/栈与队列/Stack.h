#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SIZE 101

//typedef struct dataElement {
//	char num[10];
//}String;

typedef struct stackStruct {
	double data[SIZE];
	int top;
}Stack;

int initStack(Stack **stack);

int isEmpty(Stack *stack);

int isFull(Stack *stack);

int getTop(Stack *stack, double *e);

int pop(Stack *stack, double *e);

int push(Stack *stack, double data);

