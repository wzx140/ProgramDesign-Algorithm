#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::priority_queue;
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
	int index;	// 当前顶点的索引
	int length;	// 当前顶点的单源最短路径
	int pre;	// 路径中的前一个顶点，用于存储最短路径
};

struct cmp {
	bool operator() (const Dist& a, const Dist& b) {
		return a.length > b.length;
	}
};

void dijkstra(Graph& graph, int s, Dist* &dist) {
	// 初始化
	dist = new Dist[graph.verticesNum()];
	for (int i = 0; i < graph.verticesNum(); i++) {
		graph.setVisited(i, false);
		dist[i].length = numeric_limits<int>::max();
		dist[i].index = i;
		dist[i].pre = s;
	}

	// 最小堆
	priority_queue<Dist, vector<Dist>, cmp> heap;
	// 放入源点
	dist[s].length = 0;
	heap.push(dist[s]);

	for (int i = 0; i < graph.verticesNum(); i++) {
		Dist d;

		bool found = false;
		while (!heap.empty()) {
			// 找到拥有最短路径的点
			d = heap.top();
			heap.pop();
			// 防止访问旧顶点
			if (!graph.isVisited(d.index)) {
				found = true;
				break;
			}
		}
		// 没有与源点连通的顶点了
		if (!found) {
			break;
		}

		// 更新
		int fromVertex = d.index;
		graph.setVisited(fromVertex, true);
		for (Edge* edge = graph.firstEdge(fromVertex); edge != NULL; edge = graph.nextEdge(edge)) {
			// 相邻点到源点的长度小于两边之和
			int toVertex = graph.toVertex(edge);
			if (dist[toVertex].length > (dist[fromVertex].length + graph.Weight(edge))) {
				dist[toVertex].length = dist[fromVertex].length + graph.Weight(edge);
				dist[toVertex].pre = fromVertex;
				heap.push(dist[toVertex]);
				// 这里没有删除旧顶点，因为旧顶点与新顶点拥有相同的索引
				// 但是新顶点总在旧顶点之前取出(比它小)，该索引被标记为visited
				// 所以旧顶点不会被访问到，节省了删除顶点的时间
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
	Dist** dist = new Dist*[graph.verticesNum()];
	for (int i = 0; i < graph.verticesNum(); i++) {
		dijkstra(graph, i, dist[i]);
	}

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