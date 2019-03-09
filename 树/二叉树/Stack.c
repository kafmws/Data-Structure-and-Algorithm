#include"pch.h"

void initStack(Stack **ps) {
	*ps = (Stack *)malloc(sizeof(Stack));
	(*ps)->top = -1;
}

int isEmpty(Stack *s) {
	return s->top == -1;
}

int isFull(Stack *s) {
	return s->top == StackSize;
}

int push(Stack *s, StackElement e) {
	if (isFull(s))
		return 0;
	s->stack[++s->top] = e;
	return 1;
}

int pop(Stack *s, StackElement *e) {
	if (isEmpty(s))
		return 0;
	*e = s->stack[s->top--];
	return 1;
}

int getTop(Stack *s, StackElement *e) {
	if (isEmpty(s))
		return 0;
	*e = s->stack[s->top];
	return 1;
}