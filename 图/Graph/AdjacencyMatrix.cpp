#include"pch.h"

void initGraph(AdjMatrix **am) {
	AdjMatrix *a = (AdjMatrix *)malloc(sizeof(AdjMatrix));
	*am = a;
	memset(a, 0, sizeof(char)*sizeof(AdjMatrix));
	a->isDirected = UNKNOWN;
	//a->nodeNum = a->sideNum = 0;
}

void print(AdjMatrix *a) {
	printf("  ");
	for (int i = 0; i < a->nodeNum; i++)
		printf(" %c ", a->nodes[i]);
	printf("\n");
	for (int i = 0; i < a->nodeNum; i++) {
		printf("%c ", a->nodes[i]);
		for (int j = 0; j < a->nodeNum; j++) {
			printf("%3d", a->sides[i][j]);
		}
		printf("\n");
	}
}

int getNodeIndex(AdjMatrix *a,GraphNodeType c) {
	for (int i = 0; i < a->nodeNum; i++) {
		if (a->nodes[i] == c)
			return i;
	}
	printf("error ,node NotFound\n");
	return -1;
}

void drawGraph(AdjMatrix *a) {
	int t;
	printf("Is this graph directed?(0/1):");
	scanf("%d", &t);
	a->isDirected = (t == 0 || t == 1) ? t : printf("data error, resume it's undirected.\n"),UNDIRECTED;
	printf("Please input the amount of the nodes:");
	scanf("%d%*c", &a->nodeNum);
	printf("Please input every node:\n");
	for (int i = 0; i < a->nodeNum; i++) {
		scanf("%c%*c", &(a->nodes[i]));
	}
	printf("Please input the amount of the sides:");
	scanf("%d%*c", &a->sideNum);
	printf("Please input the start node and end node of each side:\n");
	for (int i = 0; i < a->sideNum; i++) {
		int startIndex = getNodeIndex(a, getchar());
		int endIndex = getNodeIndex(a, getchar());
		getchar();
		//printf("%d %d\n", startIndex, endIndex);
		if (startIndex == -1 || endIndex == -1) {//startIndex == endIndex
			exit(1);
		}
		if (a->isDirected == DIRECTED) {//��������¼Ȩ��
			printf("Please input its weight:");
			scanf("%c%*c", &(a->sides[startIndex][endIndex]));
		}
		else {
			a->sides[startIndex][endIndex] = 1;
			a->sides[endIndex][startIndex] = 1;
		}
	}
	//print(a);
}

inline int isDirected(AdjMatrix *a) {
	return a->isDirected;
}

/*����Ҫ*/
int getFirstAdjNodeIndex(AdjMatrix *a, int nodeIndex) {
	int i, j;
	for (i = nodeIndex, j = 0; !a->sides[i][j] && j < a->nodeNum; j++);
	return j == a->nodeNum ? -1 : j;
}

int getNextAdjNodeIndex(AdjMatrix *a, int nodeIndex, int relativeIndex) {
	int i, j;
	for (i = nodeIndex, j = relativeIndex + 1; !a->sides[i][j] && j < a->nodeNum; j++);
	return j == a->nodeNum ? -1 : j;
}

void DepthFirstSearch(AdjMatrix *a, int nodeIndex) {
	if (a->isVisited[nodeIndex])
		return;
	printf("%c", a->nodes[nodeIndex]);
	a->isVisited[nodeIndex]++;
	//int nextNodeIndex = getFirstAdjNodeIndex(a, nodeIndex);
	int nextNodeIndex = getNextAdjNodeIndex(a, nodeIndex, 0);
	while (nextNodeIndex != -1) {
		DepthFirstSearch(a, nextNodeIndex);
		nextNodeIndex = getNextAdjNodeIndex(a,nodeIndex,nextNodeIndex);
	}
}

void BroadFirstSearch(AdjMatrix *a, int nodeIndex) {
	Queue *q = NULL;
	initQueue(&q);
	enterQueue(q, nodeIndex);
	a->isVisited[nodeIndex]++;
	while (!isEmpty(q)) {
		if (quitQueue(q, &nodeIndex)) {//���ӳɹ�����
			printf("%c", a->nodes[nodeIndex]);
			int nextNodeIndex = getNextAdjNodeIndex(a, nodeIndex,0);
			while (nextNodeIndex != -1) {
				if (!a->isVisited[nextNodeIndex]) {
					enterQueue(q, nextNodeIndex);
					a->isVisited[nextNodeIndex]++;
				}
				nextNodeIndex = getNextAdjNodeIndex(a, nodeIndex, nextNodeIndex);
			}
		}
	}
}

int TravelGraph(AdjMatrix *a, void(*func)(AdjMatrix *a, int nodeIndex)) {
	int cnt = 0;
	for (int index = 0; index < a->nodeNum; index++) {
		if (!a->isVisited[index]) {
			(*func)(a, index); cnt++;
		}
	}
	memset(a->isVisited, 0, sizeof(char) * sizeof(a->isVisited));//���ñ������
	return cnt;
}

int cntConnectedComponent(AdjMatrix *a) {//����ͼ����ͨ������
	return TravelGraph(a, DepthFirstSearch);
}

int cntOutDegree(AdjMatrix *a,int index) {//���ĳ���
	if (index < 0 || index >= a->nodeNum)
		return -1;
	int cnt = 0;
	for (int i = 0; i < a->nodeNum; i++) {
		if (a->sides[index][i])cnt++;
	}
	return cnt;
}

int cntInDegree(AdjMatrix *a, int index) {//�������
	if (index < 0 || index >= a->nodeNum)
		return -1;
	int cnt = 0;
	for (int i = 0; i < a->nodeNum; i++) {
		if (a->sides[i][index])cnt++;
	}
	return cnt;
}

int cntOutDegree(AdjMatrix *a, GraphNodeType node) {//�������н��ĳ���
	//if(a->isDirected == UNDIRECTED){
	//	printf("using cntDegree in undirected graph is supposed.\n");
	//}
	/*int cnt = 0;
	int index = getNodeIndex(a, node);
	if(index < 0)return -1;
	for (int i = 0; i < a->nodeNum; i++) {
		if (a->sides[index][i])cnt++;
	}
	return cnt;*/
	return cntOutDegree(a, getNodeIndex(a, node));
}

int cntInDegree(AdjMatrix *a, GraphNodeType node) {//�������н������
	/*if (a->isDirected == UNDIRECTED) {
		printf("using cntDegree in undirected graph is supposed.\n");
	}*/
	/*int cnt = 0;
	int index = getNodeIndex(a, node);
	if (index < 0)return - 1;
	for (int i = 0; i < a->nodeNum; i++) {
		if (a->sides[i][index])cnt++;
	}
	return cnt;*/
	return cntInDegree(a, getNodeIndex(a, node));
}

int cntDegree(AdjMatrix *a, GraphNodeType node) {//����ĳ���Ķ�
	int index = getNodeIndex(a, node);
	int cntOut = cntOutDegree(a, index);
	if (a->isDirected == UNDIRECTED || cntOut == -1)
		return cntOut;
	int cntIn = cntInDegree(a, index);
	return cntOut + cntIn;
}