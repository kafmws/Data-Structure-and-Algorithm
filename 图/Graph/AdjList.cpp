#include"pch.h"

void initGraph(AdjList **aa) {
	(*aa) = (AdjList *)malloc(sizeof(AdjList));
	memset(*aa, 0, sizeof(char) * sizeof(AdjList));
}

int getNodeIndex(AdjList *a, char c) {
	for (int i = 0; i < a->nodeNum; i++) {
		if (a->nodes[i].node == c)
			return i;
	}
	return -1;
}

void drawGraph(AdjList *a) {
	ReAdjList *re = NULL;
	int t;
	printf("Is this graph directed?(0/1):");
	scanf("%d", &t);
	if (t == DIRECTED) {
		re = a->re = (ReAdjList *)malloc(sizeof(ReAdjList));
		memset(re, 0, sizeof(char) * sizeof(ReAdjList));
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
	if (re) {//������
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
		if (startIndex == -1 || endIndex == -1) {
			printf("error");
			exit(1);
		}
		if (re) {//��������¼Ȩ��
			printf("Please input its weight:");
			scanf("%d%*c", &t);
			DNode *p = (DNode *)malloc(sizeof(DNode));//����
			p->index = endIndex;
			DNode *q = (DNode *)malloc(sizeof(DNode));//���
			q->index = startIndex;
			p->weight = q->weight = t;
			if (a->nodes[startIndex].tail == NULL) {//����Ϊ��ʱ
				p->next = p;
				a->nodes[startIndex].tail = p;
			}
			else {//����Ϊ��ʱ
				p->next = ((DNode *)a->nodes[startIndex].tail)->next;
				((DNode *)a->nodes[startIndex].tail)->next = p;
				a->nodes[startIndex].tail = p;
			}
			if (re->nodes[endIndex].tail == NULL) {//����Ϊ��ʱ
				q->next = q;
				re->nodes[endIndex].tail = q;				//bug
			}
			else {
				q->next = ((DNode *)re->nodes[endIndex].tail)->next;
				((DNode *)re->nodes[endIndex].tail)->next = q;
				re->nodes[endIndex].tail = q;
			}
		}
		else {//������
			UNode *p = (UNode *)malloc(sizeof(UNode));
			p->index = endIndex;
			UNode *q = (UNode *)malloc(sizeof(UNode));
			q->index = startIndex;
			if (a->nodes[startIndex].tail == NULL) {//������	
				p->next = p;
				a->nodes[startIndex].tail = p;
			}
			else {
				p->next = ((UNode *)a->nodes[startIndex].tail)->next;
				((UNode *)a->nodes[startIndex].tail)->next = p;
				a->nodes[startIndex].tail = p;
			}
			if (a->nodes[endIndex].tail == NULL) {//������	
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

void printDNList(AdjList *a) {
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

void print(AdjList *a) {
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
	else {//������
		printf("OUT\n");
		printDNList(a);
		printf("IN\n");
		printDNList(a->re);//��ӡ���ڽӱ�
	}
}

int isDirected(AdjList *a) {
	return a->re == NULL;
}

void DepthFirstSearch(AdjList *a, int index) {
	AdjListNode node = a->nodes[index];
	printf("%c", node.node);
	a->isVisited[index]++;
	if (a->re == UNDIRECTED && node.tail) {//����ͼ
		UNode *head = ((UNode *)node.tail)->next;
		while (head != node.tail) {
			if (a->isVisited[head->index] == 0)
				DepthFirstSearch(a, head->index);
			head = head->next;
		}//head == node.tail
		if (a->isVisited[head->index] == 0)
			DepthFirstSearch(a, head->index);
	}
	else if(node.tail){//������
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

//void BroadFirstSearch(AdjList *a, int index) {
//	if (a->isVisited[index])
//		return;
//	AdjListNode node = a->nodes[index];
//	printf("%c", a->nodes[index].node);
//	a->isVisited[index]++;
//	if (a->re == NULL && node.tail) {//����ͼ
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

void BroadFirstSearch(AdjList *a, int index) {
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

int TravelGraph(AdjList *a, void (*func)(AdjList *a, int index)) {
	memset(a->isVisited, 0, sizeof(char) * sizeof(a->isVisited));
	int cnt = 0;
	for (int i = 0; i < a->nodeNum; i++) {
		if (a->isVisited[i] == 0) {
			(*func)(a, i); cnt++;
		}
	}
	return cnt;
}

int cntConnectedComponent(AdjList *a) {
	return TravelGraph(a, BroadFirstSearch);
}

int cntOutDegree(AdjList *a, int index) {
	int cnt = 0;
	void *tail = a->nodes[index].tail;
	if (tail) {
		if (a->re == NULL)
			for (UNode *p = ((UNode *)tail)->next; p != tail;p = p->next,cnt++);
		else
			for (UNode *p = ((UNode *)tail)->next; p != tail; p = p->next, cnt++);
		return cnt + 1;
	}
	return cnt;
}

int cntInDegree(AdjList *a, int index) {

}

int cntOutDegree(AdjList *a, GraphNodeType node) {

}

int cntInDegree(AdjList *a, GraphNodeType node) {

}