#pragma once

typedef char TreeElement;

typedef struct node {
	TreeElement c;
	struct node *LeftChild;
	struct node *RightChild;
}BinaryTree;