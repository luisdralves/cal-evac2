#include "readFiles.h"

using namespace std;

/**
* Calculates the distance from a node to another(in km)
*/
float calcWeight(Position from, Position to) {
	int r = 6371; // raio da terra em kms
	float dLat = to.getLatRad() - from.getLatRad();
	float dLon = to.getLonRad() - from.getLonRad();
	float a = sin(dLat / 2) * sin(dLat / 2)
		+ cos(from.getLatRad()) * cos(to.getLatRad()) * sin(dLon / 2)
		* sin(dLon / 2);
	float c = 2 * atan2(sqrt(a), sqrt(1 - a));
	float d = r * c;

	return d;
}

/**
* Finds a node in the graph, through his ID
*/
Position findNode(Graph<Position, Street> & g, unsigned long ID) {
	for (unsigned int i = 0; i < g.getVertexSet().size(); i++) {
		if (g.getVertexSet().at(i)->getInfo().getId() == ID) {
			return g.getVertexSet().at(i)->getInfo();
		}
	}
}

/**
* Reads the nodes from a file and loads them into the graph
*/
void readPositions(Graph<Position, Street> & g, GraphViewer *gv) {
	ifstream inFile;

	inFile.open("vertices.txt");

	if (!inFile) {
		cerr << "Unable to open file vertices.txt";
		return;
	}

	string line;
	unsigned long long idNo = 0;
	double lat_deg = 0, lon_deg = 0, lat_rad = 0, lon_rad = 0;

	while (getline(inFile, line)) {
		stringstream linestream(line);
		string data;

		linestream >> idNo;

		getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> lat_deg;
		getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> lon_deg;/*
		getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> lon_rad;
		getline(linestream, data, ';'); // read up-to the first ; (discard ;).
		linestream >> lat_rad;*/
		Position n(idNo, lat_deg, lon_deg, lat_rad, lon_rad);
		g.addVertex(n);
		/*gv->addNode(idNo, 60000 - (((lon_deg)-(long)(lon_deg)) * -100000),
				17000 - (((lat_deg)-(long)(lat_deg)) * 100000));*/
		gv->addNode(idNo, lon_deg, lat_deg);
	}

	inFile.close();

}

/**
* Reads the edges from a file and loads them into the graph
*/
void readEdges(Graph<Position, Street> & g, GraphViewer *gv, set<string> & streets) {
	ifstream inFile;

	inFile.open("graph.txt");

	if (!inFile) {
		cerr << "Unable to open file graph.txt";
		return;
	}


	string line;
	unsigned long long streetID;
	unsigned long long position1ID, position2ID;


	while (getline(inFile, line)) {
        stringstream linestream(line);
        string data;
        string two_way;

        linestream >> streetID;

        getline(linestream, data, ';'); // read up-to the first ; (discard ;).
        linestream >> position1ID;
        getline(linestream, data, ';'); // read up-to the first ; (discard ;).
        linestream >> position2ID;

        float weight = calcWeight(findNode(g, position1ID), findNode(g, position2ID));

        Street *r = readStreets(streetID, gv);
        if (r->is_two_way()) {
            g.addEdge1(findNode(g, position2ID), findNode(g, position1ID), weight, *r);
            gv->addEdge(streetID, position1ID, position2ID, EdgeType::UNDIRECTED);
        }
        else
            gv->addEdge(streetID, position1ID, position2ID, EdgeType::DIRECTED);

        g.addEdge1(findNode(g, position1ID), findNode(g, position2ID), weight, *r);
        gv->setEdgeLabel(streetID, r->getName());

        streets.insert(r->getName());
    }


    inFile.close();

}

/**
* Finds the info of a road, through the ID of the road
*/
Street* readStreets(unsigned long streetID, GraphViewer *gv) {
	ifstream inFile;

	inFile.open("edges.txt");

	if (!inFile) {
		cerr << "Unable to open file edges.txt";
		exit(1);
	}


	string line;
	unsigned long idNo = 0;
	string name;
	string two_way;

	while (getline(inFile, line)) {
		stringstream linestream(line);
		string data;

		linestream >> idNo;

		stringstream s(line);
		getline(s, data, ';'); // read up-to the first ; (discard ;).
		getline(s, name, ';'); // read up-to the first ; (discard ;).
		getline(s, two_way); // read up-to the first ; (discard ;).

		if (idNo == streetID) {
			if (two_way == "False") {
				return new Street(idNo, name, false);

			}
			else {
				return new Street(idNo, name, true);
			}
		}
	}

	inFile.close();
}
