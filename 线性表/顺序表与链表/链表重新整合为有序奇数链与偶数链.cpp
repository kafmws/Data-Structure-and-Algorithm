#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Node {
	int num;
	struct Node *next;
} node;

void create(node *head) {
	node *p = NULL;
	printf("请输入数据的个数:");
	int n, num;
	scanf("%d", &n);
	while (n--) {
		scanf("%d", &num);
		p = (node *)malloc(sizeof(node));
		p->num = num;
		p->next = head->next;
		head->next = p;
	}
}

void initHeadNode(node **head) {
	*head = (node *)malloc(sizeof(node));
	(*head)->next = NULL;
}

void sort(node *head, node *phead, node *qhead) {
	node *p = NULL, *q = NULL, *tem = NULL;
	node *ptail = p, *qtail = q;
	head = head->next;
	while (head) {
		tem = head->next;
		if (head->num % 2) {
			q = qhead;
			while (q->next&&q->next->num <= head->num)
				q = q->next;
			head->next = q->next;
			q->next = head;
		}
		else { //偶
			p = phead;
			while (p->next&&p->next->num <= head->num)
				p = p->next;
			head->next = p->next;
			p->next = head;
		}
		head = tem;
	}
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
	initHeadNode(&q);
	initHeadNode(&p);
	create(head);
	sort(head, p, q);
	printf("奇数链为:");
	print(q);
	printf("偶数链为:");
	print(p);
}

