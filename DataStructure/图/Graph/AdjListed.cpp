#include"pch.h"

void initGraph(AdjListed **aa) {
	(*aa) = (AdjListed *)malloc(sizeof(AdjListed));
	memset(*aa, 0, sizeof(char) * sizeof(AdjListed));
}

int getNodeIndex(AdjListed *a, GraphNodeType c) {
	for (int i = 0; i < a->nodeNum; i++) {
		if (a->nodes[i].node == c)
			return i;
	}
	printf("error ,node NotFound\n");
	return -1;
}

void drawGraph(AdjListed *a) {
	ReAdjListed *re = NULL;
	int t;
	printf("Is this graph directed?(0/1):");
	scanf("%d", &t);
	if (t == DIRECTED) {
		initGraph(&(a->re));
		re = a->re;
		re->re = a;
	}
	else if (t != UNDIRECTED) {
		printf("data error, resume it's undirected.\n");
	}
	printf("Please input the amount of the nodes:");
	scanf("%d%*c", &a->nodeNum);
	if (re)re->nodeNum = a->nodeNum;
	printf("Please input every node:\n");
	for (int i = 0; i < a->nodeNum; i++) {
		scanf("%c%*c", &(a->nodes[i].node));
	}
	if (re) {//有向网
		for (int i = 0; i < a->nodeNum; i++)
			re->nodes[i].node = a->nodes[i].node;
	}
	printf("Please input the amount of the sides:");
	scanf("%d%*c", &a->sideNum);
	if (re)re->sideNum = a->sideNum;
	printf("Please input the start node and end node of each side:\n");
	for (int i = 0; i < a->sideNum; i++) {
		int startIndex = getNodeIndex(a, getchar());
		int endIndex = getNodeIndex(a, getchar());
		getchar();
		if (startIndex == -1 || endIndex == -1 || startIndex == endIndex) {
			exit(1);
		}
		if (re) {//有向网记录权重
			printf("Please input its weight:");
			scanf("%d%*c", &t);
			DNode *p = (DNode *)malloc(sizeof(DNode));//出表
			p->index = endIndex;
			DNode *q = (DNode *)malloc(sizeof(DNode));//入表
			q->index = startIndex;
			p->weight = q->weight = t;
			if (a->nodes[startIndex].tail == NULL) {//链表为空时
				p->next = p;
				a->nodes[startIndex].tail = p;
			}
			else {//链表不为空时
				p->next = ((DNode *)a->nodes[startIndex].tail)->next;
				((DNode *)a->nodes[startIndex].tail)->next = p;
				a->nodes[startIndex].tail = p;
			}
			if (re->nodes[endIndex].tail == NULL) {//链表为空时
				q->next = q;
				re->nodes[endIndex].tail = q;				//bug
			}
			else {
				q->next = ((DNode *)re->nodes[endIndex].tail)->next;
				((DNode *)re->nodes[endIndex].tail)->next = q;
				re->nodes[endIndex].tail = q;
			}
		}
		else {//无向网
			UNode *p = (UNode *)malloc(sizeof(UNode));
			p->index = endIndex;
			UNode *q = (UNode *)malloc(sizeof(UNode));
			q->index = startIndex;
			if (a->nodes[startIndex].tail == NULL) {//空链表	
				p->next = p;
				a->nodes[startIndex].tail = p;
			}
			else {
				p->next = ((UNode *)a->nodes[startIndex].tail)->next;
				((UNode *)a->nodes[startIndex].tail)->next = p;
				a->nodes[startIndex].tail = p;
			}
			if (a->nodes[endIndex].tail == NULL) {//空链表	
				q->next = q;
				a->nodes[endIndex].tail = q;
			}
			else {
				q->next = ((UNode *)a->nodes[endIndex].tail)->next;
				((UNode *)a->nodes[endIndex].tail)->next = q;
				a->nodes[endIndex].tail = q;
			}
		}
	}
	//print(a);
}

void printDNList(AdjListed *a) {
	for (int i = 0; i < a->nodeNum; i++) {
		printf("%c : ", a->nodes[i].node);
		DNode *head = a->nodes[i].tail == NULL ? NULL : ((DNode *)a->nodes[i].tail)->next;
		DNode *p = head;
		if (p) {
			for (; p != a->nodes[i].tail; p = p->next) {
				printf("%2d/%d ", p->index, p->weight);
			}
			printf("%2d/%d", p->index, p->weight);
		}
		printf("\n");
	}
}

void print(AdjListed *a) {
	if(a->re == NULL){
		for (int i = 0; i < a->nodeNum; i++) {
			printf("%c : ", a->nodes[i].node);
			UNode *head = a->nodes[i].tail == NULL ? NULL : ((UNode *)a->nodes[i].tail)->next;
			UNode *p = head;
			if (p) {
				for (; p != a->nodes[i].tail; p = p->next) {
					printf("%2d ", p->index);
				}
				printf("%2d", p->index);
			}
			printf("\n");
		}
	}
	else {//有向网
		printf("OUT\n");
		printDNList(a);
		printf("IN\n");
		printDNList(a->re);//打印逆邻接表
	}
}

int isDirected(AdjListed *a) {
	return a->re == NULL;
}

void DepthFirstSearch(AdjListed *a, int index) {
	if (index <0 || index>a->nodeNum)
		return;
	AdjListNode node = a->nodes[index];
	printf("%c", node.node);
	a->isVisited[index]++;
	if (a->re == UNDIRECTED && node.tail) {//无向图
		UNode *head = ((UNode *)node.tail)->next;
		while (head != node.tail) {
			if (a->isVisited[head->index] == 0)
				DepthFirstSearch(a, head->index);
			head = head->next;
		}//head == node.tail
		if (a->isVisited[head->index] == 0)
			DepthFirstSearch(a, head->index);
	}
	else if(node.tail){//有向网
		DNode *head = ((DNode *)node.tail)->next;
		while (head != node.tail) {
			if (a->isVisited[head->index] == 0)
				DepthFirstSearch(a, head->index);
			head = head->next;
		}
		if (a->isVisited[head->index] == 0)
			DepthFirstSearch(a, head->index);
	}
}

//void BroadFirstSearch(AdjListed *a, int index) {
//	if (a->isVisited[index])
//		return;
//	AdjListNode node = a->nodes[index];
//	printf("%c", a->nodes[index].node);
//	a->isVisited[index]++;
//	if (a->re == NULL && node.tail) {//无向图
//		UNode *head = ((UNode *)node.tail)->next;
//		for (; head != node.tail; head = head->next) {
//			if (a->isVisited[head->index] == 0) {
//				printf("%c", a->nodes[head->index].node);
//			}
//		}
//		if (a->isVisited[head->index] == 0) {
//			printf("%c", a->nodes[head->index].node);
//		}
//		for (head = head->next; head != node.tail; head = head->next) {
//				BroadFirstSearch(a, head->index);
//		}
//			BroadFirstSearch(a, head->index);
//	}
//}

void BroadFirstSearch(AdjListed *a, int index) {
	if (index <0 || index>a->nodeNum)
		return;
	Queue *q = NULL;
	initQueue(&q);
	enterQueue(q, index);
	int next;
	while (!isEmpty(q)) {
		quitQueue(q, &next);
		AdjListNode node = a->nodes[next];
		printf("%c", node.node);
		a->isVisited[next]++;
		if (a->re == NULL && node.tail) {
			for (UNode *p = ((UNode *)node.tail)->next; p != node.tail; p = p->next) {
				if (a->isVisited[p->index] == 0)
					enterQueue(q, p->index);
			}
		}
		else if (node.tail) {
			for (DNode *p = ((DNode *)node.tail)->next; p != node.tail; p = p->next) {
				if (a->isVisited[p->index] == 0)
					enterQueue(q, p->index);
			}
		}
	}
}

int TravelGraph(AdjListed *a, void (*func)(AdjListed *a, int index)) {
	int cnt = 0;
	for (int i = 0; i < a->nodeNum; i++) {
		if (a->isVisited[i] == 0) {
			(*func)(a, i); cnt++;
		}
	}
	memset(a->isVisited, 0, sizeof(char) * sizeof(a->isVisited));
	return cnt;
}

int cntConnectedComponent(AdjListed *a) {
	return TravelGraph(a, BroadFirstSearch);
}

int cntOutDegree(AdjListed *a, int index) {
	if (index < 0 || index >= a->nodeNum)
		return -1;
	int cnt = 0;
	void *tail = a->nodes[index].tail;
	if (tail) {
		if (a->re == NULL)
			for (UNode *p = ((UNode *)tail)->next; p != tail; p = p->next, cnt++);
		else 
			for (DNode *p = ((DNode *)tail)->next; p != tail; p = p->next, cnt++);
		return cnt + 1;
	}
	return cnt;
}

int cntInDegree(AdjListed *a, int index) {
	if (index < 0 || index >= a->nodeNum)
		return -1;
	int cnt = 0;
	void *tail = a->re?a->re->nodes[index].tail:a->nodes[index].tail;
	if (tail) {
		if (a->re == NULL)
			for (UNode *p = ((UNode *)tail)->next; p != tail; p = p->next, cnt++);
		else
			for (DNode *p = ((DNode *)tail)->next; p != tail; p = p->next, cnt++);
		return cnt + 1;
	}
	return cnt;
}

int cntOutDegree(AdjListed *a, GraphNodeType node) {
	return cntOutDegree(a, getNodeIndex(a, node));
}

int cntInDegree(AdjListed *a, GraphNodeType node) {
	return cntInDegree(a, getNodeIndex(a, node));
}

int cntDegree(AdjListed *a ,GraphNodeType node) {
	int index = getNodeIndex(a, node);
	int cntOut = cntOutDegree(a,index);
	if (a->re == NULL || cntOut == -1)
		return cntOut;
	return cntOut + cntInDegree(a, index);
}