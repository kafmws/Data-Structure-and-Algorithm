#pragma once

#include"pch.h"

#define TreeSize 100

typedef char TreeElement;

typedef struct node {
	TreeElement c;
	struct node *LeftChild;
	struct node *RightChild;
}BinaryTree;

typedef enum {
	THREAD,
	LINK,
}Tag;

typedef struct threadNode {
	TreeElement data;
	Tag LeftTag;
	Tag RightTag;
	struct threadNode *Left;
	struct threadNode *Right;
}ThreadBinaryTree;

void createBinaryTreeByPM(TreeElement pre[], int pstart, int pend, TreeElement mid[], int mstart, int mend, BinaryTree **root);

void createBinaryTreeByMP(TreeElement mid[], int mstart, int mend, TreeElement post[], int pstart, int pend, BinaryTree ** root);

