#include "TwHeuristic.hpp"

using namespace std;

#ifndef MIN_FILLIN_H
#define MIN_FILLIN_H

class MinFillIn : public Heuristic {
    public:
    int metric(Node n, Graph<TwStorage>* graph) const {
        return graph->getNodeStorageOf(n)->getFillIn();
    }
};

#endif