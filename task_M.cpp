#include <iostream>
#include <vector>

typedef Vertex size_t

enum VertexMark {
	WHITE,
	GRAY,
	BLACK
};

struct Edge {
	int weight;
	int f = 0;
	Vertex from;
	Vertex to;
	Edge (Vertex s, Vertex f, int w) {
		from = s;
		to = f;
		weight = w;
	}
};

class TransportNetwork {
private:
	int s, t;
	std::vector<std::vector<Edge>> graph;
	
	int dfs(int u, int c) {
		if (u == t) {
			return c;
		}
		vertex_mark[u] = GRAY;
		for (Edge i: graph[u]) {
			if (vertex_mark[i.to] == WHITE && i.f < i.w) {
				int delta = dfs(v, std::min(c, i.w - i.f));
				if (delta > 0) {
					i.f += delta;
					i.
				}
			}
		}
	}
	
public:
	int Ford-Falkerson() {
		std::vector<VertexMark> vertex_mark(graph.size(), WHITE);
		
	}
};

int main() {
	
}
