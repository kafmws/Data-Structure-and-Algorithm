#include"pch.h"
#include"Stack.h"

int initStack(Stack **stack) {
	*stack = (Stack *)malloc(sizeof(Stack));
	(*stack)->top = -1;
	if (*stack)
		return 1;
	return 0;
}

int isEmpty(Stack *stack) {
	return stack->top == -1;
}

int isFull(Stack *stack) {
	return stack->top == SIZE;
}

int getTop(Stack *stack, Coord **e) {
	if (!isEmpty(stack)) {
		*e = &(stack->data[stack->top]);
		return 1;
	}
	return 0;
}

int pop(Stack *stack, Coord *e) {
	if (!isEmpty(stack)) {
		*e = stack->data[stack->top--];
		return 1;
	}
	return 0;
}

int push(Stack *stack, Coord data) {
	if (!isFull(stack)) {
		stack->top++;
		stack->data[stack->top] = data;
		return 1;
	}
	return 0;
}