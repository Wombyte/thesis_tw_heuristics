#include "Graph.hpp"
#include "GraphWriter.hpp"

using namespace std;

#ifndef COORDINATES_GRAPH_WRITER_H
#define COORDINATES_GRAPH_WRITER_H

class CoordinatesGraphWriter : public GraphWriter<pair<int,int>> {
    private:
    bool perm;

    protected:
    string write(Graph<pair<int,int>>* g) {
        string str = "";

        int n = g->getNodeAmount();
		vector<int> ordering (n);

		for (int i = 0; i < n; i++) {
			ordering[i] = i;
		}
		if (this->perm) {
			std::random_device random_device;
			std::mt19937 random_engine(random_device());
			std::uniform_int_distribution<int> distribution(1, 100000);
			unsigned seed = distribution(random_device);
    		shuffle(ordering.begin(), ordering.end(), std::default_random_engine(seed));
			reverse(ordering.begin(), ordering.end());
		}

		vector<Edge> edges;
		g->getAllEdges(&edges);
		int m = edges.size();

        str += to_string(n) + " " + to_string(m) + "\n";
		pair<int,int>* coo;
		for (int i = 0; i < n; i++) {
			coo = g->getNodeStorageOf(i);
			str += to_string(ordering[i]) + " " + to_string(coo->first) + " " + to_string(coo->second) + "\n";
		}
		for (Edge e : edges) {
			str += to_string(ordering[e.first]) + " " + to_string(ordering[e.second]) + "\n";
		}
		str += "\n";

        return str;
    }

    void clear() {}

    public:
    CoordinatesGraphWriter() {}
    CoordinatesGraphWriter(bool perm) {
        this->perm = perm;
    }

    string before() const {
        return "";
    }

    string after() const {
        return "";
    }

    void setPerm(bool perm) {
        this->perm = perm;
    }

    bool getPerm() {
        return this->perm;
    }
};

#endif