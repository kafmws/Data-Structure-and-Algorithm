#include"pch.h"
#include "visitBinaryTree.h"

void preOrder(BinaryTree *root) {
	if (!root)
		return;
	printf("%c", root->c);
	preOrder(root->LeftChild);
	preOrder(root->RightChild);
}

void midOrder(BinaryTree *root) {
	if (!root)
		return;
	midOrder(root->LeftChild);
	printf("%c", root->c);
	midOrder(root->RightChild);
}

void postOrder(BinaryTree *root) {
	if (!root)
		return;
	postOrder(root->LeftChild);
	postOrder(root->RightChild);
	printf("%c", root->c);
}

void levelOrderRe(Queue *q) {//使用队列递归层序遍历
	if (q->front == q->rear)
		return;
	BinaryTree t;
	quitQueue(q, &t);
	printf("%c", t.c);
	if (t.LeftChild)
		enterQueue(q, *t.LeftChild);
	if (t.RightChild)
		enterQueue(q, *t.RightChild);
	levelOrderRe(q);
}

void levelOrder(Queue *q) {
	while (q->front != q->rear) {
		BinaryTree t;
		quitQueue(q, &t);
		printf("%c", t.c);
		if (t.LeftChild)
			enterQueue(q, *t.LeftChild);
		if (t.RightChild)
			enterQueue(q, *t.RightChild);
	}
}

void levelOrderInQueue(BinaryTree *root) {//队列实现二叉树层序遍历
	if (!root)
		return;
	Queue *q = NULL;
	initQueue(&q);
	enterQueue(q, *root);
	levelOrder(q);
	//levelOrderRe(q);
}

void preOrderInStackRe(Stack *s) {
	if (isEmpty(s))
		return;
	BinaryTree t;
	pop(s, &t);
	printf("%c", t.c);
	if (t.RightChild)
		push(s, *t.RightChild);
	if (t.LeftChild)
		push(s, *t.LeftChild);
	preOrderInStackRe(s);
}

void preOrderInStackNoRe(Stack *s) {
	BinaryTree t;
	while (!isEmpty(s)) {
		pop(s, &t);
		printf("%c", t.c);
		if (t.RightChild)
			push(s, *t.RightChild);
		if (t.LeftChild)
			push(s, *t.LeftChild);
	}
}

void preOrderInStack(BinaryTree *root) {
	Stack *s = NULL;
	initStack(&s);
	push(s, *root);
	preOrderInStackNoRe(s);
}

void midOrderInStackRe(Stack *s) {///////未完成
	if (s->top == -1)
		return;
	BinaryTree top;
	pop(s, &top);
	if (top.RightChild) {
		push(s, *top.RightChild);
	}
	push(s, top);
	if (top.LeftChild) {
		push(s, *top.LeftChild);
	}
	else
		return;
	midOrderInStackRe(s);
	if (top.LeftChild&&pop(s, &top))
		printf("%c", top.c);
	if (top.RightChild&&pop(s, &top))
		printf("%c", top.c);

}

void midOrderInStackNoRe(Stack *s) {
	BinaryTree t;
	while (!isEmpty(s)) {
		while (getTop(s, &t), t.LeftChild)
			push(s, *t.LeftChild);
		if (pop(s, &t))
			printf("%c", t.c);
		if (pop(s, &t))
			printf("%c", t.c);
		if (t.RightChild)
			push(s, *t.RightChild);
	}
}

void midOrderInStack(BinaryTree *root) {
	Stack *s = NULL;
	initStack(&s);
	push(s, *root);
	midOrderInStackNoRe(s);
}

void postOrderInStackRe(Stack *s) {
	BinaryTree t;
	getTop(s, &t);
	if (t.RightChild) {
		push(s, *t.RightChild);
		postOrderInStackRe(s);
	}
	if (t.LeftChild) {
		push(s, *t.LeftChild);
		postOrderInStackRe(s);
	}
}

void postOrderInStackNoRe(Stack *s) {//未完成
	BinaryTree t;
	while (!isEmpty(s)) {
	}
}

void postOrderInStack(BinaryTree *root) {
	Stack *s = NULL;
	initStack(&s);
	push(s, *root);
	BinaryTree t;
	//递归进出栈
	postOrderInStackRe(s);
	while (!isEmpty(s)) {
		pop(s, &t);
		printf("%c", t.c);
	}
}

