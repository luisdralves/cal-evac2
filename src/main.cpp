#include "main.h"

int main() {
	Graph<Position, Street> g;

    GraphViewer *gv = new GraphViewer(600, 600, false);

    set<pair<Street, pair<int, int>>> streets;

    bool filesRead = false;
    bool coordsOK = false;
    int id1 = -1, id2 = 14;

    cout << " _______________Sistema de Evacuacao_____________" << endl;
    cout << "|                                                |" << endl;
    cout << "|              _____________[\\_                  |" << endl;
    cout << "|             /  _|_    .--..--\\                 |" << endl;
    cout << "|             |)  |     [__][___\\___             |" << endl;
    cout << "|             |        |   -|-   __ `\\           |" << endl;
    cout << "|           _(  .----. |    |   /  \\ [)          |" << endl;
    cout << "|           `\'---\\__/-----------\\__/--\'          |" << endl;


    int menu = 0;
    while (menu != 4) {
        menu = getMenu("Read files,Insert your position,Calculate path,Exit");
        switch (menu) {
            case 1:
                gv->createWindow(600, 600);
                gv->defineEdgeDashed(false);
                gv->defineVertexColor("green");
                gv->defineEdgeColor("black");
                gv->defineEdgeCurved(false);
                gv->rearrange();
                readPositions(g, gv);
                gv->setVertexIcon(id2, "hospital.png");
                readEdges(g, gv, streets);
                gv->rearrange();
                filesRead = true;
                break;
            case 2:
                if (filesRead) {
                    int submenu = getMenu("Approximate position,Exact position");
                    switch (submenu) {
                        case 1:
                            id1 = getApxIntersection(streets);
                            if (id1 == -1)
                                cout << "Those streets never cross, we are expecting an intersection between two streets\n";
                            break;
                        case 2:
                            id1 = getExaIntersection(streets);
                            if (id1 == -1)
                                cout << "Unknown location\n";
                            break;
                    }
                    if (id1 != -1) {
                        coordsOK = true;
                        gv->setVertexColor(id1, "red");
                        gv->rearrange();
                    }
                }
                else
                    cout << "Must read files first!\n";
                system("pause");
                break;

            case 3:
                if (filesRead && coordsOK) {
                    Position  p1(id1,0,0);
                    Position  p2(id2,0,0);
                    vector<Position> path = g.getPath(p1, p2);
                    for(int i = 0; i < path.size(); i++)
                        cout << path[i].getId() << " -> " << path[i].getLatDeg() << ", " << path[i].getLonDeg() << endl;
                }
                else
                    cout << "Must read files and specify position!\n";
                system("pause");
                break;
        }
    }

	return 0;
}

int getApxIntersection(set<pair<Street, pair<int, int>>> streets) {
    string street1str, street2str;
    cout << "Please insert starting position\nStreet 1: ";
    cin.ignore(1000, '\n');
    getline(cin, street1str);
    street1str = closestStreet(streets, street1str);
    cout << "Street 2: ";
    getline(cin, street2str);
    street2str = closestStreet(streets, street2str);
    Street * st1 = new Street(0, street1str, true);
    Street * st2 = new Street(0, street2str, true);
    return st1->getIntersection(*st2, streets);
}

int getExaIntersection(set<pair<Street, pair<int, int>>> streets) {
    string street1str, street2str;
    cout << "Please insert starting position\nStreet 1: ";
    cin.ignore(1000, '\n');
    getline(cin, street1str);
    street1str = exactStreet(streets, street1str);
    cout << "Street 2: ";
    getline(cin, street2str);
    street2str = exactStreet(streets, street2str);
    Street * st1 = new Street(0, street1str, true);
    Street * st2 = new Street(0, street2str, true);
    return st1->getIntersection(*st2, streets);
}
