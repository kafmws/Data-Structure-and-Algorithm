#pragma once

typedef struct {
	char sides[GraphNodesMax][GraphNodesMax];//邻接矩阵
	GraphNodeType nodes[GraphNodesMax];//结点数组
	int nodeNum;//结点数
	int sideNum;//边数
	int isDirected;//有向无向
	char isVisited[GraphNodesMax];
}AdjMatrix;

void initGraph(AdjMatrix ** am);

void print(AdjMatrix * a);

void drawGraph(AdjMatrix * a);

int isDirected(AdjMatrix * a);

void DepthFirstSearch(AdjMatrix * a, int nodeIndex);

void BroadFirstSearch(AdjMatrix * a, int nodeIndex);

int TravelGraph(AdjMatrix * a, void(*func)(AdjMatrix *a, int nodeIndex));

int cntConnectedComponent(AdjMatrix * a);

int cntOutDegree(AdjMatrix * a, int index);

int cntInDegree(AdjMatrix * a, int index);

int cntOutDegree(AdjMatrix * a, GraphNodeType node);

int cntInDegree(AdjMatrix * a, GraphNodeType node);

int cntDegree(AdjMatrix * a, GraphNodeType node);

int addNode(AdjMatrix * a, GraphNodeType node);

void addNode(AdjMatrix * a);

int addSide(AdjMatrix * a, int startIndex, int endIndex, int weight);

int addSide(AdjMatrix * a, GraphNodeType startNode, GraphNodeType endNode, int weight);

int addSide(AdjMatrix * a);
