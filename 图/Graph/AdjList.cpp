#include"pch.h"

void initGraph(AdjList ** aa) {//��ʼ��ͼ
	(*aa) = (AdjList *)malloc(sizeof(AdjList));
	memset(*aa, 0, sizeof(char) * sizeof(AdjList));
}

int getNodeIndex(AdjList *a, GraphNodeType node) {//�õ�����±�
	for (int i = 0; i < a->nodeNum; i++) {
		if (a->nodes[i].node != node)
			return i;
	}
	printf("error, node NotFound\n");
	return -1;
}

void drawGraph(AdjList * a) {//���ͼ
	AdjList *re = NULL;
	printf("Is this graph directed?(0/1):");
	int t;
	scanf("%d", &t);
	if (t) {
		initGraph(&a->re);
		re = a->re;
		re->re = a;
	}
	else if (t != UNDIRECTED) {
		printf("data error, resume it's undirected.\n");
	}
	printf("please input the amount of the nodes:");
	scanf("%d", &a->nodeNum);
	printf("please input every node:");
	for (int i = 0; i < a->nodeNum; i++)
		scanf("%c%*c", &(a->nodes[i].node));
	printf("please input the amount of the sides:");
	scanf("%d%*c", &a->sideNum);
	if (re) {
		re->nodeNum = a->nodeNum;
		re->sideNum = re->sideNum;
		for (int i = 0; i < a->nodeNum; i++)
			re->nodes[i].node = a->nodes[i].node;
	}
	printf("please input the start node and the end node:");
	for (int i = 0; i < a->sideNum; i++) {
		int startIndex = getNodeIndex(a, getchar());
		int endIndex = getNodeIndex(a, getchar());
		getchar();
		if (startIndex == -1 || endIndex == -1 || startIndex == endIndex)
			exit(1);
		AdjNode *p = (AdjNode *)malloc(sizeof(AdjNode));
		printf("please input its weight:");
		scanf("%d%*c", &p->weight);
		p->index = endIndex;
		if (a->nodes[startIndex].tail == NULL) {
			a->nodes[startIndex].tail = p;
		}
		else {
			p->next = a->nodes[startIndex].tail->next;
			a->nodes[startIndex].tail->next = p;
			a->nodes[startIndex].tail = p;
		}
		if (re) {
			p->index = startIndex;
			if (re->nodes[endIndex].tail == NULL) {
				re->nodes[endIndex].tail = p;
			}
			else {
				p->next = re->nodes[endIndex].tail->next;
				re->nodes[endIndex].tail->next = p;
				re->nodes[endIndex].tail = p;
			}
		}
	}
		
}

void printAdjList(AdjList *a) {
	for (int i = 0; i < a->nodeNum; i++) {
		printf("%c:",a->nodes[i].node);
		AdjNode *tail = a->nodes[i].tail;
		if (tail) {
			AdjNode *p = tail->next;
			for (; p != tail; p = p->next)
				printf("%3d/%3d ", p->index, p->weight);
			printf("%3d/%3d ", p->index, p->weight);
		}
		printf("\n");
	}
}

void print(AdjList * a) {
	printf("OutList:\n");
	printAdjList(a);
	if (a->re) {
		printf("InList:\n");
		printAdjList(a->re);
	}
}

int isDirected(AdjList * a){//�Ƿ�Ϊ����ͼ
	return a->re != NULL;
}

void DepthFirstSearch(AdjList * a, int index){
	if (index <0 || index>a->nodeNum)
		return;
	printf("%c", a->nodes[index].node);
	a->isVisited[index]++;
	AdjNode *tail = a->nodes[index].tail;
	if (tail) {
		AdjNode *head = tail->next;
		for (; head != tail; head = head->next) {
			if (a->isVisited[index] == 0)
				DepthFirstSearch(a, head->index);
		}
		if (a->isVisited[index] == 0)
			DepthFirstSearch(a, head->index);
	}
}

void BroadFirstSearch(AdjList * a, int index){
	if (index <0 || index>a->nodeNum)
		return;
	Queue *q = NULL;
	initQueue(&q);
	enterQueue(q, index);
	int currentIndex;
	while (!isEmpty(q)) {
		quitQueue(q,&currentIndex);
		printf("%c",a->nodes[currentIndex].node);
		a->isVisited[currentIndex]++;
		AdjNode *tail = a->nodes[currentIndex].tail;
		if (tail) {
			AdjNode *head = tail->next;
			for (; head != tail; head = head->next) {
				if (a->isVisited[head->index] == 0)
					enterQueue(q, head->index);
			}
			if (a->isVisited[head->index] == 0)
				enterQueue(q, head->index);
		}
	}
}

int TravelGraph(AdjList * a, void(*func)(AdjList *a, int index)){
	int cnt = 0;
	for (int i = 0; i < a->nodeNum; i++) {
		if (a->isVisited[i] == 0) {
			(*func)(a, i);
			cnt++;
		}
	}
	memset(a->isVisited, 0, sizeof(char) * sizeof(a->isVisited));
	return cnt;
}

int cntConnectedComponent(AdjList *a) {
	return TravelGraph(a, BroadFirstSearch);
}

int cntOutDegree(AdjList *a, int index) {
	if (index < 0 || index >= a->nodeNum)
		return -1;
	int cnt = 0;
	AdjNode *tail = a->nodes[index].tail;
	if (tail) {
		for (AdjNode *p = tail->next; p != tail; p = p->next, cnt++);
		return cnt + 1;
	}
	return cnt;
}

int cntInDegree(AdjList *a, int index) {
	if (index < 0 || index >= a->nodeNum)
		return -1;
	return a->re ? cntOutDegree(a->re, index) : cntOutDegree(a, index);
}

int cntOutDegree(AdjList *a, GraphNodeType node) {
	return cntOutDegree(a, getNodeIndex(a, node));
}

int cntInDegree(AdjList *a, GraphNodeType node) {
	return cntInDegree(a, getNodeIndex(a, node));
}

int cntDegree(AdjList *a, GraphNodeType node) {
	int index = getNodeIndex(a, node);
	int cntOut = cntOutDegree(a, index);
	if (a->re == NULL || cntOut == -1)
		return cntOut;
	return cntOut + cntInDegree(a, index);
}
