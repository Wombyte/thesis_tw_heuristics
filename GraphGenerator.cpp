#include <iostream>
#include <string>
#include <vector>
#include "Graph.hpp"
#include "CoordinatesGraphWriter.hpp"
#include "GraphWriter.hpp"

using namespace std;

class GraphGenerator {
	private:
	CoordinatesGraphWriter writer;

	public:
	GraphGenerator() {}
	GraphGenerator(bool perm) {
		this->writer = new CoordinatesGraphWriter(perm);
	}

	virtual void generate() {
		Graph<pair<int,int>> g;
		getGraph(&g);
		this->writer.reset();
		this->writer.add(&g);
		this->writer.print();
	}

	virtual void getGraph(Graph<pair<int,int>>* g) const = 0;
};

class GridGenerator : public GraphGenerator {
	private:
	int h;
	int w;

	public:
	int gridCooToNumber(int x, int y) const {
		return y*w + x;
	}

	pair<int,int> numberToCoo(int i) const {
		return pair<int,int> (i % w, i / w);
	}

	GridGenerator() {}
	GridGenerator(int h, int w, bool perm) : GraphGenerator(perm) {
		this->h = h;
		this->w = w;
	}

	void getGraph(Graph<pair<int,int>>* g) const {
		int nodes = this->w * this->h;
		pair<int,int> gridcoo;
		for (int i = 0; i < nodes; i++) {
			gridcoo = numberToCoo(i);
			g->addNode(pair<int,int> (gridcoo.first*4, gridcoo.second*4));
		}
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				// check right
				if (x < w - 1) {
					g->addEdge({gridCooToNumber(x,y), gridCooToNumber(x+1,y)});
				}
				// check above
				if (y < h - 1) {
					g->addEdge({gridCooToNumber(x,y), gridCooToNumber(x,y+1)});
				}
			}
		}
	}
};

int main() {
    string type;
	GraphGenerator* gen;

	while (cin >> type) {
		/**
		 * >> grids <w1> <h1> <w2> <h2> <perms> 
		 * w1 h1 w2 h2 [4x number]: range for grid dimensions
		 * perms [number]: number of different permutations for each grid, one default permutation if perms=0
		 */ 
		if (type.compare("grids") == 0) {
			int startw, endw, starth, endh, perms;
			bool coordinates;
			cin >> starth >> startw >> endh >> endw >> perms;
			for (int w = startw; w <= endw; w++) {
				for (int h = starth; h <= endh; h++) {
					if (perms == 0) {
						gen = (GraphGenerator*) new GridGenerator(h, w, false);
						gen->generate();
					} else {
						gen = (GraphGenerator*) new GridGenerator(h, w, true);
						for (int i = 0; i < perms; i++) {
							gen->generate();
						}
					}
				}
			}
		}
	}
}

