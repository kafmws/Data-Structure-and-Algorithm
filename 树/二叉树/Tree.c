#include"pch.h"

void createBinaryTreeByExPreOrd(BinaryTree **root) {//扩展二叉树前序创建
	*root = (BinaryTree *)malloc(sizeof(BinaryTree));
	BinaryTree *node = *root;
	scanf("%c", &node->c);
	if (node->c != '#') {
		createBinaryTreeByExPreOrd(&node->LeftChild);
		createBinaryTreeByExPreOrd(&node->RightChild);
	}
	else {
		node->LeftChild = NULL;
		node->RightChild = NULL;
	}
}

int lastIndexOf(TreeElement objs[], int len, TreeElement obj) {//未找到返回-1
	if (len < 0)
		return -1;
	for (len--; len >= 0 && objs[len] != obj; len--);
	return len;
}

void print(char *s, int begin, int end) {
	for (; begin <= end;) {
		printf("%c",s[begin++]);
	}
}

/*
*	Create BinaryTree from preOrder & midOrder
*	by kafm
*	2018/10/28
*/
void createBinaryTreeByPM(TreeElement pre[], int pstart, int pend, TreeElement mid[], int mstart, int mend, BinaryTree **root) {//下标均可访问
	if (pstart > pend || mstart > mend) {
		*root = NULL;
		return ;
	}
	*root = (BinaryTree *)malloc(sizeof(BinaryTree));
	(*root)->c = pre[pstart];
	int index = lastIndexOf(mid, strlen(mid), pre[pstart]);
	if (mstart >= index) {//左子树为空
		(*root)->LeftChild = NULL;
	}
	else {//创建左子树
		createBinaryTreeByPM(pre, pstart + 1, pend - mend + index, mid, mstart, index - 1,&((*root)->LeftChild));
	}
	if (mend <= index) {//右子树为空
		(*root)->RightChild = NULL;
	}
	else {//创建右子树
		createBinaryTreeByPM(pre, pend - mend + index +1, pend, mid, index + 1, mend, &((*root)->RightChild));
	}
}

/*
*	Create BinaryTree from midOrder & postOrder
*	by kafm
*	2018/10/28
*/
void createBinaryTreeByMP(TreeElement mid[], int mstart, int mend, TreeElement post[], int pstart, int pend, BinaryTree **root) {
	if (mstart > mend || pstart > pend) {
		*root = NULL;
		return;
	}
	*root = (BinaryTree *)malloc(sizeof(BinaryTree));
	(*root)->c = post[pend];
	int index = lastIndexOf(mid, strlen(mid), (*root)->c);//mend - mstart + 1
	if (mstart < index) {//左子树存在
		createBinaryTreeByMP(mid, mstart, index - 1, post, pstart, pstart + index - mstart - 1, &((*root)->LeftChild));
		//printf("创建左子树。mid"); print(mid, mstart, index - 1); printf("post"); print(post, pstart, pstart + index - mstart - 1); printf("\n");
	}
	else
		(*root)->LeftChild = NULL;
	/*if ((*root)->c == 'E')
		printf("\n");//递归代码调试使用*/
	if (index < mend&&index!=-1) {//右子树
		createBinaryTreeByMP(mid, index + 1, mend, post, pstart + index - mstart, pend - 1, &((*root)->RightChild));
		//printf("创建右子树。mid"); print(mid, index + 1, mend); printf("post"); print(post, pstart + index - mstart, pend - 1); printf("\n");
	}
	else
		(*root)->RightChild = NULL;
}

/*
*	draw a horizontal BinaryTree
*	create by kafm
*	2018/10/30
*/
void drawBinaryTree(BinaryTree *root, int height) {
	if (!root)
		return;
	drawBinaryTree(root->RightChild, height + 1);
	for (int i = 1; i < height; i++)
		printf("   ");
	printf("%c\n", root->c);
	drawBinaryTree(root->LeftChild, height + 1);
}

void cntLeavesRe(BinaryTree *root, int curLevel, int objLevel, int *cnt) {
	if (!root)
		return;
	if ((curLevel == objLevel || objLevel < 0) && root->LeftChild == root->RightChild)
		(*cnt)++;
	cntLeavesRe(root->LeftChild, curLevel + 1, objLevel, cnt);
	cntLeavesRe(root->RightChild, curLevel + 1, objLevel, cnt);
}

int cntLeaves(BinaryTree *root, int objLevel) {//cnt leaves in a BinaryTree  input -1 stands for cntAll
	if (!root)
		return 0;
	int cnt = 0;
	cntLeavesRe(root, 1, objLevel, &cnt);
	return cnt;
}

int measureHeight(BinaryTree *root, int curH) {
	static int maxH = 0;
	if (maxH == 0)
		curH = 1;
	if (!root)
		return 0;
	if (curH > maxH) {
		maxH = curH;
	}
	measureHeight(root->LeftChild, curH + 1);
	measureHeight(root->RightChild, curH + 1);
	return maxH;
}
