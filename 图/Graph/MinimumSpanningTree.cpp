#include"pch.h"
#include "MinimumSpanningTree.h"

void MSTPrim(AdjMatrix *a) {
	int side[GraphNodesMax + 1][2] = { 0 };
	for (int i = 0; i <= a->nodeNum; i++)
		side[i][1] = 0x7777777;
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