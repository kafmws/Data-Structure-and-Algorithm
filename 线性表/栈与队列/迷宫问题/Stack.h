#include"pch.h"
#include<stdio.h>
#include<string.h>

#define SIZE 101

typedef struct dataElement {
	int x;
	int y;
	int step;//当前试探到的step; 0,1,2,3
}Coord;

typedef struct stackStruct {
	Coord data[SIZE];
	int top;
}Stack;

int initStack(Stack **stack);

int isEmpty(Stack *stack);

int isFull(Stack *stack);

int getTop(Stack *stack, Coord **e);

int pop(Stack *stack, Coord *e);

int push(Stack *stack, Coord data);
