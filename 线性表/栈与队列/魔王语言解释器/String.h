#include"pch.h"

#define STR 101

typedef struct {
	char *str;
	int maxlen;
}String;

void initString(String *s);

int StringIndexOf(String *s, char sub[]);

int StringIndexOf(String *s, char c);

int StringLastIndexOf(String *s, char c);

void StringCat(String *s, char sub[]);

void StringReplace(String *s, char sub[], char obj[]);

void StringReplace(String *s, int pos, int subLen, char obj[]);

void StringReplaceAll(String *s, char sub[], char obj[]);

void StringInsert(String *s, int pos, char in[]);

char *SubString(String *s, int begin, int end, char *des);

char *StringReverse(char *str);