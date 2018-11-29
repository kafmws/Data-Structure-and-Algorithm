#include"pch.h"


int main() {
	//AdjMatrix *am = NULL;
	//initGraph(&am);
	//drawGraph(am);	//A B C D E		AB AE AD BC BD CD CE
	//TravelGraph(am,DepthFirstSearch);
	//puts("");
	//TravelGraph(am, BroadFirstSearch);

	AdjListed *al = NULL;
	initGraph(&al);
	drawGraph(al);
	print(al);
	TravelGraph(al, DepthFirstSearch);
	puts("");
	TravelGraph(al, BroadFirstSearch);
	puts("");
	printf("%d",cntOutDegree(al, getchar()));
	return 0;
}
