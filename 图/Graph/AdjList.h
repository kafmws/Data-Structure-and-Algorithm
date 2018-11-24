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

typedef struct adjList {
	AdjListNode nodes[GraphNodesMax];
	struct adjList *re;			//入表
	char isVisited[GraphNodesMax];
	int nodeNum;
	int sideNum;
}AdjList;

typedef AdjList ReAdjList;//逆邻接表

//结构体变量若有指针类型或内部有指针类型     ，须初始化

void initGraph(AdjList ** aa);

void drawGraph(AdjList * a);

void print(AdjList * a);

int isDirected(AdjList * a);

void DepthFirstSearch(AdjList * a, int index);

void BroadFirstSearch(AdjList * a, int index);

int TravelGraph(AdjList * a, void(*func)(AdjList *a, int index));
