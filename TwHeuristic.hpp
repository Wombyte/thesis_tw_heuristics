#include "Graph.hpp"
#include "TwStorage.hpp"

#pragma once

using namespace std;

class Heuristic {
    public:
    virtual int metric(Node n, Graph<TwStorage>* g) const = 0;
};