#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <stdlib.h>
using namespace std;

template <class T, class U>
class Edge1;

template <class T, class U>
class Graph;

const int NOT_VISITED = 0;
const int BEING_VISITED = 1;
const int DONE_VISITED = 2;
const int INT_INFINITY = numeric_limits<int>::max();

/*
* ================================================================================================
* Class Vertex
* ================================================================================================
*/
template <class T, class U>
class Vertex {
	T info;
	vector<Edge1<T, U> > adj;
	bool visited;
	bool processing;
	int indegree;
	double dist;
public:

	Vertex(T in);
	friend class Graph<T, U>;

	vector<Edge1<T, U> > getAdj();
	void addEdge1(Vertex<T, U> *dest, double w, U info);
	bool removeEdge1To(Vertex<T, U> *d);

	T getInfo() const;
	void setInfo(T info);

	int getDist() const;
	int getIndegree() const;

	bool operator<(const Vertex<T, U> vertex);

	Vertex* path;
};

template <class T, class U>
vector<Edge1<T, U> > Vertex<T, U>::getAdj() {
	return adj;
}

template <class T, class U>
struct vertex_greater_than {
	bool operator()(Vertex<T, U> * a, Vertex<T, U> * b) const {
		return a->getDist() > b->getDist();
	}
};

template <class T, class U>
bool Vertex<T, U>::removeEdge1To(Vertex<T, U> *d) {
	d->indegree--; //adicionado do exercicio 5
	typename vector<Edge1<T, U> >::iterator it = adj.begin();
	typename vector<Edge1<T, U> >::iterator ite = adj.end();
	while (it != ite) {
		if (it->dest == d) {
			adj.erase(it);
			return true;
		}
		else it++;
	}
	return false;
}

//atualizado pelo exerc�cio 5
template <class T, class U>
Vertex<T, U>::Vertex(T in) : info(in), visited(false), processing(false), indegree(0), dist(0) {
	path = NULL;
}


template <class T, class U>
void Vertex<T, U>::addEdge1(Vertex<T, U> *dest, double w, U info) {
	Edge1<T, U> Edge1D(dest, w, info);
	adj.push_back(Edge1D);
}

//--
template <class T, class U>
T Vertex<T, U>::getInfo() const {
	return this->info;
}

template <class T, class U>
int Vertex<T, U>::getDist() const {
	return this->dist;
}


template <class T, class U>
void Vertex<T, U>::setInfo(T info) {
	this->info = info;
}

template <class T, class U>
int Vertex<T, U>::getIndegree() const {
	return this->indegree;
}




/* ================================================================================================
* Class Edge1
* ================================================================================================
*/
template <class T, class U>
class Edge1 {
	Vertex<T, U> * dest;
	double weight;
	U info;
public:
	Edge1(Vertex<T, U> *d, double w, U info);
	void setInfo(T in);
	friend class Graph<T, U>;
	friend class Vertex<T, U>;
	U getInfo();
	double getWeight() const;
	Vertex<T, U>  getDest() const;
};
template <class T, class U>
U Edge1<T, U>::getInfo() {
	return info;
}

template<class T, class U>
Vertex<T, U>  Edge1<T, U>::getDest() const {
	Vertex<T, U> v = *dest;
	return v;
}

template<class T, class U>
double Edge1<T, U>::getWeight() const {
	return weight;
}

template <class T, class U>
Edge1<T, U>::Edge1(Vertex<T, U> *d, double w, U info) : dest(d), weight(w), info(info) {}





/* ================================================================================================
* Class Graph
* ================================================================================================
*/
template <class T, class U>
class Graph {
	vector<Vertex<T, U> *> vertexSet;
	void dfs(Vertex<T, U> *v, vector<T> &res) const;

	//exercicio 5
	int numCycles;
	void dfsVisit(Vertex<T, U> *v);
	void dfsVisit();
	void getPathTo(Vertex<T, U> *origin, list<T> &res);

	//exercicio 6
	int ** W;   //weight
	int ** P;   //path

public:
	bool addVertex(const T &in);
	bool addEdge1(const T &sourc, const T &dest, double w, U &info);
	bool removeVertex(const T &in);
	bool removeEdge1(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(Vertex<T, U> *v) const;
	int maxNewChildren(Vertex<T, U> *v, T &inf) const;
	vector<Vertex<T, U> * > getVertexSet() const;
	int getNumVertex() const;

	//exercicio 5
	Vertex<T, U>* getVertex(const T &v) const;
	void resetIndegrees();
	vector<Vertex<T, U>*> getSources() const;
	int getNumCycles();
	vector<T> topologicalOrder();
	vector<T> getPath(const T &origin, const T &dest);
	void unweightedShortestPath(const T &v);
	bool isDAG();

	//exercicio 6
	void bellmanFordShortestPath(const T &s);
	void dijkstraShortestPath(const T &s);
	void floydWarshallShortestPath();
	int Edge1Cost(int vOrigIndex, int vDestIndex);
	vector<T> getfloydWarshallPath(const T &origin, const T &dest);
	void getfloydWarshallPathAux(int index1, int index2, vector<T> & res);
};

template <class T, class U>
int Graph<T, U>::getNumVertex() const {
	return vertexSet.size();
}
template <class T, class U>
vector<Vertex<T, U> * > Graph<T, U>::getVertexSet() const {
	return vertexSet;
}

template <class T, class U>
int Graph<T, U>::getNumCycles() {
	numCycles = 0;
	dfsVisit();
	return this->numCycles;
}

template <class T, class U>
bool Graph<T, U>::isDAG() {
	return (getNumCycles() == 0);
}

template <class T, class U>
bool Graph<T, U>::addVertex(const T &in) {
	typename vector<Vertex<T, U>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T, U>*>::iterator ite = vertexSet.end();
	for (; it != ite; it++)
		if ((*it)->info == in) {
			cout << in.getId() << endl;
			return false;
		}
	Vertex<T, U> *v1 = new Vertex<T, U>(in);
	vertexSet.push_back(v1);
	return true;
}

template <class T, class U>
bool Graph<T, U>::removeVertex(const T &in) {
	typename vector<Vertex<T, U>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T, U>*>::iterator ite = vertexSet.end();
	for (; it != ite; it++) {
		if ((*it)->info == in) {
			Vertex<T, U> * v = *it;
			vertexSet.erase(it);
			typename vector<Vertex<T, U>*>::iterator it1 = vertexSet.begin();
			typename vector<Vertex<T, U>*>::iterator it1e = vertexSet.end();
			for (; it1 != it1e; it1++) {
				(*it1)->removeEdge1To(v);
			}

			typename vector<Edge1<T, U> >::iterator itAdj = v->adj.begin();
			typename vector<Edge1<T, U> >::iterator itAdje = v->adj.end();
			for (; itAdj != itAdje; itAdj++) {
				itAdj->dest->indegree--;
			}
			delete v;
			return true;
		}
	}
	return false;
}

template <class T, class U>
bool Graph<T, U>::addEdge1(const T &sourc, const T &dest, double w, U &info) {
	typename vector<Vertex<T, U>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T, U>*>::iterator ite = vertexSet.end();
	int found = 0;
	Vertex<T, U> *vS, *vD;
	while (found != 2 && it != ite) {
		if ((*it)->info == sourc)
		{
			vS = *it; found++;
		}
		if ((*it)->info == dest)
		{
			vD = *it; found++;
		}
		it++;
	}
	if (found != 2) return false;
	vD->indegree++;
	vS->addEdge1(vD, w, info);

	return true;
}

template <class T, class U>
bool Graph<T, U>::removeEdge1(const T &sourc, const T &dest) {
	typename vector<Vertex<T, U>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T, U>*>::iterator ite = vertexSet.end();
	int found = 0;
	Vertex<T, U> *vS, *vD;
	while (found != 2 && it != ite) {
		if ((*it)->info == sourc)
		{
			vS = *it; found++;
		}
		if ((*it)->info == dest)
		{
			vD = *it; found++;
		}
		it++;
	}
	if (found != 2)
		return false;

	vD->indegree--;

	return vS->removeEdge1To(vD);
}




template <class T, class U>
vector<T> Graph<T, U>::dfs() const {
	typename vector<Vertex<T, U>*>::const_iterator it = vertexSet.begin();
	typename vector<Vertex<T, U>*>::const_iterator ite = vertexSet.end();
	for (; it != ite; it++)
		(*it)->visited = false;
	vector<T> res;
	it = vertexSet.begin();
	for (; it != ite; it++)
		if ((*it)->visited == false)
			dfs(*it, res);
	return res;
}

template <class T, class U>
void Graph<T, U>::dfs(Vertex<T, U> *v, vector<T> &res) const {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge1<T, U> >::iterator it = (v->adj).begin();
	typename vector<Edge1<T, U> >::iterator ite = (v->adj).end();
	for (; it != ite; it++)
		if (it->dest->visited == false) {
			//cout << "ok ";
			dfs(it->dest, res);
		}
}

template <class T, class U>
vector<T> Graph<T, U>::bfs(Vertex<T, U> *v) const {
	vector<T> res;
	queue<Vertex<T, U> *> q;
	q.push(v);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T, U> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		typename vector<Edge1<T, U> >::iterator it = v1->adj.begin();
		typename vector<Edge1<T, U> >::iterator ite = v1->adj.end();
		for (; it != ite; it++) {
			Vertex<T, U> *d = it->dest;
			if (d->visited == false) {
				d->visited = true;
				q.push(d);
			}
		}
	}
	return res;
}

template <class T, class U>
int Graph<T, U>::maxNewChildren(Vertex<T, U> *v, T &inf) const {
	vector<T> res;
	queue<Vertex<T, U> *> q;
	queue<int> level;
	int maxChildren = 0;
	inf = v->info;
	q.push(v);
	level.push(0);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T, U> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		int l = level.front();
		level.pop(); l++;
		int nChildren = 0;
		typename vector<Edge1<T, U> >::iterator it = v1->adj.begin();
		typename vector<Edge1<T, U> >::iterator ite = v1->adj.end();
		for (; it != ite; it++) {
			Vertex<T, U> *d = it->dest;
			if (d->visited == false) {
				d->visited = true;
				q.push(d);
				level.push(l);
				nChildren++;
			}
		}
		if (nChildren>maxChildren) {
			maxChildren = nChildren;
			inf = v1->info;
		}
	}
	return maxChildren;
}


template <class T, class U>
Vertex<T, U>* Graph<T, U>::getVertex(const T &v) const {
	for (unsigned int i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == v) return vertexSet[i];
	return NULL;
}

template<class T, class U>
void Graph<T, U>::resetIndegrees() {
	//colocar todos os indegree em 0;
	for (unsigned int i = 0; i < vertexSet.size(); i++) vertexSet[i]->indegree = 0;

	//actualizar os indegree
	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		//percorrer o vector de Edges, e actualizar indegree
		for (unsigned int j = 0; j < vertexSet[i]->adj.size(); j++) {
			vertexSet[i]->adj[j].dest->indegree++;
		}
	}
}


template<class T, class U>
vector<Vertex<T, U>*> Graph<T, U>::getSources() const {
	vector< Vertex<T, U>* > buffer;
	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i]->indegree == 0) buffer.push_back(vertexSet[i]);
	}
	return buffer;
}


template <class T, class U>
void Graph<T, U>::dfsVisit() {
	typename vector<Vertex<T, U>*>::const_iterator it = vertexSet.begin();
	typename vector<Vertex<T, U>*>::const_iterator ite = vertexSet.end();
	for (; it != ite; it++)
		(*it)->visited = false;
	it = vertexSet.begin();
	for (; it != ite; it++)
		if ((*it)->visited == false)
			dfsVisit(*it);
}

template <class T, class U>
void Graph<T, U>::dfsVisit(Vertex<T, U> *v) {
	v->processing = true;
	v->visited = true;
	typename vector<Edge1<T, U> >::iterator it = (v->adj).begin();
	typename vector<Edge1<T, U> >::iterator ite = (v->adj).end();
	for (; it != ite; it++) {
		if (it->dest->processing == true) numCycles++;
		if (it->dest->visited == false) {
			dfsVisit(it->dest);
		}
	}
	v->processing = false;
}

template<class T, class U>
vector<T> Graph<T, U>::topologicalOrder() {
	//vetor com o resultado da ordenacao
	vector<T> res;

	//verificar se � um DAG
	if (getNumCycles() > 0) {
		cout << "Ordenacao Impossivel!" << endl;
		return res;
	}

	//garantir que os "indegree" estao inicializados corretamente
	this->resetIndegrees();

	queue<Vertex<T, U>*> q;

	vector<Vertex<T, U>*> sources = getSources();
	while (!sources.empty()) {
		q.push(sources.back());
		sources.pop_back();
	}


	//processar fontes
	while (!q.empty()) {
		Vertex<T, U>* v = q.front();
		q.pop();

		res.push_back(v->info);

		for (unsigned int i = 0; i < v->adj.size(); i++) {
			v->adj[i].dest->indegree--;
			if (v->adj[i].dest->indegree == 0) q.push(v->adj[i].dest);
		}
	}

	//testar se o procedimento foi bem sucedido
	if (res.size() != vertexSet.size()) {
		while (!res.empty()) res.pop_back();
	}

	//garantir que os "indegree" ficam atualizados ao final
	this->resetIndegrees();

	return res;
}



template<class T, class U>
vector<T> Graph<T, U>::getPath(const T &origin, const T &dest) {

	list<T> buffer;
	Vertex<T, U>* v = getVertex(dest);

	buffer.push_front(v->info);
	while (v->path != NULL &&  v->path->info != origin) {
		v = v->path;
		buffer.push_front(v->info);
	}
	if (v->path != NULL)
		buffer.push_front(v->path->info);


	vector<T> res;
	while (!buffer.empty()) {
		res.push_back(buffer.front());
		buffer.pop_front();
	}
	return res;
}

template<class T, class U>
vector<T> Graph<T, U>::getfloydWarshallPath(const T &origin, const T &dest) {

	int originIndex = -1, destinationIndex = -1;

	for (unsigned int i = 0; i < vertexSet.size(); i++)
	{
		if (vertexSet[i]->info == origin)
			originIndex = i;
		if (vertexSet[i]->info == dest)
			destinationIndex = i;

		if (originIndex != -1 && destinationIndex != -1)
			break;
	}


	vector<T> res;

	//se nao foi encontrada solucao possivel, retorna lista vazia
	if (W[originIndex][destinationIndex] == INT_INFINITY)
		return res;

	res.push_back(vertexSet[originIndex]->info);

	//se houver pontos intermedios...
	if (P[originIndex][destinationIndex] != -1)
	{
		int intermedIndex = P[originIndex][destinationIndex];

		getfloydWarshallPathAux(originIndex, intermedIndex, res);

		res.push_back(vertexSet[intermedIndex]->info);

		getfloydWarshallPathAux(intermedIndex, destinationIndex, res);
	}

	res.push_back(vertexSet[destinationIndex]->info);


	return res;
}



template<class T, class U>
void Graph<T, U>::getfloydWarshallPathAux(int index1, int index2, vector<T> & res)
{
	if (P[index1][index2] != -1)
	{
		getfloydWarshallPathAux(index1, P[index1][index2], res);

		res.push_back(vertexSet[P[index1][index2]]->info);

		getfloydWarshallPathAux(P[index1][index2], index2, res);
	}
}


template<class T, class U>
void Graph<T, U>::unweightedShortestPath(const T &s) {

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = "";
		vertexSet[i]->dist = INT_INFINITY;
	}

	Vertex<T, U>* v = getVertex(s);
	v->dist = 0;
	queue< Vertex<T, U>* > q;
	q.push(v);

	while (!q.empty()) {
		v = q.front(); q.pop();
		for (unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T, U>* w = v->adj[i].dest;
			if (w->dist == INT_INFINITY) {
				w->dist = v->dist + 1;
				w->path = v;
				q.push(w);
			}
		}
	}
}


template<class T, class U>
void Graph<T, U>::bellmanFordShortestPath(const T &s) {

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = "";
		vertexSet[i]->dist = INT_INFINITY;
	}

	Vertex<T, U>* v = getVertex(s);
	v->dist = 0;
	queue< Vertex<T, U>* > q;
	q.push(v);

	while (!q.empty()) {
		v = q.front(); q.pop();
		for (unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T, U>* w = v->adj[i].dest;
			if (v->dist + v->adj[i].weight < w->dist) {
				w->dist = v->dist + v->adj[i].weight;
				w->path = v;
				q.push(w);
			}
		}
	}
}





template<class T, class U>
void Graph<T, U>::dijkstraShortestPath(const T &s) {

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
		vertexSet[i]->processing = false;
	}

	Vertex<T, U>* v = getVertex(s);
	v->dist = 0;

	vector< Vertex<T, U>* > pq;
	pq.push_back(v);

	make_heap(pq.begin(), pq.end());


	while (!pq.empty()) {

		v = pq.front();
		pop_heap(pq.begin(), pq.end());
		pq.pop_back();

		for (unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T, U>* w = v->adj[i].dest;

			if (v->dist + v->adj[i].weight < w->dist) {

				w->dist = v->dist + v->adj[i].weight;
				w->path = v;

				//se j� estiver na lista, apenas a actualiza
				if (!w->processing)
				{
					w->processing = true;
					pq.push_back(w);
				}

				make_heap(pq.begin(), pq.end(), vertex_greater_than<T, U>());
			}
		}
	}
}

template<class T, class U>
int Graph<T, U>::Edge1Cost(int vOrigIndex, int vDestIndex)
{
	if (vertexSet[vOrigIndex] == vertexSet[vDestIndex])
		return 0;

	for (unsigned int i = 0; i < vertexSet[vOrigIndex]->adj.size(); i++)
	{
		if (vertexSet[vOrigIndex]->adj[i].dest == vertexSet[vDestIndex])
			return vertexSet[vOrigIndex]->adj[i].weight;
	}

	return INT_INFINITY;
}


/*void printSquareArray(int ** arr, unsigned int size)
{
for(unsigned int k = 0; k < size; k++)
{
if(k == 0)
{
cout <<  "   ";
for(unsigned int i = 0; i < size; i++)
cout <<  " " << i+1 << " ";
cout << endl;
}
for(unsigned int i = 0; i < size; i++)
{
if(i == 0)
cout <<  " " << k+1 << " ";
if(arr[k][i] == INT_INFINITY)
cout << " - ";
else
cout <<  " " << arr[k][i] << " ";
}
cout << endl;
}
}*/


template<class T, class U>
void Graph<T, U>::floydWarshallShortestPath() {

	W = new int *[vertexSet.size()];
	P = new int *[vertexSet.size()];
	for (unsigned int i = 0; i < vertexSet.size(); i++)
	{
		W[i] = new int[vertexSet.size()];
		P[i] = new int[vertexSet.size()];
		for (unsigned int j = 0; j < vertexSet.size(); j++)
		{
			W[i][j] = Edge1Cost(i, j);
			P[i][j] = -1;
		}
	}


	for (unsigned int k = 0; k < vertexSet.size(); k++)
		for (unsigned int i = 0; i < vertexSet.size(); i++)
			for (unsigned int j = 0; j < vertexSet.size(); j++)
			{
				//se somarmos qualquer coisa ao valor INT_INFINITY, ocorre overflow, o que resulta num valor negativo, logo nem conv�m considerar essa soma
				if (W[i][k] == INT_INFINITY || W[k][j] == INT_INFINITY)
					continue;

				int val = min(W[i][j], W[i][k] + W[k][j]);
				if (val != W[i][j])
				{
					W[i][j] = val;
					P[i][j] = k;
				}
			}

}


#endif /* GRAPH_H_ */