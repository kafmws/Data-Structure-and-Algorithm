#include"pch.h"

void put(HashTable *table) {
	while (1) {
		int len;
		char str[100] = { 0 };
		rewind(stdin);
		scanf("%[^\n]s", str);
		if (len = strlen(str)) {
			char *key = (char *)malloc(sizeof(char) * len + 1);
			strcpy(key, str);
			int *value = (int *)malloc(sizeof(int));
			scanf("%d", value);
			put(table, key, value);
		}
		else
			break;
	}
}

void print(HashTable *table) {
	if (table->cnt)
		printf("key\t\t\tvalue\n");
	for (int i = 0, cnt = 0; cnt < table->cnt; i++) {
		if (table->table[i].key && table->table[i].key != table->flag) {
			cnt++;
			//printf("%s\t\t%4d\n", table->table[i].key, *(int *)table->table[i].value);
			printf("%-15s\t\t%4d	%d\n", table->table[i].key, *(int *)table->table[i].value,hashCode(table->table[i].key)%TABLESIZE);
		}
	}
	if (table->cnt)
		printf("共%d个\n", table->cnt);
}

void show() {
	system("cls");
	puts("\n\t\t\t    HashTableTest\n");
	puts("\t\t\t\t1.put\n");
	puts("\t\t\t\t2.get\n");
	puts("\t\t\t\t3.remove\n");
	puts("\t\t\t\t4.print\n");
	puts("\t\t\t\t5.ASL");
}

void calculate(HashTable *table) {
	int ASL = 0;
	for (int i = 0, cnt = 0; cnt < table->cnt; i++) {
		if (table->table[i].key&&table->table[i].key != table->flag) {
			cnt++;
			int time = 0,hash = -1;
			hash = hashCode(table->table[i].key)%TABLESIZE;
			while (hash != i)
				hash = (hash+1)%TABLESIZE,time++;
			ASL += time;
		}	
	}
	printf("ASL = %f\n", ASL*1.0 / table->cnt);
}

int main() {
	HashTable hashTable;
	HashTable *table = &hashTable;
	initHashTable(table);
	int *result = NULL;
	char key[100];
	while (1) {
		show();
		int choice = getchar() - '0';
		getchar();
		switch (choice) {
		case 1:put(table); break;
		case 2:printf("请输入key："); scanf("%s", key); if (result = (int *)get(table, key))printf("%d\n", *result); else puts("not found\n"); rewind(stdin); break;
		case 3:printf("请输入key："); scanf("%s", key); if (!remove(table, key))puts("fail"); else puts("success"); rewind(stdin); break;
		case 4:print(table); break;
		case 5:calculate(table); break;
		}
		getchar();
	}
	return 0;
}