#include"pch.h"

///////////////////��ӽ���ʱ      ���Ŷ�ַ����ʹhashʧȥ����

unsigned int hashCode(char * key) {
	unsigned int hash = 0;
	while (*key) {
		hash = hash * 33 + *key;
		key++;
	}
	return hash;
}

void initHashTable(HashTable *table) {
	table->table = (KV *)malloc(sizeof(KV)*TABLESIZE);
	memset(table->table, 0, sizeof(KV)*TABLESIZE);
	table->cnt = 0;
	table->delFlag = malloc(1);
	table->tableSize = TABLESIZE;
}

int search(HashTable *table, char *key) {//����̽�ⷨ
	int hash = 0;//= hashCode(key) + 0 , re = hash;
	int i = 0;
	do {
		hash = (hashCode(key) + i++)%table->tableSize;
		if (i >= table->tableSize) {
			printf("����\n");
			return -1;
		}
	} while (table->table[hash].key
		//&&  table->table[hash].key != table->delFlag
		&& strcmp(key, table->table[hash].key));//out : NULL  /  find key
	return hash;
}

int searchRandom(HashTable *table, char *key) {//���̽�ⷨ
	int hash = 0;
	int i = 0;
	srand(1);
	do {
		hash = (hashCode(key) + rand()%table->tableSize) % table->tableSize;
		i++;
		if (i >= table->tableSize) {
			printf("����\n");
			return -1;
		}
	} while (table->table[hash].key
		&&  strcmp(key, table->table[hash].key));//NULL / DEL
	return hash;
}

int put(HashTable *table, char *key, void *value) {
	int hash = search(table, key);
	if (hash == -1)
		return 0;
	//printf("%d\n", hash);
	if (table->table[hash].key) {//����valueֵ
		if (table->table[hash].key != table->delFlag) {//��ΪDEL
			free(table->table[hash].value);
		}
		else {//DEL   value��free
			table->table[hash].key = key;
			table->cnt++;
		}
		table->table[hash].value = value;
	}
	else {//�µ�����
		table->table[hash].key = key;
		table->table[hash].value = value;
		table->cnt++;
	}
	if (table->cnt*1.25 > table->tableSize) {
		extendTable(table);
	}
	return 1;
}

void *get(HashTable *table, char *key) {
	int hash = search(table, key);
	if (hash == -1)
		return NULL;
	return table->table[hash].key == table->delFlag ? NULL : table->table[hash].value;
}

int remove(HashTable *table, char *key) {
	int hash = search(table, key);
	if (hash == -1 || table->table[hash].key == NULL || table->table[hash].key == table->delFlag)
		return 0;
	free(table->table[hash].key);
	table->table[hash].key = (char *)table->delFlag;
	free(table->table[hash].value);
	table->cnt--;
	return 1;
}

void extendTable(HashTable *table) {//��չ��
	KV *pre = table->table;
	table->table = (KV *)malloc(sizeof(KV) * table->tableSize * 2);//table->cnt?//ʹ��reallocԭ���ݶѻ�
	memset(table->table, 0, sizeof(KV)*table->tableSize * 2);
	table->tableSize *= 2;
	for (int i = 0, cnt = 0; cnt < table->cnt; i++) {
		if (pre[i].key) {
			table->cnt--;
			put(table, pre[i].key, pre[i].value);
			cnt++;
		}
	}
	free(pre);
}