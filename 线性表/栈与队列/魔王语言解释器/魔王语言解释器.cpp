#include"pch.h"
#include"Stack.h"
#include"String.h"
///�߼�����    �ô�Сд��ĸ����

int amount = 0;
char source[NUM][LEN], object[NUM][LEN];

void go_on() {
	printf("�����������");
	getch();
	getch();
}

int confirm() {
	char choice[25] , flag = 1;
	printf("�Ƿ�ȷ�ϱ��β���?(0/1):");
	do {
		if (flag == 0) {
			printf("������0��1��ʾѡ��\n");
		}
		scanf("%s", choice);
	} while (choice[0] != '0' && choice[0] != '1');
	return choice[0] - '0';
}

void menu() {
	system("cls");
	printf("\t\t    ��ӭʹ��ħ�����Խ�����\n\n");
	printf("\t\t\t1.�鿴���й���\n");
	printf("\t\t\t2.¼���µĹ���\n");
	printf("\t\t\t3.ɾ�Ĺ���˳��\n");
	printf("\t\t\t4.��ʼ���Խ���\n");
	printf("\t\t\t0.�˳��ý�����\n");
	printf("��ѡ��:");
}

int import_rule() {//���ļ��ж������
	int i = 0, j = 0;
	FILE *fp = fopen("TheLanguageOftheKingOftheDevil.rule", "r");
	if (fp == NULL) { printf("�ļ���ʧ��\n"); return 0; }
	while (fscanf(fp,"%s   ��   %s", source[i++], object[j++]) != EOF);
	if (i != j) {
		printf("�ļ��𻵣�");
	}
	fclose(fp);
	return i-1;
}

void write_rule() {
	int i;
	FILE *fp = fopen("TheLanguageOftheKingOftheDevil.rule", "w");
	for (i = 0; i < amount; i++) {
		fprintf(fp, "%s   ��   %s\n", source[i], object[i]);
	}
	fclose(fp);
}

void check_rule() {
	system("cls");
	printf("\t\t�ߵȹ���\n");
	printf("\t��   ��   ��1��2����m\n");
	printf("\t(�Ȧ�1��2����n)   ��   �Ȧ�n�Ȧ�n��1�� �Ȧ�1��\n\n");
	printf("\t\t��ǰ����\n");
	int i = 0;
	while (i < amount) {
		printf("\t%d��\t%s   ��   %s\n", i + 1, source[i], object[i]);
		i++;
	}
}

int checkBracket(char *s) {//��������Ƿ�ƥ��
	Stack sstack;
	Stack *stack = &sstack;
	for (int i = 0; i < strlen(s); i++) {
		if (s[i] == '(') {
			push(stack, s[i]);
		}
		else if (s[i] == ')') {
			if (stack->data[stack->top] == '(')
				stack->top--;
			else
				push(stack, s[i]);
		}
	}
	if (stack->top == -1)
		return 1;
	return 0;
}

void EliminateBracket(String *s, int left, int right) {//left��right �������ŵ�λ��
	if (right <= left)
		return;
	char *str = s->str;
	char sub[NUM];
	SubString(s, left+2, right-1, sub);
	char re = str[left + 1];
	StringReverse(sub);
	char resub[NUM*2+1];
	int i, j;
	for (i = 0, j = 0; i < strlen(sub); i++) {
		resub[j++] = re;
		resub[j++] = sub[i];
	}
	resub[j++] = re;
	resub[j] = 0;
	StringReplace(s, left, right-left+1, resub);//int pos, int subLen  ��������ĵ���������Ϊ���滻���Ĵ���
	left = StringLastIndexOf(s, '('), right = StringIndexOf(s, ')');
	EliminateBracket(s, left, right);//�ݹ���������
}

void use_rule(String *s) {
	int i;
	for (i = 0; i < amount;i++) {
		StringReplaceAll(s, source[i], object[i]);
	}
	EliminateBracket(s, StringLastIndexOf(s, '('), StringIndexOf(s, ')'));
}

void add_rule() {
	char from[NUM], to[NUM];
	printf("������Ҫת����ħ���ʻ�:");
	scanf("%s", from);
	printf("������ôʻ��Ӧ������:");
	scanf("%s", to);
	if (confirm()) {
		strcpy(source[amount], from);
		strcpy(object[amount++], to);
		//���浽�ļ�
		write_rule();
	}
	else {//ȡ��
		printf("�����޸���ȡ��");
	}
}

void sort_rule() {
	printf("����һ����%d������,������ʾ:\n", amount);
	int i = 0, j;
	while (i < amount) {
		printf("\t%d��\t%s   ��   %s\n", i + 1, source[i], object[i]);
		i++;
	}
	printf("����%d������ʾ��ǰ���������ţ������-1���ʾɾ����������\n,�����Ĺ�����Ű��Ⱥ�˳���С����\n������:",amount);
	int order[NUM], cnt = 0;
	char Tsource[NUM][LEN], Tobject[NUM][LEN];
	for (i = 0; i < amount; i++) {
		scanf("%d", &order[i]);
		if (order[i] != -1)
			cnt++;
		strcpy(Tsource[i], source[i]);
		strcpy(Tobject[i], object[i]);
	}
	for (i = 1; i < cnt; i++) {//����order����
		for (j = 0; j < amount; j++) {
			if (order[j] == i)
			break;
		}
		strcpy(source[i - 1], Tsource[j]);
		strcpy(object[i - 1], Tobject[j]);
	}
	amount = cnt;
	write_rule();
	printf("�޸������\n");
}

int main() {
	//return 0;
	char choice[20];
	amount = import_rule();
	String ss;
	String *s = &ss;
	initString(s);
	while (1) {
		menu();
		scanf("%s", choice);
		switch (choice[0]){
		case '1':check_rule(); break;
		case '2':add_rule(); break;
		case '3':sort_rule(); break;
		case '4':printf("������������ַ���:"); scanf("%s", s->str); use_rule(s); printf("���Ϊ:%s\n",s->str); break;
		case '0':exit(0); break;
		default:
			printf("��������������ѡ��\n");
			break;
		}
		go_on();
	}
	return 0;
}