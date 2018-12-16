#include"pch.h"

///////////////MinimumSpanningTree

void MSTPrim(AdjMatrix *a) {
	int side[GraphNodesMax + 1][2] = { 0 };
	for (int i = 0; i <= a->nodeNum; i++)
		side[i][1] = INFINITE;
	int time = a->nodeNum - 1;
	int nodeIndex = 0;
	side[0][1] = 0;
	while (time != 0) {
		int min = a->nodeNum;
		for (int i = 0; i < a->nodeNum; i++) {
			if (a->sides[nodeIndex][i] && side[i][1] > a->sides[nodeIndex][i]) {
				side[i][0] = nodeIndex;
				side[i][1] = a->sides[nodeIndex][i];
			}
		}
		for (int i = 0; i < a->nodeNum; i++) {
			if (side[i][1] != 0 && side[i][1] < side[min][1])
				min = i;
		}

		/*for (int i = 0; i < a->nodeNum; i++)
			printf("%d ", a->sides[nodeIndex][i]);*/

		printf("%c%c ", a->nodes[side[min][0]], a->nodes[min]);
		side[min][1] = 0;
		nodeIndex = min;
		time--;
	}
	printf("\n");
}

int findEnd(int *judge, int begin) {
	while (judge[begin])
		begin = judge[begin];
	return begin;
}

void MSTKruskal(AdjMatrix *a) {
	int cnt = 0;
	int minx = 0, miny = 0;
	int sides[1500][3] = { 0 };//x,y,value
	for (int i = 0; i < a->nodeNum; i++) {
		for (int j = i + 1; j < a->nodeNum; j++) {
			if(a->sides[i][j]){
				sides[cnt][0] = i;
				sides[cnt][1] = j;
				sides[cnt++][2] = a->sides[i][j];
			}
		}
	}
	//≈≈–Ú
	for (int i = 1; i < a->sideNum; i++) {
		for (int j = 0; j < a->sideNum - i; j++) {
			if (sides[j][2] > sides[j + 1][2]) {
				int t;
				t = sides[j][0], sides[j][0] = sides[j + 1][0], sides[j + 1][0] = t;
				t = sides[j][1], sides[j][1] = sides[j + 1][1], sides[j + 1][1] = t;
				t = sides[j][2], sides[j][2] = sides[j + 1][2], sides[j + 1][2] = t;
			}
		}
	}
	int judge[GraphNodesMax] = { 0 };
	cnt = 0;
	for (int i = 0; i < a->sideNum&&cnt<a->nodeNum-1; i++) {
		int start = sides[i][0], end = sides[i][1];
		int tail1 = findEnd(judge, start);
		int tail2 = findEnd(judge, end);
		if ( tail1 != tail2 ) {
			printf("%c%c ", a->nodes[start], a->nodes[end]);
			judge[tail1] = tail2;
			cnt++;
			/*for (int k = 0; k < a->nodeNum; k++)
				printf("%d", judge[k]);
			printf("\n");*/
		}
	}
	printf("\n");
}

//////////////////////////TopologicalOrder
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
	for (int j = 0; j < a->nodeNum; j++) {
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

////////////////SingleSourceShortestPath

void Dijkstra(AdjMatrix *a, int distance[GraphNodesMax + 1], int path[GraphNodesMax], int index) {
	for (int i = 0; i < a->nodeNum; i++) {
		distance[i] = a->sides[index][i] ? path[i] = index, a->sides[index][i] : INFINITE;
	}
	distance[index] = 0;
	distance[GraphNodesMax] = INFINITE;
	int min;
	while (1) {
		min = GraphNodesMax;
		for (int i = 0; i < a->nodeNum; i++) {
			if (a->isVisited[i] == 0 && distance[i] < distance[min])
				min = i;
		}
		if (min == GraphNodesMax)
			break;
		//path[index] = min;
		a->isVisited[min]++;
		index = min;
		for (int i = 0; i < a->nodeNum; i++)
			if (a->sides[index][i] && distance[index] + a->sides[index][i] < distance[i]) {
				distance[i] = distance[index] + a->sides[index][i];
				path[i] = index;
			}
	}
	memset(a->isVisited, 0, sizeof(char)*GraphNodesMax);
}

void findShortestPath(AdjMatrix *a, GraphNodeType start, GraphNodeType end) {
	int distance[GraphNodesMax + 1];
	int path[GraphNodesMax];
	memset(path, -1, sizeof(int)*GraphNodesMax);
	int index = getNodeIndex(a, start);
	int object = getNodeIndex(a, end);
	int startIndex = index;
	Dijkstra(a, distance, path, index);
	char routine[GraphNodesMax + 1] = { 0 };
	int cnt = 0;
	for (index = object; index != -1; index = path[index]) {//  index != startIndex
		//printf("%d", index);
		routine[cnt++] = a->nodes[index];
	}
	//routine[cnt++] = a->nodes[index];          // when index != startIndex
	printf("the shortest distance is %d, path is ", distance[object]);
	for (cnt = cnt - 1; cnt >= 0; cnt--)
		printf("%c", routine[cnt]);
	printf("\n");
}   

////////////////Analyze graph and store results
void FloydAnalyzeGraph(AdjMatrix *a, int distance[][GraphNodesMax], int path[][GraphNodesMax]) {
	for (int i = 0; i < a->nodeNum; i++)
		memset(path[i], -1, sizeof(int)*GraphNodesMax);
	for (int i = 0; i < GraphNodesMax; i++) {
		for (int j = 0; j < GraphNodesMax; j++) {
			distance[i][j] = a->sides[i][j] ? path[i][j] = i, a->sides[i][j] : INFINITE;
		}
	}
	for (int i = 0; i < GraphNodesMax; i++)
		distance[i][i] = 0;
	for (int index = 0; index < a->nodeNum; index++) {//±È¿˙√ø∏ˆ∂•µ„
		for (int i = 0; i < a->nodeNum; i++) {//±È¿˙æÿ’Û
			for (int j = 0; j < a->nodeNum; j++) {
				if (distance[i][index] != INFINITE && distance[index][j] != INFINITE
					&& distance[i][index] + distance[index][j] < distance[i][j]) {
					distance[i][j] = distance[i][index] + distance[index][j];
					path[i][j] = index;
				}
			}
		}
	}


	for (int i = 0; i < a->nodeNum; i++) {//±È¿˙æÿ’Û
		for (int j = 0; j < a->nodeNum; j++) {
			if (distance[i][j] == INFINITE)
				printf("///");
			else
				printf("%3d", distance[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < a->nodeNum; i++) {//±È¿˙æÿ’Û
		for (int j = 0; j < a->nodeNum; j++) {
			printf("%3d", path[i][j]);
		}
		printf("\n");
	}
}

void DijkstraAnalyzeGraph(AdjMatrix * a, int distance[][GraphNodesMax], int path[][GraphNodesMax]) {
	for (int i = 0; i < a->nodeNum; i++)
		memset(path[i], -1, sizeof(int)*GraphNodesMax);

	for (int i = 0; i < a->nodeNum; i++) {
		Dijkstra(a, distance[i], path[i], i);
	}

	for (int i = 0; i < a->nodeNum; i++) {//±È¿˙æÿ’Û
		for (int j = 0; j < a->nodeNum; j++) {
			if (distance[i][j] == INFINITE)
				printf("///");
			else
				printf("%3d", distance[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < a->nodeNum; i++) {//±È¿˙æÿ’Û
		for (int j = 0; j < a->nodeNum; j++) {
			printf("%3d", path[i][j]);
		}
		printf("\n");
	}
}