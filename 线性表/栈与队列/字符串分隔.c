#include<stdio.h>
#include<string.h>

int main() { // + - * / ( )
	char res[100][21];
	char str[21];
	char c;
	int i = 0, j = 0;
	while ((c = getchar()) != '\n') {
		if (c != '+'&&c != '-'&&c != '*'&&c != '/'&&c != '('&&c != ')') {
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
	for (j = 0; j < i; j++) {
		printf("%s ", res[j]);
	}
	return 0;
}
