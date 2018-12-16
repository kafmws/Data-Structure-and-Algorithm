#include"pch.h"

void initGraph(AdjMatrix **am) {
	AdjMatrix *a = (AdjMatrix *)malloc(sizeof(AdjMatrix));
	*am = a;
	memset(a, 0, sizeof(char)*sizeof(AdjMatrix));
	a->isDirected = UNKNOWN;
	//a->nodeNum = a->sideNum = 0;
}

void print(AdjMatrix *a) {
	printf("   ");
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
	int isDirceted, ownWeight;
	printf("Is this graph directed?(0/1):");
	scanf("%d", &isDirceted);
	a->isDirected = (isDirceted == 0 || isDirceted == 1) ? isDirceted : printf("data error, resume it's undirected.\n"),UNDIRECTED;
	printf("Is it own weight for each side?(0/1):");
	scanf("%d",&ownWeight);
	if (ownWeight != 0 && ownWeight != 1)
		printf("data error, resume it isn't.\n");
	printf("Please input the amount of the nodes:");
	scanf("%d%*c", &a->nodeNum);
	printf("Please input every node:\n");
	for (int i = 0; i < a->nodeNum; i++) {
		scanf("%c", &(a->nodes[i]));
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
		if (ownWeight == 1) {//记录权重
			printf("Please input its weight:");
			int tem;
			scanf("%d%*c", &tem);
			a->sides[startIndex][endIndex] = tem;
		}
		else {
			a->sides[startIndex][endIndex] = 1;
		}
		if (!isDirceted)
			a->sides[endIndex][startIndex] = ownWeight ? a->sides[startIndex][endIndex] : 1;
		//print(a);
	}
	//print(a);
}

inline int isDirected(AdjMatrix *a) {
	return a->isDirected;
}

/*无需要*/
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
	if (!a->isVisited[nodeIndex]) {
		enterQueue(q, nodeIndex);
		a->isVisited[nodeIndex]++;
	}
	while (!isEmpty(q)) {
		if (quitQueue(q, &nodeIndex)) {//出队成功并且
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
	memset(a->isVisited, 0, sizeof(char) * sizeof(a->isVisited));//重置标记数组
	return cnt;
}

int cntConnectedComponent(AdjMatrix *a) {//计算图的连通分量数
	return TravelGraph(a, DepthFirstSearch);
}

int cntOutDegree(AdjMatrix *a,int index) {//结点的出度
	if (index < 0 || index >= a->nodeNum)
		return -1;
	int cnt = 0;
	for (int i = 0; i < a->nodeNum; i++) {
		if (a->sides[index][i])cnt++;
	}
	return cnt;
}

int cntInDegree(AdjMatrix *a, int index) {//结点的入度
	if (index < 0 || index >= a->nodeNum)
		return -1;
	int cnt = 0;
	for (int i = 0; i < a->nodeNum; i++) {
		if (a->sides[i][index])cnt++;
	}
	return cnt;
}

int cntOutDegree(AdjMatrix *a, GraphNodeType node) {//有向网中结点的出度
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

int cntInDegree(AdjMatrix *a, GraphNodeType node) {//有向网中结点的入度
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

int cntDegree(AdjMatrix *a, GraphNodeType node) {//计算某结点的度
	int index = getNodeIndex(a, node);
	int cntOut = cntOutDegree(a, index);
	if (a->isDirected == UNDIRECTED || cntOut == -1)
		return cntOut;
	int cntIn = cntInDegree(a, index);
	return cntOut + cntIn;
}

void cntDegree(AdjMatrix *a) {
	printf("node out   in\n");
	for (int i = 0; i < a->nodeNum; i++) {
		printf(" %c  %3d  %3d\n", a->nodes[i], cntOutDegree(a, i), cntInDegree(a, i));
	}
}

int addNode(AdjMatrix *a, GraphNodeType node) {
	for (int i = 0; i < a->nodeNum; i++) {
		if (a->nodes[i] == node) {
			printf("there is a node named %c.", node);
			return 0;
		}
	}
	a->nodes[a->nodeNum++] = node;
	return 1;
}

void addNode(AdjMatrix *a) {
	GraphNodeType c;
	if (a->nodeNum == GraphNodesMax) {
		printf("there is no room for another node.");
		return;
	}
	printf("please input the node:");
	scanf("%c", &c);
	addNode(a, c);
	if (a->nodeNum < GraphNodesMax) {
		printf("ok, do you want to add another node?(0/1)");
		int t;
		scanf("%d", &t);
		if (t)
			addNode(a);
	}
}

int addSide(AdjMatrix *a,int startIndex, int endIndex, int weight) {
	int t;
	if (a->sides[startIndex][endIndex]) {
			printf("this side is already existing.Do you want to override it?(0/1)");
			scanf("%d",&t);
			if (t == 0)
				return 0;
	}
	if (a->isDirected)
		a->sides[startIndex][endIndex] = weight;
	else
		a->sides[startIndex][endIndex] = a->sides[endIndex][startIndex] = weight;
	return 1;
}

int addSide(AdjMatrix *a, GraphNodeType startNode, GraphNodeType endNode, int weight) {
	int startIndex = getNodeIndex(a, startNode);
	int endIndex = getNodeIndex(a, endNode);
	if (startIndex == -1 || endIndex == -1)
		return 0;
	return addSide(a, startIndex, endIndex, weight);
}

int addSide(AdjMatrix *a) {
	printf("please input the start and the end node of the side:");
	GraphNodeType start, end;
	scanf("%c%c", &start, &end);
	printf("please input the weight of the side:");
	int weight;
	scanf("%d", &weight);
	return addSide(a, start, end, weight);
}