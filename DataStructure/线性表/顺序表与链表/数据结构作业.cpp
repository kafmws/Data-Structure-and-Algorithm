#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Node {
	int num;
	struct Node *next;
} node;

void create(node *head) {
	node *p;
	int n;
	printf("请录入数据，-1表示结束:");
	while (scanf("%d", &n) && n != -1) {
		p = (node *)malloc(sizeof(node));
		p->num = n;
		p->next = head->next;
		head->next = p;
		head = p;
	}
}

int process(node *head, int k) {
	node *p = head->next;
	int cnt = 1,i = 1;
	while(p->next) {
		p = p->next;
		cnt++;
	}
	if(cnt<k)
		return 0;
	for(p = head->next; i<=cnt-k; p = p->next,i++);
	printf("%d\n",p->num);
	return 1;
}

int main() {
	node *head = (node *)malloc(sizeof(node));
	head->next = NULL;
	create(head);
	int k;
	printf("请输入k:");
	scanf("%d",&k);
	printf("%d",process(head,k));
	return 0;
}
