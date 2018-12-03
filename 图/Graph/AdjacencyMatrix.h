#pragma once

typedef struct {
	char sides[GraphNodesMax][GraphNodesMax];//�ڽӾ���
	GraphNodeType nodes[GraphNodesMax];//�������
	int nodeNum;//�����
	int sideNum;//����
	int isDirected;//��������
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
