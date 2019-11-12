#include <iostream>
#include <queue>
#include <cmath>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

// 2. 拓扑排序

class Edge {
public:
	// 相邻点
	int adjVex;
	Edge* nextArc;
	int weight;
	Edge(int a, int w) :adjVex(a), weight(w), nextArc(NULL) {}
	Edge() :adjVex(0), weight(0), nextArc(NULL) {}
};

class AdjList {
public:
	int data;
	Edge* firstArc;
	AdjList() :firstArc(NULL), data(0) {}
};

class Graph {
private:
	int numVertex = 0;
	int numEdge = 0;
	// 图的顶点访问标记
	bool mark[30];
	// 存放图中顶点的入度
	int Indegree[30];
	// 邻接表
	AdjList vertices[50];

public:
	int verticesNum();
	int edgesNum();
	// 顶点的第一条关联边
	Edge* firstEdge(int vertex);
	// 下一条兄弟边
	Edge* nextEdge(Edge* preEdge);
	void addVertex(int data);
	void setEdge(int fromVertex, int toVertex, int weight);
	bool delEdge(int fromVertex, int toVertex);
	bool isVisited(int vertices);
	void setVisited(int vertex, bool value);
	//int FromVertex(Edge* edge);
	int ToVertex(Edge* edge);
	int Weight(Edge* edge);
	int getVertex(int vertex);
	int indexOf(int data);
	int getIndegree(int vertex);
};

int Graph::verticesNum() {
	return numVertex;
}

int Graph::edgesNum() {
	return numEdge;
}

Edge* Graph::firstEdge(int vertex) {
	return this->vertices[vertex].firstArc;
}

Edge* Graph::nextEdge(Edge* preEdge) {
	return preEdge->nextArc;
}

void Graph::addVertex(int data) {
	this->Indegree[numVertex] = 0;
	this->vertices[numVertex++].data = data;
}

void Graph::setEdge(int fromVertex, int toVertex, int weight) {

	Edge* newEdge = new Edge(toVertex, weight);
	// 放到边表的最后一个
	Edge* curEdge = this->vertices[fromVertex].firstArc;
	if (curEdge == NULL) {
		this->vertices[fromVertex].firstArc = newEdge;
	} else {
		while (curEdge->nextArc != NULL) {
			curEdge = curEdge->nextArc;
		}
		curEdge->nextArc = newEdge;
	}
	this->numEdge++;
	this->Indegree[toVertex]++;
}

bool Graph::delEdge(int fromVertex, int toVertex) {

	Edge* curEdge = this->vertices[fromVertex].firstArc;
	Edge* preEdge = curEdge;

	if (curEdge->adjVex == toVertex) {
		Edge* temp = this->vertices[fromVertex].firstArc;
		this->vertices[fromVertex].firstArc = temp->nextArc;
		delete temp;
		this->numEdge--;
		this->Indegree[toVertex]--;
		return true;
	}

	for (; curEdge != NULL; curEdge = curEdge->nextArc, preEdge = curEdge) {
		if (curEdge->adjVex == toVertex) {
			Edge* temp = curEdge;
			preEdge->nextArc = curEdge->nextArc;
			this->numEdge--;
			delete curEdge;
			this->Indegree[toVertex]--;
			return true;
		}
	}

	return false;
}

bool Graph::isVisited(int vertex) {
	return mark[vertex];
}

void Graph::setVisited(int vertex, bool value) {
	mark[vertex] = value;
}

int Graph::ToVertex(Edge* edge) {
	return edge->adjVex;
}

int Graph::Weight(Edge* edge) {
	return edge->weight;
}

int Graph::getVertex(int vertex) {
	return this->vertices[vertex].data;
}

int Graph::indexOf(int data) {
	for (int i = 0; i < numVertex; i++) {
		if (this->vertices[i].data == data) {
			return i;
		}
	}
	return -1;
}

int Graph::getIndegree(int vertex) {
	return this->Indegree[vertex];
}

vector<int> topoSort(Graph& graph) {

	for (int i = 0; i < graph.verticesNum(); i++) {
		graph.setVisited(i, false);
	}

	vector<int> res;

	while (true) {
		// 寻找入度为0的点
		int vex = -1;
		for (int i = 0; i < graph.verticesNum(); i++) {
			if (graph.getIndegree(i) == 0 && graph.isVisited(i) == false) {
				vex = i;
				graph.setVisited(vex, true);
				break;
			}
		}
		// 所有顶点都完成排序，或者存在回路
		if (vex == -1) {
			return res;
		}

		res.push_back(graph.getVertex(vex));
		for (Edge* edge = graph.firstEdge(vex); edge != NULL; edge = graph.firstEdge(vex)) {
			graph.delEdge(vex, graph.ToVertex(edge));
		}
	}

	return res;
}

int main(int argc, char *argv[]) {
	Graph graph;

	int v = 0;
	int a = 0;
	cin >> v >> a;

	for (int i = 0; i < v; i++) {
		graph.addVertex(i + 1);
	}

	for (int i = 0; i < a; i++) {
		int fromVex = 0;
		int toVex = 0;
		cin >> fromVex >> toVex;
		graph.setEdge(fromVex - 1, toVex - 1, 0);
	}

	vector<int> res = topoSort(graph);

	for (int i = 0; i < res.size(); i++) {
		int num = res[i];
		cout << 'v' << res[i] << ' ';
	}

	return 0;
}
