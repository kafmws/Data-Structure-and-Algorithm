#include"pch.h"
#include"Stack.h"
#include<stdio.h>

#define MAX 100
#define X 0
#define Y 1
////////////////////////////////////  y  →
////////////////////////////////////  x  ↓
int n, m;
int map[MAX][MAX];
int book[MAX][MAX] = { 0 };
int steps[4][2] = { {0,1}, {1,0}, {0,-1},{-1,0} };//  →  ↓  ←  ↑
Stack *stack = NULL;

void importMap() {
	int i, j;
	printf("请输入迷宫的行列数：");
	scanf("%d%d", &n, &m);
	printf("请键入迷宫：\n");
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
			case 0:printf("○"); break;
			case 1:printf("×"); break;
			case 9:printf("●"); break;
			default:printf("DATA ERROR");exit(0);break;
			}
		}
		printf("\n");
	}
}

int process(Coord begin, Coord end) {
	int flag = 1;
	push(stack, begin);//设置起点
	book[begin.x][begin.y] = 1;
	Coord *top = (Coord *)malloc(sizeof(Coord));
	*top= begin;//栈顶坐标初始化
	Coord tem = { 0, 0 ,0 };
	while (top->x != end.x||top->y != end.y) {
		if (flag)
			top->step = 0;
		else
			top->step++;//回溯后继续尝试
		do {
			tem = *top;
			tem.x += steps[top->step][X];
			tem.y += steps[top->step][Y];
			if (0 <= tem.x&&tem.x < n && 0 <= tem.y&&tem.y < m && 
				map[tem.x][tem.y] == 0&& book[tem.x][tem.y] ==0){
				flag = 1;//可行
			}
			else {
				flag = 0;
				top->step++;
			}
		} while (top->step <= 3 && !flag);//不可行且有余地时继续寻找
		if (flag) {//可行
			push(stack, tem);
			book[tem.x][tem.y] = 1;//标记
		}
		else { //此处无解
			pop(stack, &tem);
			book[tem.x][tem.y] = 0;//去除标记
			if (isEmpty(stack))//无解
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
	printf("请输入起点坐标：\n");
	scanf("%d%d",&i ,&j );
	begin.x = i, begin.y = j;
	printf("请输入终点坐标：\n");
	scanf("%d%d",&i ,&j );
	end.x = i, end.y = j;
	if (process(begin, end)) {
		bookTrace();
		print();
	}
	else
		printf("无解\n");
	return 0;
}