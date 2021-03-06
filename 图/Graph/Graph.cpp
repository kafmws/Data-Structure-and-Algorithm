#include"pch.h"

int main() {

	AdjMatrix *am = NULL;
	initGraph(&am);
	drawGraph(am);	//A B C D E		AB AE AD BC BD CD CE
	print(am);
	printf("DFS:");
	TravelGraph(am,DepthFirstSearch);
	puts("");
	printf("BFS:");
	TravelGraph(am, BroadFirstSearch);
	puts("");
	printf("MST by Kruskal:");
	MSTKruskal(am);
	printf("MST by Prim:");
	MSTPrim(am);
	printf("please input the start node and end node:");
	GraphNodeType start, end;
	scanf("%c%c", &start, &end);
	int FloydDistance[GraphNodesMax][GraphNodesMax];
	int FloydPath[GraphNodesMax][GraphNodesMax];
	findShortestPath(am,start ,end );
	/*puts("dijkstra");
	DijkstraAnalyzeGraph(am, FloydDistance, FloydPath);*/
	puts("floyd");
	FloydAnalyzeGraph(am, FloydDistance, FloydPath);
	puts("dijkstra");
	DijkstraAnalyzeGraph(am, FloydDistance, FloydPath);

	//A B C D E F G H I                    //AB 10 AF 11 FE 26 DE 20 DH 16 CI 8 DI 21
													//CD 22 CB 18 BI 12 BG 16 GD 24 GH 19 HE 7 GF 17
	AdjList *al = NULL;
	initGraph(&al);
	drawGraph(al);
	print(al);
	printf("DFS:");
	TravelGraph(al, DepthFirstSearch);
	puts("");
	printf("BFS:");
	TravelGraph(al, BroadFirstSearch);
	puts("");
	//cntDegree(al);
	//printf("topological order:");
	//getTopologicalOrder(al);

	return 0;
}
