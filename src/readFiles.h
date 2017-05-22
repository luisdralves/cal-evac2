#pragma once

#ifndef READFILES_H_
#define READFILES_H_

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include "Position.h" //Vertices
#include "Street.h" //Edges
#include "Graph.h"
#include "graphViewer.h"

using namespace std;

void readPositions(Graph<Position, Street> & g, GraphViewer *gv);
Street readStreets(unsigned long StreetID, GraphViewer *gv);
void readEdges(Graph<Position, Street> & g, GraphViewer *gv);
Position findPosition(Graph<Position, Street> & g, unsigned long ID);
float calcWeight(Position from, Position to);

#endif