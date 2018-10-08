/*
	@brief:最小生成树（普里姆算法）
	@author:WavenZ
	@time:2018/10/8
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "MGraph.h"
#define VertexType  char
#define VRType		int
typedef struct{
	VertexType		adjvex;
	VRType			lowcost;
}Mclosedge[MAX_VERTEX_NUM];
Mclosedge closedge;

VRType minimum(MGraph G, Mclosedge Mc) {
	int i;
	VRType min=65535;
	int index = -1;
	for (i = 0; i < G.vexnum; ++i) {
		if (Mc[i].lowcost != 0 && Mc[i].lowcost < min) {
			min = Mc[i].lowcost;
			index = i;
		}
	}
	return index;
}

void MiniSpanTree_PRIM(MGraph G, VertexType v) {
	int i, j;
	int k;
	k = LocateVex(G, v);
	for (i = 0; i < G.vexnum; ++i) {//初始化辅助数组
		if (i != k) {
			closedge[i].adjvex = v;
			closedge[i].lowcost = G.arcs[k][i].adj;
		}
	}
	closedge[k].lowcost = 0;//置零表示并入U集
	for (i = 1; i < G.vexnum; ++i) {
		k = minimum(G, closedge);//
		printf("(%c, %c )", closedge[k].adjvex, G.vexs[k]);
		for (j = 0; j < G.vexnum; ++j) {
			if (G.arcs[k][j].adj < closedge[j].lowcost) {
				closedge[j].adjvex = G.vexs[k];
				closedge[j].lowcost = G.arcs[k][j].adj;
			}
		}
		closedge[k].lowcost = 0;
	}
	
}

int main(int argc, char *argv[]) {
	MGraph G;
	CreateMGraph(&G);
	printMGraph(G);
	printf("最小生成树：");
	MiniSpanTree_PRIM(G, 'A');
	system("pause");
	return 1;
}