#pragma once

#include"pch.h"

#define StackSize 100

/*
*	ջ
*	create by kafm
*	2018.10.26
*/

typedef BinaryTree StackElement;

typedef struct {
	StackElement stack[StackSize];
	int top;
}Stack;

void initStack(Stack **ps);

int isEmpty(Stack *s);

int isFull(Stack *s);

int push(Stack *s, StackElement e);

int pop(Stack *s, StackElement *e);

int getTop(Stack *s, StackElement *e);