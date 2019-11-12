#include <iostream>
#include <vector>
#include <limits>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::numeric_limits;

// 1. 我爱北大
// 无向图
// 两点之间可能存在多条路线

struct Edge {
	// 相邻点
	int adjVex;
	Edge* nextArc;
	int weight;
	Edge(int a, int w) :adjVex(a), weight(w), nextArc(NULL) {}
	Edge() :adjVex(0), weight(0), nextArc(NULL) {}
};

struct AdjList {
	string data;
	Edge* firstArc;
	AdjList() :firstArc(NULL) {}
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
	void addVertex(string data);
	void setEdge(int fromVertex, int toVertex, int weight);
	bool isVisited(int vertices);
	void setVisited(int vertex, bool value);
	int toVertex(Edge* edge);
	int Weight(Edge* edge);
	string getVertex(int vertex);
	int indexOf(string data);
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

void Graph::addVertex(string data) {
	this->vertices[numVertex++].data = data;
}

void Graph::setEdge(int fromVertex, int toVertex, int weight) {

	// 替代旧值
	bool flag = false;
	Edge* curEdge = this->vertices[fromVertex].firstArc;
	while (curEdge != NULL) {
		if (this->toVertex(curEdge) == toVertex) {
			flag = true;
			if (weight < this->Weight(curEdge)) {
				curEdge->weight = weight;
			}
			break;
		}
		curEdge = curEdge->nextArc;
	}
	curEdge = this->vertices[toVertex].firstArc;
	while (curEdge != NULL) {
		if (this->toVertex(curEdge) == fromVertex) {
			flag = true;
			if (weight < this->Weight(curEdge)) {
				curEdge->weight = weight;
			}
			break;
		}
		curEdge = curEdge->nextArc;
	}
	if (flag) {
		return;
	}


	// 添加边，如果不存在重复
	Edge* newEdge = new Edge(toVertex, weight);
	// 放到边表的最后一个
	curEdge = this->vertices[fromVertex].firstArc;
	if (curEdge == NULL) {
		this->vertices[fromVertex].firstArc = newEdge;
	} else {
		while (curEdge->nextArc != NULL) {
			curEdge = curEdge->nextArc;
		}
		curEdge->nextArc = newEdge;
	}
	this->numEdge++;

	newEdge = new Edge(fromVertex, weight);
	// 放到边表的最后一个
	curEdge = this->vertices[toVertex].firstArc;
	if (curEdge == NULL) {
		this->vertices[toVertex].firstArc = newEdge;
	} else {
		while (curEdge->nextArc != NULL) {
			curEdge = curEdge->nextArc;
		}
		curEdge->nextArc = newEdge;
	}
	this->numEdge++;
}

bool Graph::isVisited(int vertex) {
	return mark[vertex];
}

void Graph::setVisited(int vertex, bool value) {
	mark[vertex] = value;
}

int Graph::toVertex(Edge* edge) {
	return edge->adjVex;
}

int Graph::Weight(Edge* edge) {
	return edge->weight;
}

string Graph::getVertex(int vertex) {
	return this->vertices[vertex].data;
}

int Graph::indexOf(string data) {
	for (int i = 0; i < numVertex; i++) {
		if (this->vertices[i].data == data) {
			return i;
		}
	}
	return -1;
}

struct Dist {
	int length;	// 当前顶点的单源最短路径
	int pre;	// 路径中的前一个顶点，用于存储最短路径
};

void floyd(Graph& graph, Dist** &dist) {
	// 初始化
	dist = new Dist*[graph.verticesNum()];
	for (int i = 0; i < graph.verticesNum(); i++) {
		dist[i] = new Dist[graph.verticesNum()];
	}
	for (int i = 0; i < graph.verticesNum(); i++) {
		for (int j = 0; j < graph.verticesNum(); j++) {
			if (i == j) {
				dist[i][j].length = 0;
				dist[i][j].pre = i;
			} else {
				dist[i][j].length = numeric_limits<int>::max();
				dist[i][j].pre = -1;
			}
		}
	}

	// 更新直接路径
	for (int vex = 0; vex < graph.verticesNum(); vex++) {
		for (Edge* edge = graph.firstEdge(vex); edge != NULL; edge = graph.nextEdge(edge)) {
			dist[vex][graph.toVertex(edge)].length = graph.Weight(edge);
			dist[vex][graph.toVertex(edge)].pre = vex;
		}
	}

	// 用每个顶点作为中间点更新，原两点间的路径
	for (int v = 0; v < graph.verticesNum(); v++) {
		for (int i = 0; i < graph.verticesNum(); i++) {
			for (int j = 0; j < graph.verticesNum(); j++) {
				// 因为将不连通的距离设置为了int最大值
				// 这里是为了防止溢出
				if (dist[i][v].length != numeric_limits<int>::max() &&
					dist[v][j].length != numeric_limits<int>::max() &&

					dist[i][j].length > dist[i][v].length + dist[v][j].length) {

					dist[i][j].length = dist[i][v].length + dist[v][j].length;
					dist[i][j].pre = dist[v][j].pre;
				}
			}
		}
	}
}

int main(int argc, char *argv[]) {
	Graph graph;

	int p = 0;
	cin >> p;
	for (int i = 0; i < p; i++) {
		string site;
		cin >> site;
		graph.addVertex(site);
	}

	int q = 0;
	cin >> q;
	for (int i = 0; i < q; i++) {
		string site1;
		string site2;
		int weight = 0;
		cin >> site1 >> site2 >> weight;
		graph.setEdge(graph.indexOf(site1), graph.indexOf(site2), weight);
	}

	// 计算两点间最小路径
	Dist** dist = NULL;
	floyd(graph, dist);

	int r = 0;
	cin >> r;
	for (int i = 0; i < r; i++) {
		string site1;
		string site2;
		cin >> site1 >> site2;

		int vex1 = graph.indexOf(site1);
		int vex2 = graph.indexOf(site2);

		// 从后往前推路径
		vector<int> route;
		while (vex2 != vex1) {
			route.push_back(vex2);
			vex2 = dist[vex1][vex2].pre;
		}
		route.push_back(vex1);

		// 输出
		for (int i = route.size() - 1; i >= 1; i--) {

			// 找到边的权重
			int weight = 0;
			for (Edge* edge = graph.firstEdge(route[i]); edge != NULL; edge = graph.nextEdge(edge)) {
				if (graph.toVertex(edge) == route[i - 1]) {
					weight = graph.Weight(edge);
					break;
				}
			}

			cout << graph.getVertex(route[i]) << "->(" << weight << ")->";
		}
		cout << graph.getVertex(route[0]) << endl;
	}

	return 0;
}