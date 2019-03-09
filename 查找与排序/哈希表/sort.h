#pragma once

const int MAXSIZE = 1005;

//typedef unsigned char SortType;
typedef int SortType;

typedef struct {
	SortType num[MAXSIZE];
	int length;
}Array;

void print(Array * a);

void DirectInsertSort(Array * a);

void BinarySearchDirectInsertSort(Array * a);

void ShellSort(Array * a);

void BubbleSort(Array * a);

void QuickSort(Array * a);
