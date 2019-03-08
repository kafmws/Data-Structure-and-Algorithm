#include<stdio.h>
#include<stdlib.h>
//3172484
typedef struct personStruct {
	int num;
	int password;
	struct personStruct *next;
} Person;

int pnum;

void print(Person *head) {
	Person *phead = head;
	for (; head->next != phead; head = head->next) {
		printf("%d ", head->num);
	}
	printf("%d\n", head->num); 
}

Person *initList(Person *head) {
	int i,password;
	printf("请输入人数:");
	scanf("%d", &pnum);
	Person *p, *tail = head;
	for (i = 1; i <= pnum; i++) {
		p = (Person *)malloc(sizeof(Person));
		p->num = i;
		printf("请输入第%d个人的密码:");
		scanf("%d",&password);
		p->password  = password;
		p->next = NULL;
		if (head == NULL) {
			head = tail = p;
		} else {
			tail->next = p;
			tail = p;
		}
	}
	tail->next = head;
	print(head);
	return head;
}

Person *process(Person *p) {
	int i, begin, value;
	printf("请输入起始编号及起始password:");
	scanf("%d%d", &begin, &value);
	Person *pre = p;
	if (value > pnum) {
		value %= pnum;
		if (value == 0)value = pnum;
	}
	if(begin > pnum) {
		begin %= pnum;
		if(begin == 0)begin = pnum;
	}
	for(i = 1; i<begin; i++,p = p->next);
	for (; pre->next != p; pre = pre->next);
	for (i = 1; pre != p; i++, pre = p, p = p->next) {
		if (i == value) {
			i = 0;
			pnum--;
			printf("%d 退出，新的password为%d\n", p->num, p->password);
			value = p->password;
			if (value > pnum) {
				value %= pnum;
				if (value == 0)value = pnum;
			}
			pre->next = p->next;
			free(p);
			p = pre;
			print(p->next);
		}
	}
	return p;
}

int main() {
	Person *head = NULL;
	head = initList(head);
	head = process(head);
	printf("最后的人是%d,password是%d\n",head->num,head->password);
	system("pause");
	return 0;
}
