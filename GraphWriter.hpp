#include "Graph.hpp"

using namespace std;

#ifndef GRAPH_WRITER_H
#define GRAPH_WRITER_H

template <typename T>
class GraphWriter {
    private:
    string str;

    protected:
    virtual string write(Graph<T>* g) = 0;
    virtual void clear() = 0;

    public:
    virtual string before() const = 0;
    virtual string after() const = 0;

    void add(Graph<T>* g) {
        str += write(g);
    }

    void print() {
        cout << this->before();
        cout << this->str;
        cout << this->after();
        cout << endl;
    }

    void reset() {
        this->str = "";
        this->clear();
    }
};

#endif