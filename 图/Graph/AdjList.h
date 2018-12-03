#pragma once

typedef struct adjNode {
	int index;
	int weight;
	struct adjNode *next;
}AdjNode;

typedef struct {
	GraphNodeType node;
	AdjNode *tail;//循环链表
}AdjListElement;

typedef struct adjList {
	AdjListElement nodes[GraphNodesMax];
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

int cntConnectedComponent(AdjList * a);

int cntOutDegree(AdjList * a, int index);

int cntInDegree(AdjList * a, int index);

int cntOutDegree(AdjList * a, GraphNodeType node);

int cntInDegree(AdjList * a, GraphNodeType node);

int cntDegree(AdjList * a, GraphNodeType node);

void getTopologicalOrder(AdjList * a);
