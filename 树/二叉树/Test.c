#include"pch.h"

int main() {

	BinaryTree *root = NULL;
	//createBinaryTreeByExPreOrd(&root);
	//printf("�ݹ�ǰ�������");
	//preOrder(root);
	//printf("\n�ݹ����������");
	//midOrder(root);
	//printf("\n�ݹ���������");
	//postOrder(root);
	//printf("\n���в��������");
	//levelOrderInQueue(root);//��չǰ������
	//printf("\nջ��ǰ�������");
	//preOrderInStack(root);
	//printf("\nջ�����������");
	//midOrderInStack(root);
	//printf("\nջ�к��������");
	//postOrderInStack(root);
	//printf("��������������������������������\n");


	/*char *s = "1234566111";
	printf("%d", lastIndexOf(s,10,'0'));*/


	TreeElement pre[TreeSize], mid[TreeSize], post[TreeSize];
	printf("�������������У�");
	scanf("%s", pre);
	printf("�������������У�");
	scanf("%s", mid);
	createBinaryTreeByPM(pre, 0, strlen(pre) - 1, mid, 0, strlen(mid) - 1, &root);
	printf("��������Ϊ��");
	postOrder(root);
	printf("\n");
	drawBinaryTree(root, 1);
	printf("������ͳ��Ҷ�ӽ��Ĳ�����");
	int objLevel;
	scanf("%d", &objLevel);
	printf("%d\n", cntLeaves(root, objLevel));
	printf("����Ϊ%d\n", measureHeight(root,100));
	/*BinaryTree *tree = NULL;
	printf("\n�������������У�");
	scanf("%s", mid);
	printf("������������У�");
	scanf("%s", post);
	createBinaryTreeByMP(mid,0,strlen(mid)-1,post,0,strlen(post)-1, &tree);
	preOrder(tree);*/
	return 0;
}
