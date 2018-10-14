#include<stdio.h> 
#include<stdlib.h>
#include<math.h>

#define size 100

typedef struct dataElement{
	char num[10];
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
	double a = 65+128;
	printf("%c\n\n",(char)((int)a%128));
	printf("%g\n\n",pow(2,3));
//	printf("%p\n",stack); 
//	printf("%d\n",initStack (&stack));
//	printf("%p",stack);
	return 0;
} 
