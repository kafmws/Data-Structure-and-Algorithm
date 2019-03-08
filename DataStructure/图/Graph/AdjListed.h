#pragma once

typedef struct AdjUN{
	int index;
	struct AdjUN *next;
}UNode;

typedef struct AdjDN{
	int index;
	int weight;
	struct AdjDN *next;
}DNode;

typedef struct {
	GraphNodeType node;
	void *tail;//循环链表
}AdjListNode;

typedef struct adjListEd {
	AdjListNode nodes[GraphNodesMax];
	struct adjListEd *re;			//入表
	char isVisited[GraphNodesMax];
	int nodeNum;
	int sideNum;
}AdjListed;

typedef AdjListed ReAdjListed;//逆邻接表

//结构体变量若有指针类型或内部有指针类型     ，须初始化

void initGraph(AdjListed ** aa);

int getNodeIndex(AdjListed * a, GraphNodeType c);

void drawGraph(AdjListed * a);

void print(AdjListed * a);

int isDirected(AdjListed * a);

void DepthFirstSearch(AdjListed * a, int index);

void BroadFirstSearch(AdjListed * a, int index);

int TravelGraph(AdjListed * a, void(*func)(AdjListed *a, int index));

int cntOutDegree(AdjListed * a, int index);

int cntInDegree(AdjListed * a, int index);

int cntOutDegree(AdjListed * a, GraphNodeType node);

int cntInDegree(AdjListed * a, GraphNodeType node);

int cntDegree(AdjListed * a, GraphNodeType node);
