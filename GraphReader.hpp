#include "Graph.hpp"

using namespace std;

#ifndef GRAPH_READER_H
#define GRAPH_READER_H

template <typename T>
class GraphReader {
    protected:
    virtual void read(Graph<T>* g) = 0;

    public:
    bool next(Graph<T>* g) {
        g->clear();
        this->read(g);
        return g->getNodeAmount() != 0;
    }
};

#endif