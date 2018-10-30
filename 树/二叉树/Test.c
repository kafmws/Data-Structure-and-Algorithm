#include"pch.h"

int main() {

	BinaryTree *root = NULL;
	//createBinaryTreeByExPreOrd(&root);
	//printf("递归前序遍历：");
	//preOrder(root);
	//printf("\n递归中序遍历：");
	//midOrder(root);
	//printf("\n递归后序遍历：");
	//postOrder(root);
	//printf("\n队列层序遍历：");
	//levelOrderInQueue(root);//扩展前序序列
	//printf("\n栈中前序遍历：");
	//preOrderInStack(root);
	//printf("\n栈中中序遍历：");
	//midOrderInStack(root);
	//printf("\n栈中后序遍历：");
	//postOrderInStack(root);
	//printf("————————————————\n");


	/*char *s = "1234566111";
	printf("%d", lastIndexOf(s,10,'0'));*/


	TreeElement pre[TreeSize], mid[TreeSize], post[TreeSize];
	printf("请输入先序序列：");
	scanf("%s", pre);
	printf("请输入中序序列：");
	scanf("%s", mid);
	createBinaryTreeByPM(pre, 0, strlen(pre) - 1, mid, 0, strlen(mid) - 1, &root);
	printf("后序序列为：");
	postOrder(root);
	printf("\n");
	drawBinaryTree(root, 1);
	printf("请输入统计叶子结点的层数：");
	int objLevel;
	scanf("%d", &objLevel);
	printf("%d\n", cntLeaves(root, objLevel));
	printf("树高为%d\n", measureHeight(root,100));
	/*BinaryTree *tree = NULL;
	printf("\n请输入中序序列：");
	scanf("%s", mid);
	printf("请输入后序序列：");
	scanf("%s", post);
	createBinaryTreeByMP(mid,0,strlen(mid)-1,post,0,strlen(post)-1, &tree);
	preOrder(tree);*/
	return 0;
}
