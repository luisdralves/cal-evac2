#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <stdlib.h>
#include <set>
#include "Graph.h"
#include "Position.h"
#include "Street.h"
#include "readFiles.h"
#include "menus.h"
#include "Matcher.h"

using namespace std;

int getApxIntersection(set<pair<Street, pair<int, int>>> streets);
int getExaIntersection(set<pair<Street, pair<int, int>>> streets);
int main();

#endif //_MAIN_H
