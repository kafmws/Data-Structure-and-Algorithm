#include"pch.h"

void initGraph(AdjList ** aa) {//初始化图
	(*aa) = (AdjList *)malloc(sizeof(AdjList));
	memset(*aa, 0, sizeof(char) * sizeof(AdjList));
}

int getNodeIndex(AdjList *a, GraphNodeType node) {//得到结点下标
	for (int i = 0; i < a->nodeNum; i++) {
		if (a->nodes[i].node == node)
			return i;
	}
	printf("error, node NotFound\n");
	return -1;
}

void drawGraph(AdjList * a) {//填充图
	AdjList *re = NULL;
	printf("Is this graph directed?(0/1):");
	int isDirected;
	scanf("%d", &isDirected);
	if (isDirected) {
		initGraph(&a->re);
		re = a->re;
		re->re = a;
	}
	else if (isDirected != UNDIRECTED) {
		printf("data error, resume it's undirected.\n");
	}
	printf("Does every side own its weight?(0/1):");
	int ownWeight;
	scanf("%d", &ownWeight);
	if (ownWeight != 0 && ownWeight != 1)
		ownWeight = 0, printf("data error, resume it doesn't.");
	printf("please input the amount of the nodes:");
	scanf("%d", &a->nodeNum);
	printf("please input every node:\n");
	rewind(stdin);
	for (int i = 0; i < a->nodeNum; i++)
		scanf("%c%", &(a->nodes[i].node));
	printf("please input the amount of the sides:");
	scanf("%d%*c", &a->sideNum);
	if (re) {
		re->nodeNum = a->nodeNum;
		re->sideNum = re->sideNum;
		for (int i = 0; i < a->nodeNum; i++)
			re->nodes[i].node = a->nodes[i].node;
	}
	AdjList *choice = re ? re : a;
	for (int i = 0; i < a->sideNum; i++) {
		printf("please input the start node and the end node:\n");
		int startIndex = getNodeIndex(a, getchar());
		int endIndex = getNodeIndex(a, getchar());
		getchar();
		if (startIndex == -1 || endIndex == -1 || startIndex == endIndex)
			exit(1);
		AdjNode *p = (AdjNode *)malloc(sizeof(AdjNode));
		if (ownWeight) {
			printf("please input its weight:");
			scanf("%d%*c", &p->weight);
		}
		else
			p->weight = 1;
		p->index = endIndex;
		if (a->nodes[startIndex].tail == NULL) {
			a->nodes[startIndex].tail = p;
			a->nodes[startIndex].tail->next = a->nodes[startIndex].tail;
		}
		else {
			p->next = a->nodes[startIndex].tail->next;
			a->nodes[startIndex].tail->next = p;
			a->nodes[startIndex].tail = p;
		}
		AdjNode *q = (AdjNode *)malloc(sizeof(AdjNode));
		q->weight = p->weight;
		int index;
		if (choice == re) {//有向图
			q->index = startIndex;
			index = endIndex;
		}
		else {//无向图
			q->index = startIndex;
			index = endIndex;
		}
		if (choice->nodes[index].tail == NULL) {
			choice->nodes[index].tail = q;
			choice->nodes[index].tail->next = choice->nodes[index].tail;
		}
		else {
			q->next = choice->nodes[index].tail->next;
			choice->nodes[index].tail->next = q;
			choice->nodes[index].tail = q;
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

int isDirected(AdjList * a){//是否为有向图
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
	if (a->isVisited[index] == 0) {
		enterQueue(q, index);
		a->isVisited[index]++;
	}
	int currentIndex;
	while (!isEmpty(q)) {
		quitQueue(q,&currentIndex);
		printf("%c",a->nodes[currentIndex].node);
		AdjNode *tail = a->nodes[currentIndex].tail;
		if (tail) {
			AdjNode *head = tail->next;
			for (; head != tail; head = head->next)
				if (a->isVisited[head->index] == 0) {
					enterQueue(q, head->index);
					a->isVisited[head->index]++;
				}
			if (a->isVisited[head->index] == 0) {
				enterQueue(q, head->index);
				a->isVisited[head->index]++;
			}
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

void getTopologicalOrder(AdjList *a) {
	AdjList *re = a->re;
	if (re == NULL)
		return;
	int inDegree[GraphNodesMax] = { 0 };
	for (int i = 0; i < a->nodeNum; i++) {
		int cnt = 0;
		AdjNode *tail = re->nodes[i].tail;
		if (tail) {
			for (AdjNode *head = tail->next; head != tail; head = head->next, cnt++);
			cnt++;
		}
		inDegree[i] = cnt;
	}
	char order[GraphNodesMax + 1] = { 0 };
	int cnt = 0, flag;
	for(int j = 0;j<a->nodeNum;j++) {
		flag = 0;
		for (int i = 0; i < a->nodeNum; i++) {
			if (inDegree[i] == 0 && a->isVisited[i] == 0) {
				order[cnt++] = a->nodes[i].node;
				a->isVisited[i]++;
				flag = 1;
				AdjNode *tail = a->nodes[i].tail;
				if (tail) {
					for (AdjNode *head = tail->next; head != tail; head = head->next)
						inDegree[head->index]--;
					inDegree[tail->index]--;
				}
			}	
		}
		if (flag == 0) {
				flag = -1;
				break;
			}
		if (flag == -1)
			break;
	}
	if (cnt == a->nodeNum)
		printf("topological order : %s", order);
	else
		printf("no topological order exists.");
	printf("\n");
}