#include<stdio.h>
#include<string.h>

int judge(char* str, int len) {
	char exam[10005];//    i           str:   j
	//int flag;
	exam[0] = str[0];
	int i = 1, j = 1;
	while (j < len) {
		exam[i++] = str[j++];
		if (i > 1)
			if (exam[i - 2] == '('&&exam[i - 1] == ')' || exam[i - 2] == '['&&exam[i - 1] == ']') {
				i -= 2;
			}
	}
	return i;
}

int main() {
	int n;
	scanf("%d", &n);
	char source[10005];
	while (n--) {
		scanf("%s", source);
		int len = strlen(source);
		if (len % 2 == 0 && judge(source, len)==0) {
			printf("Yes\n");
		}
		else {
			printf("No\n");
		}
	}
	return 0;
}
