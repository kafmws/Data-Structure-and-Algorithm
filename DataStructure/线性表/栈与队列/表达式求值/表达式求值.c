#include"pch.h"
#include"Stack.h"
#include<stdlib.h>
#include<math.h>

inline int isDigit(int x) {
	return '0' <= x && x <= '9' || x == '.';
}

int process(char res[SIZE][21]) {//�ָ��������������
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
	return i;//����Ԫ�ظ���
}

int judge(char c) {//minֵΪ1
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

double caculate(Stack *num, Stack *operator) {//����һ�ε�ջ����  ���ؽ��
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
	printf("���������ʽ��\n");
	int size = process(res);//size  ���ݸ���
	Stack *num, *operator;
	if (!initStack(&num) || !initStack(&operator)) { printf("��ʼ������"); return -1; }
	int i, top, now;
	for (i = 0; i < size; i++) {
		if (isDigit(res[i][0])) {//������
			push(num, atof(res[i]));
		}
		else if (res[i][0] == '(') {
			push(operator,res[i][0]);
		}
		else {//�����
			if (res[i][0] != ')') {//  �� )
				double tem = 0;
				now = judge(res[i][0]);//���㵱ǰ��������ȼ�
				do {
					getTop(operator,&tem);//ȡ��ջ�������
					top = judge((int)tem);//����ջ����������ȼ�
					if (now > top)
						push(operator,res[i][0]);
					else {//��ջ����      **��������ջ
						push(num, caculate(num, operator));
					}
				} while (now <= top);
			}
			else {//  ��ǰ�����Ϊ  )
				double tem;
				while (getTop(operator,&tem) && ((int)tem != '(')) {//��ʱջ������Ϊ��
					push(num, caculate(num, operator));
				}
				pop(operator,&tem);//����  (
			}
		}
	}
	while (!isEmpty(operator)) {
		push(num, caculate(num, operator));
	}
	if (num->top != 0)
		printf("�������\n");
	double result;
	getTop(num, &result);
	printf("%g", result);
	return 0;
}