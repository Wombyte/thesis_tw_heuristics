#include "Graph.hpp"
#include "GraphWriter.hpp"
#include "TwStorage.hpp"

using namespace std;

#ifndef TW_HEURISTIC_GRAPH_WRITER_H
#define TW_HEURISTIC_GRAPH_WRITER_H

class TwHeuristicGraphWriter : public GraphWriter<TwStorage> {
    public:
    virtual void prepare(Node n, Graph<TwStorage>* graph) = 0;
};

#endif