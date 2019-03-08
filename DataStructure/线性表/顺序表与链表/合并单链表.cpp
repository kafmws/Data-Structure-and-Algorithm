#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int num;
	struct Node *next;
} node;

void create(node *head) {
	node *p;
	int n;
	while (scanf("%d", &n) && n != -1) {
		p = (node *)malloc(sizeof(node));
		p->num = n;
		p->next = head->next;
		head->next = p;
		head = p;
	}
}

void sort(node *head, node *heada, node *headb) { //a > b
	heada = heada->next, headb = headb->next;
	while (heada&&headb) {
		head->next = headb;
		head = headb;
		headb = headb->next;
		head->next = heada;
		head = heada;
		heada = heada->next;
	}
	head->next = heada;
}

void useSort(node *head, node *phead, node *qhead) {
	node *p = phead, *q = qhead;
	while (p&&q) {
		p = p->next;
		q = q->next;
	}
	if (p == NULL) {
		sort(head, qhead, phead);
	}
	else {
		sort(head, phead, qhead);
	}
}

void initHeadNode(node **head) {
	*head = (node *)malloc(sizeof(node));
	(*head)->next = NULL;
}

void print(node *head) {
	head = head->next;
	while (head->next) {
		printf("%d ", head->num);
		head = head->next;
	}
	printf("%d\n", head->num);
}

int main() {
	node *head, *p, *q;
	initHeadNode(&head);
	initHeadNode(&p);
	initHeadNode(&q);
	create(p);
	create(q);
	useSort(head, p, q);
	free(p);
	free(q);
	print(head);
	return 0;
}

