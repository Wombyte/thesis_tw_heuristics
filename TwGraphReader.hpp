#include "Graph.hpp"
#include "TwStorage.hpp"
#include "GraphReader.hpp"

using namespace std;

#ifndef TW_GRAPH_READER_H
#define TW_GRAPH_READER_H

class TwGraphReader : public GraphReader<TwStorage> {
    public:
    TwGraphReader() {}

    void read(Graph<TwStorage>* g) {
		int n, m;
		cin >> n >> m;
        vector<pair<int,int>> storage (n);
		int order, x, y;

		for (int i = 0; i < n; i++) {
			cin >> order >> x >> y;
			storage[order] = {x, y};
		}
		for (int order = 0; order < n; order++) {
			TwStorage twst;
			twst.coordinates = storage[order];
			g->addNode(twst);
		}

		int a, b;
		for (int j = 0; j < m; j++) {
			cin >> a >> b;
			g->addEdge({a,b});
		}
	}
};

#endif