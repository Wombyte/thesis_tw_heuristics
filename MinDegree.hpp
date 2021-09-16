#include "TwHeuristic.hpp"

using namespace std;

#ifndef MIN_DEGREE_H
#define MIN_DEGREE_H

class MinDegree : public Heuristic {
    public:
    int metric(Node n, Graph<TwStorage>* graph) const {
        return graph->getNodeStorageOf(n)->getDegree();
    }
};

#endif