#pragma once

const int TABLESIZE = 15;

typedef struct {
	char *key;
	void *value;
}KV;

typedef struct {
	KV *table;
	void *delFlag;
	int cnt;
	int tableSize;
}HashTable;

unsigned int hashCode(char * key);

void initHashTable(HashTable * table);

int search(HashTable * table, char * key);

int put(HashTable * table, char * key, void * value);

void * get(HashTable * table, char * key);

int remove(HashTable * table, char * key);

void extendTable(HashTable * table);
