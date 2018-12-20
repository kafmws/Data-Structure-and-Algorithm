#pragma once

const int TABLESIZE = 200;

typedef struct {
	char *key;
	void *value;
	void *next;
}KV;

typedef struct {
	KV *table;
	void *flag;
	int cnt;
}HashTable;

unsigned int hashCode(char * key);

void initHashTable(HashTable * table);

int search(HashTable * table, char * key);

int put(HashTable * table, char * key, void * value);

void * get(HashTable * table, char * key);

int remove(HashTable * table, char * key);
