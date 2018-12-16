#pragma once

void MSTPrim(AdjMatrix * a);

void MSTKruskal(AdjMatrix * a);

void Dijkstra(AdjMatrix * a, int distance[GraphNodesMax + 1], int path[GraphNodesMax], int index);

void findShortestPath(AdjMatrix * a, GraphNodeType start, GraphNodeType end);

void FloydAnalyzeGraph(AdjMatrix * a, int distance[][GraphNodesMax], int path[][GraphNodesMax]);

void DijkstraAnalyzeGraph(AdjMatrix * a, int distance[][GraphNodesMax], int path[][GraphNodesMax]);
