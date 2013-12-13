#include "User.h"
#include "Connection.h"
#ifndef _GRAPH_INCLUDE
#define _GRAPH_INCLUDE

#define _MAX_NODES_GRAPH 100
#define _MAX_PATHS_GRAPH 200

#define INFINITESIMAL 0.001

typedef struct Node{
	float x, y, z, width;
	User user;
}Node;

typedef struct Path{
	int nodei, nodef;
	float weight, width;
	Connection connection;                                                    
}Path;

extern Node nodes[];
extern Path paths[];
extern int numNodes, numPaths;

void addNode(Node);
void deleteNode(int);
void printNode(Node);
void listNodes();
Node createNode(float, float, float, User);

void addPath(Path);
void deletePath(int);
void printPath(Path);
void listPaths();
Path createPath(int, int, float, float);

void saveGraph();
void readGraph();

#endif