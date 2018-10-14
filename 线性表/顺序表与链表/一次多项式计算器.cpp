#include<stdio.h>
#include<stdlib.h>

typedef struct PolyStruct {
	int coef;
	int exp;
	struct PolyStruct *next;
} Poly;

typedef struct ListStruct {
	Poly *head;
	Poly *tail;
} List;

void initHeadNode(List *list) {
	list->head = (Poly *)malloc(sizeof(Poly));
	list->head->next = NULL;
	list->tail = list->head;
}

void print(List list) {
	Poly *p = list.head->next;
	if (p) {
		if (p->exp == 0)printf("%d", p->coef);
		else {
			if (p->coef != 1)printf("%d", p->coef);
			if (p->exp != 1)
				printf("X^%d", p->exp);
			else
				printf("X");
		}
		if (p)p = p->next;
		for (; p ; p = p->next) {
			if (p->exp == 0) {
				printf("%+d", p->coef);
			} else if (p) {
				if (p->coef != 1)printf("%+d", p->coef);
				if (p->exp != 1)
					printf("X^%d", p->exp);
				else
					printf("X", p->coef);
			}
		}
	} else {
		printf("0");
	}
	printf("\n");
}

void initPoly(List *list) {
	printf("请输入系数与指数,系数为0表示结束:\n");
	int coef, exp;
	Poly *p;
	scanf("%d%d", &coef, &exp);
	list->head->coef = 0;
	if (coef)
		do {
			p = (Poly *)malloc(sizeof(Poly));
			p->coef = coef;
			p->exp = exp;
			p->next = NULL;
			list->tail->next = p;
			list->tail = p;
			list->head->coef++;//计数，保存多项式的项数
		} while (scanf("%d%d", &coef, &exp) && coef != 0);
	print(*list);
}

void appendNode(List *list, Poly *node) {//复制单项式至list尾部
	Poly *p = (Poly *)malloc(sizeof(Poly));
	p->coef = node->coef;
	p->exp = node->exp;
	p->next = NULL;
	list->tail->next = p;
	list->tail = p;
}

void addApdNode(List *list, Poly *p1, Poly *p2) {//将两个单项式合并后增加至list尾部
	Poly *p;
	if (p1->coef + p2->coef) {
		p = (Poly *)malloc(sizeof(Poly));
		p->coef = p1->coef + p2->coef;
		p->exp = p1->exp;
		p->next = NULL;
		list->tail->next = p;
		list->tail = p;
	}
}

void multiplyApdNode(List *list, Poly *p1, Poly *p2) {
	Poly *p = (Poly *)malloc(sizeof(Poly));
	p->coef = p1->coef*p2->coef;
	p->exp = p1->exp + p2->exp;
	p->next = NULL;
	list->tail->next = p;
	list->tail = p;
}

void add(List *list, List list1, List list2) {
	Poly *p1 = list1.head->next, *p2 = list2.head->next;
	while (p1&&p2) {
		if (p1->exp < p2->exp) {
			appendNode(list, p1);
			p1 = p1->next;
		} else if (p1->exp == p2->exp) {
			addApdNode(list, p1, p2);
			p1 = p1->next;
			p2 = p2->next;
		} else {
			appendNode(list, p2);
			p2 = p2->next;
		}
	}
	while (p1) {
		appendNode(list, p1);
		p1 = p1->next;
	}
	while (p2) {
		appendNode(list, p2);
		p2 = p2->next;
	}
}

void minus(List *list, List list1, List list2) {
	Poly *p = NULL;
	for (p = list2.head->next; p; p = p->next) {
		p->coef *= -1;
	}
	add(list, list1, list2);
}

void multiply(List *list, List list1, List list2) {
	int size = list1.head->coef;
	size = size*2-1;
	List tem[size];
	int i;
	Poly *p = list1.head->next, *q = list2.head->next;
	for (i = 0; i < size; i++) {
		initHeadNode(&tem[i]);
	}
	i = 0;
	while (p) {
		for (; q; q = q->next) {
			if (p->exp + q->exp)
				multiplyApdNode(&tem[i], p, q);
		}
		i++;
		p = p->next;
		q = list2.head->next;
	}
	for (i = 1; i < size; i++) {
		add(&tem[(size+1)/2+i-1], tem[(size+1)/2+i-2], tem[i]);
	}
	list->head = tem[size-1].head;
	list->tail = tem[size-1].tail;
}

void derivative(List *result, List list) {
	Poly *p = list.head->next;
	Poly *t = NULL;
	for (; p; p = p->next) {
		if (p->exp) {
			t = (Poly *)malloc(sizeof(Poly));
			t->coef = p->coef*p->exp;
			t->exp = p->exp - 1;
			t->next = NULL;
			result->tail->next = t;
			result->tail = t;
		}
	}
}

int main() {
	List list[7];
	for (int i = 0; i <= 6; i++) {
		initHeadNode(&list[i]);
	}
	printf("请录入两个多项式\n");
	initPoly(&list[0]);
	initPoly(&list[1]);
	int choice;
	add(&list[2], list[0], list[1]);
	derivative(&list[5], list[0]);
	while(1) {
		printf("1.两式相加\n2.两式相减\n3.两式相乘\n4.求导\n");
		printf("请选择:");scanf("%d", &choice);
		switch (choice) {
			case 1:
				print(list[2]);
				break;
			case 2:
				minus(&list[3], list[0], list[1]);
				print(list[3]);
				break;
			case 3:
				multiply(&list[6], list[0], list[1]);
				print(list[6]);
				break;
			case 4:
				print(list[5]);
				break;
		}
	}
}
