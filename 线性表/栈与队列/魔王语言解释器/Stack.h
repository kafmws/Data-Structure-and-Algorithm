#include"pch.h"

#define NUM 101
#define LEN 25

typedef struct stackStruct {
	char data[NUM];
	int top;
}Stack;

int initStack(Stack **stack);

int isEmpty(Stack *stack);

int isFull(Stack *stack);

int getTop(Stack *stack, char *e);

int pop(Stack *stack, char *e);

int push(Stack *stack, char data);
