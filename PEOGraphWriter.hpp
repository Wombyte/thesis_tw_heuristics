#include "Graph.hpp"
#include "TwHeuristicGraphWriter.hpp"
#include "TwStorage.hpp"

using namespace std;

#ifndef PEO_GRAPH_WRITER_H
#define PEO_GRAPH_WRITER_H

extern const int NONE;

class PEOGraphWriter : public TwHeuristicGraphWriter {
    private:
    Node curNode;

    protected:
    string write(Graph<TwStorage>* g) {
        return " " + to_string(this->curNode);
    }

    public:
    PEOGraphWriter() {}

    void prepare(Node n, Graph<TwStorage>* graph) {
        this->curNode = n;
    }

    void clear() {}

    string before() const {
        return "PEO:";
    }

    string after() const {
        return "";
    }
};

#endif