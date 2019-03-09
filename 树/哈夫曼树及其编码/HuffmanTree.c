#include"pch.h"

typedef char ElementTree;

typedef struct {
	ElementTree data;	//�������
	int weight;	//���Ȩ��
	int parent;	//	˫���±�
	int left, right;	//	���������±�
}HuffmanTree;

typedef struct {
	ElementTree data;
	char hfCode[115];
}HfCode;

int num = 1;//��ǰ��̬������Ч���� [1,num)
int charNum = 0;//�ַ����е��ַ����� [0,num)

char text[2005];//�ı�Դ
char encodedText[4005];//�������ı�
int cpNum = 0;//ʹ�õ��±���
char cpllText[1005];//�����һ����  ���洢long ���һ���洢ԭ��������

HfCode codes[111];//ÿ���ַ��Ĺ���������

char *textAnalyze() {//�����ַ������ַ�����������
	char *chars = (char *)malloc(sizeof(char)*127);//32~126
	char c = 0;
	memset(chars, 0, sizeof(char)*127);
	scanf("%[^\n]", text);
	int i = 0;
	while (c = text[i++]) {
		chars[c]++;//����
	}
	for (i = 32; i <= 126; i++) {
		if (chars[i]) {
			printf("�ַ�%c ����%d��\n", i, chars[i]);
		}
	}
	return chars;
}////ͳ���ַ����

void initElement(HuffmanTree *nodes, char *chars) {
	memset(nodes, 0, sizeof(char) * sizeof(HuffmanTree) * 200);
	for (int i = 32; i <= 126; i++) {
		if (chars[i]) {
			nodes[num].data = i;
			nodes[num].weight = chars[i];
			nodes[num].parent = nodes[num].left = nodes[num].right = 0;
			num++;
		}
	}
	free(chars);
	/*for (int i = 1; i < num; i++) {
		printf("%c,%d,%d,%d,%d\n", nodes[i].data, nodes[i].weight, nodes[i].parent, nodes[i].left, nodes[i].right);
	}*/
}///////��ʼ����̬�������

int *searchMin(HuffmanTree *nodes) {// num>=2
	int *nums = (int *)malloc(sizeof(int) * 2);
	int i = 1;
	for (; i < num&&nodes[i].parent != 0; i++);//nodes[i].parent == 0 ����
	nums[0] = i;//        0  min      1Smin
	for (i++; i < num&&nodes[i].parent != 0; i++);
	nodes[i].weight > nodes[nums[0]].weight ? nums[1] = i:(nums[1]=nums[0],nums[0] = i);//�ҵ���ʼ���±�
	for (i++; i < num; i++) {
		if (nodes[i].parent == 0) {//δʹ��
			if (nodes[i].weight < nodes[nums[0]].weight) {//  <min
				nums[1] = nums[0], nums[0] = i;
			}
			else if(nodes[i].weight < nodes[nums[1]].weight) {
				nums[1] = i;
			}
		}
	}
	return nums;
}//���ص�ǰȨ����Сֵ���Сֵ���±�

int *searchOrder(HuffmanTree *nodes) {// num>=2
	int *nums = (int *)malloc(sizeof(int) * 2);
	int i = 1;
	for (; i < num&&nodes[i].parent != 0; i++);//nodes[i].parent == 0 ����
	nums[0] = i;//        0  pre      1 later
	for (i++; i < num&&nodes[i].parent != 0; i++);
	nums[1] = i;//�ҵ���ʼ���±�
	for (i++; i < num; i++) {
		if (nodes[i].parent == 0) {//δʹ��
			if (nodes[i].weight < nodes[nums[1]].weight) {//  <min
				nums[1] = i;
			}
			else if (nodes[i].weight < nodes[nums[0]].weight) {
				nums[0]=nums[1],nums[1] = i;
			}
		}//������˳���������Ŷ�����
	}
	return nums;
}//���ص�ǰȨ����Сֵ���Сֵ���±�

void createHuffmanTree(HuffmanTree *nodes) {
	int end = num + num - 3;
	int *min = NULL;
	while (num != end+1) {
		min = searchOrder(nodes);
		//�����½��
		nodes[num].weight = nodes[min[0]].weight + nodes[min[1]].weight;
		nodes[num].left = min[0];
		nodes[num].right = min[1];
		//�ԭ���
		nodes[min[0]].parent = num;
		nodes[min[1]].parent = num;
		num++;
		free(min);
		/*printf("-------------------����%d----------\n", num-1);
		for (int i = 1; i < num; i++) {
			printf("�±�%d:  %c,%d,%d,%d,%d\n",i ,nodes[i].data, nodes[i].weight, nodes[i].parent, nodes[i].left, nodes[i].right);
		}*/
	}
}

void preOrder(HuffmanTree *nodes,HuffmanTree *node) {//ǰ�����HuffmanTree
	printf("%d ", node->weight);
	if (node->left) {
		preOrder(nodes,&nodes[node->left]);
		preOrder(nodes,&nodes[node->right]);
	}
}

void encodeAll(HuffmanTree *nodes, int index, char *order, int cnt) {
	if (nodes[index].left == nodes[index].right) {
		printf("%c : ", nodes[index].data);
		order[cnt] = 0;
		puts(order);
		codes[charNum].data = nodes[index].data;
		strcpy(codes[charNum++].hfCode,order);
		/*for (int i = 0; i < cnt; i++)
			printf("%c", order[i]);
		printf("\n");*/
	}
	/*else {����
		order[cnt++] = nodes[nodes[index].parent].left == index ? '0' : '1';
	}*/
	if (nodes[index].left) {
		order[cnt] = '0';
		encodeAll(nodes, nodes[index].left, order, cnt+1);
		order[cnt] = '1';
		encodeAll(nodes, nodes[index].right, order, cnt+1);
	}
}

void getCodeByChar(HuffmanTree *nodes, char leaf) {//�õ�ĳ��Ҷ�ӽڵ�ı���
	int index;
	int end = num / 2;
	for (index = 0; index <= end; index++) {
		if (nodes[index].data == leaf)
			break;
	}
	if (index > end) {
		printf("��������");
		return;
	}
	char order[115];
	int cnt = 0;
	while (nodes[index].parent) {//��Ϊ��
		order[cnt++] = nodes[nodes[index].parent].left == index ? '0' : '1';
		index = nodes[index].parent;
	}
	printf("%c : ", leaf);
	for (cnt--; cnt >= 0; cnt--) {
		printf("%c", order[cnt]);
	}
	printf("\n");
}

void encodeText(HuffmanTree *nodes) {//����
	int i, j, len = strlen(text);
	printf("����ϢΪ��\n%s\n", text);
	printf("����Ϣ�Ĺ���������Ϊ��\n");
	for (i = 0; i < len; i++) {
		for (j = 0; j < charNum&&codes[j].data != text[i]; j++);
			strcat(encodedText, codes[j].hfCode);
	}
	printf("%s\n",encodedText);
}

void decodeText(HuffmanTree *nodes, char *unknown) {//����
	int len = strlen(unknown);
	int root = num - 1;
	int i, index;
	for (i = 0, index = root; i < len; i++) {
		index = unknown[i] == '0' ? nodes[index].left : nodes[index].right;
		if (nodes[index].left == 0) {
			printf("%c", nodes[index].data);
			index = root;
		}
	}
}

void compress() {//
	
}

int main() {
	HuffmanTree nodes[200];
	initElement(nodes, textAnalyze());
	createHuffmanTree(nodes);

	for (int i = 1; i < num; i++) {
		printf("�±�%d:  %c,%d,%d,%d,%d\n", i, nodes[i].data, nodes[i].weight, nodes[i].parent, nodes[i].left, nodes[i].right);
	}

	preOrder(nodes,&nodes[num-1]);
	puts("");
	char order[115] = { 0 };
	encodeAll(nodes, num-1, order, 0);
	
	/*for (int i = 0; i < charNum; i++) {
		printf("%c :",codes[i].data);
		puts(codes[i].hfCode);
	}*/
	
	char leaf;
	do {
		printf("��������Ҫ������ַ�:");
		scanf("%*c%c", &leaf);
		getCodeByChar(nodes, leaf);
		printf("�Ƿ������(0/1)");
	} while (scanf("%*c%c",&leaf),leaf == '1');
	encodeText(nodes);
	printf("��������Ҫ���������:");
	char unknown[2005];
	rewind(stdin);
	scanf("%[01]", unknown);
	decodeText(nodes, unknown);
	return 0;
}
