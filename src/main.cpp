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

    GraphViewer *gv = new GraphViewer(600, 600, false);

    gv->setBackground("background.jpg");

    gv->createWindow(600, 600);

    gv->defineEdgeDashed(false);
    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");
    gv->defineVertexSize(1);
    gv->defineEdgeCurved(false);

	readPositions(g, gv);
	readEdges(g, gv);

	gv->rearrange();

	return 0;
}
