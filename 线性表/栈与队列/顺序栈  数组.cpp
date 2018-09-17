#include<stdio.h> 
#include<stdlib.h>

#define size 100

typedef struct dataElement{
	int num;
}Element;

typedef struct stackStruct{
	Element data[size];
	int top;
}Stack;

int initStack(Stack **stack){
	*stack = (Stack *)malloc(sizeof(Stack));
	(*stack)->top = -1;
	if(*stack)
		return 1;
	return 0;
}

int isEmpty(Stack *stack){
	return stack->top == -1;
} 

int isFull(Stack *stack){
	return stack->top == size;
}

int getTop(Stack *stack, Element *e){
	if(!isEmpty(stack)){
		*e = stack->data[stack->top];
		return 1;
	}
	return 0;
}

int pop(Stack *stack, Element *e){
	if(!isEmpty(stack)){
		*e = stack->data[stack->top--];
		return 1;
	}
	return 0;
} 

int push(Stack *stack, Element data ){
	if(!isFull(stack)){
		stack->data[stack->top++] = data;
		return 1;
	}
	return 0;
}

int main(){
	Stack *stack = NULL;
	printf("%p\n",stack); 
	printf("%d\n",initStack (&stack));
	printf("%p",stack);
	return 0;
} 
