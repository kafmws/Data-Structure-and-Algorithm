#include"pch.h"
#include"Stack.h"
#include<stdio.h>

#define MAX 100
#define X 0
#define Y 1
////////////////////////////////////  y  ��
////////////////////////////////////  x  ��
int n, m;
int map[MAX][MAX];
int book[MAX][MAX] = { 0 };
int steps[4][2] = { {0,1}, {1,0}, {0,-1},{-1,0} };//  ��  ��  ��  ��
Stack *stack = NULL;

void importMap() {
	int i, j;
	printf("�������Թ�����������");
	scanf("%d%d", &n, &m);
	printf("������Թ���\n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			scanf("%d", &map[i][j]);
		}
	}
}

void print() {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			switch (map[i][j]){
			case 0:printf("��"); break;
			case 1:printf("��"); break;
			case 9:printf("��"); break;
			default:printf("DATA ERROR");exit(0);break;
			}
		}
		printf("\n");
	}
}

int process(Coord begin, Coord end) {
	int flag = 1;
	push(stack, begin);//�������
	book[begin.x][begin.y] = 1;
	Coord *top = (Coord *)malloc(sizeof(Coord));
	*top= begin;//ջ�������ʼ��
	Coord tem = { 0, 0 ,0 };
	while (top->x != end.x||top->y != end.y) {
		if (flag)
			top->step = 0;
		else
			top->step++;//���ݺ��������
		do {
			tem = *top;
			tem.x += steps[top->step][X];
			tem.y += steps[top->step][Y];
			if (0 <= tem.x&&tem.x < n && 0 <= tem.y&&tem.y < m && 
				map[tem.x][tem.y] == 0&& book[tem.x][tem.y] ==0){
				flag = 1;//����
			}
			else {
				flag = 0;
				top->step++;
			}
		} while (top->step <= 3 && !flag);//�������������ʱ����Ѱ��
		if (flag) {//����
			push(stack, tem);
			book[tem.x][tem.y] = 1;//���
		}
		else { //�˴��޽�
			pop(stack, &tem);
			book[tem.x][tem.y] = 0;//ȥ�����
			if (isEmpty(stack))//�޽�
				return 0;
		}
		getTop(stack, &top);
	}
	return 1;
}

void bookTrace() {
	for (int i = 0; i <= stack->top; i++) {
		map[stack->data[i].x][stack->data[i].y] = 9;
	}
}

int main() {
	importMap();
	initStack(&stack);
	Coord begin = { 0,0,0 };
	Coord end = { 0,0,0 };
	int i, j;
	printf("������������꣺\n");
	scanf("%d%d",&i ,&j );
	begin.x = i, begin.y = j;
	printf("�������յ����꣺\n");
	scanf("%d%d",&i ,&j );
	end.x = i, end.y = j;
	if (process(begin, end)) {
		bookTrace();
		print();
	}
	else
		printf("�޽�\n");
	return 0;
}