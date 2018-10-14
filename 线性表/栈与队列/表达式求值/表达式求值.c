#include"pch.h"
#include"Stack.h"
#include<stdlib.h>
#include<math.h>

inline int isDigit(int x) {
	return '0' <= x && x <= '9' || x == '.';
}

int process(char res[SIZE][21]) {//分隔操作数与操作符
	char str[21];
	char c;
	int i = 0, j = 0;
	while ((c = getchar()) != '\n') {
		if (isDigit(c)) {//c != '+'&&c != '-'&&c != '*'&&c != '/'&&c != '('&&c != ')'
			str[j++] = c;
		}
		else {
			if (j != 0) {
				str[j] = 0;
				strcpy(res[i++], str);
				j = 0;
			}
			res[i][0] = c;
			res[i++][1] = 0;
		}
	}
	str[j] = 0;
	strcpy(res[i++], str);
	return i;//返回元素个数
}

int judge(char c) {//min值为1
	int flag = 0;
	switch (c){
		case 0:flag = 0; break;
		case '(': flag = 0; break;
		case '+': flag = 1; break;
		case '-': flag = 1; break;
		case '*': flag = 2; break;
		case '/': flag = 2; break;
		case '^': flag = 3; break;
	}
	return flag;
}

double caculate(Stack *num, Stack *operator) {//进行一次弹栈运算  返回结果
	char c;
	double a, b, re, t;
	pop(operator, &t);
	pop(num, &b);
	pop(num, &a);
	c = (int)t;
	switch (c){
		case '+':re = a + b; break;
		case '-':re = a - b; break;
		case '*':re = a * b; break;
		case '/':re = a / b; break;
		case '^':re = pow(a, b); break;
	}
	return re;
}

int main() {
	char res[SIZE][21];
	printf("请输入计算式：\n");
	int size = process(res);//size  数据个数
	Stack *num, *operator;
	if (!initStack(&num) || !initStack(&operator)) { printf("初始化出错！"); return -1; }
	int i, top, now;
	for (i = 0; i < size; i++) {
		if (isDigit(res[i][0])) {//操作数
			push(num, atof(res[i]));
		}
		else if (res[i][0] == '(') {
			push(operator,res[i][0]);
		}
		else {//运算符
			if (res[i][0] != ')') {//  非 )
				double tem = 0;
				now = judge(res[i][0]);//计算当前运算符优先级
				do {
					getTop(operator,&tem);//取得栈顶运算符
					top = judge((int)tem);//计算栈顶运算符优先级
					if (now > top)
						push(operator,res[i][0]);
					else {//弹栈运算      **运算结果入栈
						push(num, caculate(num, operator));
					}
				} while (now <= top);
			}
			else {//  当前运算符为  )
				double tem;
				while (getTop(operator,&tem) && ((int)tem != '(')) {//此时栈不可能为空
					push(num, caculate(num, operator));
				}
				pop(operator,&tem);//弹出  (
			}
		}
	}
	while (!isEmpty(operator)) {
		push(num, caculate(num, operator));
	}
	if (num->top != 0)
		printf("计算出错！\n");
	double result;
	getTop(num, &result);
	printf("%g", result);
	return 0;
}