#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <stdlib.h>
#include <ctime>
#include <set>
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
    gv->defineVertexColor("green");
    gv->defineEdgeColor("black");
    gv->defineEdgeCurved(false);
    gv->rearrange();

    set<string> streets;

    bool filesRead = false;
    string street1str, street2str;


    readPositions(g, gv);
    readEdges(g, gv, streets);
    for(auto iter=streets.begin(); iter!=streets.end();++iter) {
        cout << *iter << endl;
    }
/*
    int menu = 0;
    while (menu != 5) {
        menu = getMenu("Read files,Insert origin and destination,Add accident,Calculate path,Exit");
        switch (menu) {
            case 1:
                readPositions(g, gv);
                readEdges(g, gv, streets);
                filesRead = true;
                break;
            case 2:
                if (filesRead) {
                    cout << "Please insert starting position\nStreet 1:";
                    cin >> street1str;
                    cout << "Street 2:";
                    cin >> street2str;
                }
                else
                    cout << "must read files first!\n";
                system("pause");
                break;
            case 3:
                if (filesRead) {
                    cout << "Por favor insira as coordenadas do acidente\n";
                    while (accidentLat < miny || accidentLat > maxy || accidentLong < minx || accidentLong > maxx) {
                        cout << "Introduza a latitude: \n";
                        cin >> accidentLat;
                        cout << "Introduza a longitude: \n";
                        cin >> accidentLong;
                        system("cls");
                    }
                    accident = new Position(accidentLong, accidentLat);

                    if (g.getVertex(*accident) == NULL)
                        cout << "coordenadas do acidente nao existem\n";
                    else
                        g.removeVertex(*accident);
                }
                else
                    cout << "must read files first!\n";
                system("pause");
                break;
            case 4:
                if (filesRead && coordsOK) {
                    g.dijkstraShortestPath(*userO);
                    while (true) {
                        cout << g.getVertex(*userD)->path->getInfo().getLatDeg() << ',' << g.getVertex(*userD)->path->getInfo().getLonDeg() << endl;
                        *userD = g.getVertex(*userD)->path->getInfo();
                    }
                }
                else
                    cout << "must read files and add origin and destination first!\n";
                system("pause");
                break;
        }
    }
*/
	return 0;
}
