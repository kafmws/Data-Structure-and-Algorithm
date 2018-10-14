#include"pch.h"
#include"String.h"

void initString(String *s) {
	s->str = (char *)malloc(sizeof(char)*STR);
	s->maxlen = 100;
}

int StringIndexOf(String *s, char sub[]) {//返回子串开始的下标，无则返回-1
	char *str = s->str;
	int i, j;
	for (i = 0; i < strlen(str); i++) {
		j = 0;
		for (j = 0; j < strlen(sub); j++) {
			if (str[i + j] != sub[j])
				break;
		}
		if (j == strlen(sub)) {
			return i;
		}
	}
	return -1;
}

int StringIndexOf(String *s, char c) {
	char *str = s->str;
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == c)
			return i;
	}
	return -1;
}

int StringLastIndexOf(String *s, char c) {
	char *str = s->str;
	for (int i = strlen(str) - 1; i >=0; i--) {
		if (str[i] == c)
			return i;
	}
	return -1;
}

void StringCat(String *s , char sub[]) {
	char *str = s->str;
	char *re = NULL;
	int len = strlen(str) + strlen(sub);
	if ( len <= s->maxlen) {
		strcat(str,sub);
	}
	else {
		re = (char *)malloc(sizeof(char)*len + 25);
		strcpy(re, str);
		strcat(re, sub);
		free(str);
		s->str = re;
		s->maxlen = len + 24;
	}
}

void StringReplace(String *s, char sub[], char obj[]) {//
	int pos = StringIndexOf(s, sub);
	if (pos == -1)
		return;
	char *str = s->str;
	int subLen = strlen(sub), objLen = strlen(obj);
	char tem[125], *re = NULL;
	strcpy(tem, &str[pos + subLen]);
	int len = strlen(str) - subLen + objLen;
	if (len <= s->maxlen) {
		strcpy(str + pos, obj);
		strcpy(&str[strlen(str)], tem);
	}
	else {
		re = (char *)malloc(sizeof(char)*len + 25);
		strncpy(re, str, pos);
		strcpy(&re[pos],obj);
		strcpy(&re[pos+objLen], tem);
		free(str);
		s->str = re;
		s->maxlen = len + 24;
	}
}

void StringReplace(String *s, int pos, int subLen, char obj[]) {//
	char *str = s->str;
	int objLen = strlen(obj);
	char tem[125], *re = NULL;
	strcpy(tem, &str[pos + subLen]);
	int len = strlen(str) - subLen + objLen;
	if (len <= s->maxlen) {
		strcpy(str + pos, obj);
		strcpy(&str[strlen(str)], tem);
	}
	else {
		re = (char *)malloc(sizeof(char)*len + 25);
		strncpy(re, str, pos);
		strcpy(&re[pos], obj);
		strcpy(&re[pos + objLen], tem);
		free(str);
		s->str = re;
		s->maxlen = len + 24;
	}
}

void StringReplaceAll(String *s, char sub[], char obj[]) {
	int pos;
	int subLen = strlen(sub);
	while ((pos = StringIndexOf(s, sub)) != -1) {
		StringReplace(s, pos, subLen, obj);
	}
}

void StringInsert(String *s , int pos, char in[]) {//从指定位置开始插入字符串
	char *str = s->str;
	char *re = NULL;
	char tem[125];
	strcpy(tem, &str[pos]);
	int requirement = strlen(s->str) + strlen(in);
	if ( requirement <= s->maxlen) {//空间足够
		strcpy(&str[pos], in);
		strcpy(&str[strlen(str)], tem);
	}
	else {
		re = (char *)malloc(sizeof(char)*(requirement + 25));
		strncpy(re, str, pos);
		strcpy(&(re[pos]), in);
		strcpy(&re[strlen(re)], tem);
		free(str);
		s->str = re;
		s->maxlen = requirement + 24;
	}
}

char *SubString(String *s, int begin, int end, char *des) {
	strncpy(des, &(s->str)[begin], end - begin + 1);
	des[end - begin + 1] = 0;
	return des;
}

char *StringReverse(char *str) {
	int i, len = strlen(str);
	char c;
	for (i = 0; i < len / 2; i++) {
		c = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = c;
	}
	return str;
}