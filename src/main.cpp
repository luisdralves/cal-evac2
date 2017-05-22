#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <stdlib.h>
#include <ctime>
#include "Graph.h"
#include "Position.h"
#include "Street.h"
#include "readFiles.h"
#include "menus.h"

using namespace std;

int main() {
	Graph<Position, Street> g;
	GraphViewer * gv;

	gv = new GraphViewer(600, 600, false);
	gv->createWindow(700, 700);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");
	gv->defineEdgeCurved(false);


	readPositions(g, gv);
	system("pause");
	readEdges(g, gv);

	gv->rearrange();

	return 0;
}
