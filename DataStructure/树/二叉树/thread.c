#include"pch.h"

void preThread(ThreadBinaryTree *root, ThreadBinaryTree *pre) {//ǰ��������
	if (root) {

	}
}

void midThread(ThreadBinaryTree *root, ThreadBinaryTree *pre) {//����������
	if (root) {
		midThread(root->Left, pre);
		if (!root->Left) {
			root->LeftTag = THREAD;
			root->Left = pre;
		}
		if (pre&&!pre->Right) {
			pre->RightTag = LINK;
			pre->Right = root;
		}
		midThread(root->Right, root);
	}
}