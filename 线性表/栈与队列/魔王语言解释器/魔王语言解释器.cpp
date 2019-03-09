#include"pch.h"
#include"Stack.h"
#include"String.h"
///高级规则    用大小写字母区分

int amount = 0;
char source[NUM][LEN], object[NUM][LEN];

void go_on() {
	printf("按任意键继续");
	getch();
	getch();
}

int confirm() {
	char choice[25] , flag = 1;
	printf("是否确认本次操作?(0/1):");
	do {
		if (flag == 0) {
			printf("请输入0或1表示选择\n");
		}
		scanf("%s", choice);
	} while (choice[0] != '0' && choice[0] != '1');
	return choice[0] - '0';
}

void menu() {
	system("cls");
	printf("\t\t    欢迎使用魔王语言解释器\n\n");
	printf("\t\t\t1.查看已有规则\n");
	printf("\t\t\t2.录入新的规则\n");
	printf("\t\t\t3.删改规则顺序\n");
	printf("\t\t\t4.开始语言解释\n");
	printf("\t\t\t0.退出该解释器\n");
	printf("请选择:");
}

int import_rule() {//从文件中读入规则
	int i = 0, j = 0;
	FILE *fp = fopen("TheLanguageOftheKingOftheDevil.rule", "r");
	if (fp == NULL) { printf("文件丢失！\n"); return 0; }
	while (fscanf(fp,"%s   →   %s", source[i++], object[j++]) != EOF);
	if (i != j) {
		printf("文件损坏！");
	}
	fclose(fp);
	return i-1;
}

void write_rule() {
	int i;
	FILE *fp = fopen("TheLanguageOftheKingOftheDevil.rule", "w");
	for (i = 0; i < amount; i++) {
		fprintf(fp, "%s   →   %s\n", source[i], object[i]);
	}
	fclose(fp);
}

void check_rule() {
	system("cls");
	printf("\t\t高等规则\n");
	printf("\tα   →   β1β2…βm\n");
	printf("\t(θδ1δ2…δn)   →   θδnθδn－1… θδ1θ\n\n");
	printf("\t\t当前规则\n");
	int i = 0;
	while (i < amount) {
		printf("\t%d、\t%s   →   %s\n", i + 1, source[i], object[i]);
		i++;
	}
}

int checkBracket(char *s) {//检查括号是否匹配
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

void EliminateBracket(String *s, int left, int right) {//left、right 左右括号的位置
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
	StringReplace(s, left, right-left+1, resub);//int pos, int subLen  这个方法的第三个参数为被替换串的串长
	left = StringLastIndexOf(s, '('), right = StringIndexOf(s, ')');
	EliminateBracket(s, left, right);//递归消除括号
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
	printf("请输入要转换的魔王词汇:");
	scanf("%s", from);
	printf("请输入该词汇对应的内容:");
	scanf("%s", to);
	if (confirm()) {
		strcpy(source[amount], from);
		strcpy(object[amount++], to);
		//保存到文件
		write_rule();
	}
	else {//取消
		printf("本次修改已取消");
	}
}

void sort_rule() {
	printf("现在一共有%d条规则,如下所示:\n", amount);
	int i = 0, j;
	while (i < amount) {
		printf("\t%d、\t%s   →   %s\n", i + 1, source[i], object[i]);
		i++;
	}
	printf("输入%d个数表示当前规则的新序号，新序号-1则表示删除该条规则\n,保留的规则序号按先后顺序从小到大\n请输入:",amount);
	int order[NUM], cnt = 0;
	char Tsource[NUM][LEN], Tobject[NUM][LEN];
	for (i = 0; i < amount; i++) {
		scanf("%d", &order[i]);
		if (order[i] != -1)
			cnt++;
		strcpy(Tsource[i], source[i]);
		strcpy(Tobject[i], object[i]);
	}
	for (i = 1; i < cnt; i++) {//根据order排序
		for (j = 0; j < amount; j++) {
			if (order[j] == i)
			break;
		}
		strcpy(source[i - 1], Tsource[j]);
		strcpy(object[i - 1], Tobject[j]);
	}
	amount = cnt;
	write_rule();
	printf("修改已完成\n");
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
		case '4':printf("请输入待解释字符串:"); scanf("%s", s->str); use_rule(s); printf("结果为:%s\n",s->str); break;
		case '0':exit(0); break;
		default:
			printf("输入有误，请重新选择\n");
			break;
		}
		go_on();
	}
	return 0;
}