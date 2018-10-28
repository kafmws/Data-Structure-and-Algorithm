#include"pch.h"

void initBinaryTreeByExPreOrd(BinaryTree **root) {//扩展二叉树前序创建
	*root = (BinaryTree *)malloc(sizeof(BinaryTree));
	BinaryTree *node = *root;
	scanf("%c", &node->c);
	if (node->c != '#') {
		initBinaryTreeByExPreOrd(&node->LeftChild);
		initBinaryTreeByExPreOrd(&node->RightChild);
	}
	else {
		node->LeftChild = NULL;
		node->RightChild = NULL;
	}
}

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
	printf("%c",root->c);
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
	if(t.LeftChild)
		push(s, *t.LeftChild);
	preOrderInStackRe(s);
}

void preOrderInStackNoRe(Stack *s) {
	BinaryTree t;
	while (!isEmpty(s)) {
		pop(s, &t);
		printf("%c", t.c);
		if(t.RightChild)
			push(s, *t.RightChild);
		if(t.LeftChild)
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
	pop(s,&top);
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
		while(getTop(s, &t), t.LeftChild)
			push(s, *t.LeftChild);
		if(pop(s, &t))
			printf("%c", t.c);
		if(pop(s, &t))
			printf("%c", t.c);
		if(t.RightChild)
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

int lastIndexOf(TreeElement objs[], int len, TreeElement obj) {//未找到返回-1
	if (len < 0)
		return -1;
	for (len--; len >= 0 && objs[len] != obj; len--);
	return len;
}

/*
*	Create BinaryTree from preOrder & midOrder
*	by kafm
*	2018/10/28
*/
void createBinaryTreeByPM(TreeElement pre[], int pstart, int pend, TreeElement mid[], int mstart, int mend, BinaryTree **root) {//下标均可访问
	/*if (pstart > pend || mstart > mend) {
		return ;
	}*/
	*root = (BinaryTree *)malloc(sizeof(BinaryTree));
	(*root)->c = pre[pstart];
	int index = lastIndexOf(mid, strlen(mid), pre[pstart]);
	if (mstart >= index) {//左子树为空
		(*root)->LeftChild = NULL;
	}
	else {//创建左子树
		createBinaryTreeByPM(pre, pstart + 1, pend - mend + index, mid, mstart, index - 1,&((*root)->LeftChild));
	}
	if (mend <= index) {//右子树为空
		(*root)->RightChild = NULL;
	}
	else {//创建右子树
		createBinaryTreeByPM(pre, pend - mend + index +1, pend, mid, index + 1, mend, &((*root)->RightChild));
	}
}

int main() {

	BinaryTree *root = NULL;
	//initBinaryTreeByExPreOrd(&root);
	//printf("递归前序遍历：");
	//preOrder(root);
	//printf("\n递归中序遍历：");
	//midOrder(root);
	//printf("\n递归后序遍历：");
	//postOrder(root);
	//printf("\n队列层序遍历：");
	//levelOrderInQueue(root);//扩展前序序列
	//printf("\n栈中前序遍历：");
	//preOrderInStack(root);
	//printf("\n栈中中序遍历：");
	//midOrderInStack(root);
	//printf("\n栈中后序遍历：");
	//postOrderInStack(root);
	//printf("————————————————\n");
	
	
	/*char *s = "1234566111";
	printf("%d", lastIndexOf(s,10,'0'));*/
	
	
	TreeElement pre[TreeSize], mid[TreeSize];
	printf("请输入先序序列：");
	scanf("%s", pre);
	printf("请输入中序序列：");
	scanf("%s", mid);
	BinaryTree tree;
	createBinaryTreeByPM(pre, 0, strlen(pre) - 1, mid, 0, strlen(mid) - 1, &root);
	preOrder(root);
	printf("\n");
	postOrder(root);
	return 0;
}