#include "Graph.hpp"
#include "TwHeuristicGraphWriter.hpp"
#include "TwStorage.hpp"

using namespace std;

#ifndef IPE_GRAPH_WRITER_H
#define IPE_GRAPH_WRITER_H

extern const int NONE;

class IpeGraphWriter : public TwHeuristicGraphWriter {
    private:
    int horSpace;
    int vertSpace;

    int graphWidth;
    int graphHeight;
    int graphsPerColumn;

    int xoffset;
    int yoffset;
    int count;

    const int IPE_HEIGHT = 800;

    protected:
    string write(Graph<TwStorage>* g) {
        string str = "";

        int nodes = g->getNodeAmount();
        pair<int,int> coo;
        for (int i = 0; i < nodes; i++) {
            if (g->getNodeStorageOf(i)->peoPos != NONE) continue;
            coo = g->getNodeStorageOf(i)->coordinates;
            str += "<use layer=\"alpha\" name=\"mark/circle(sx)\"";
            str += "pos=\"" + to_string(coo.first + this->xoffset) + " " + to_string(coo.second + this->yoffset) + "\"";
            str += " size=\"tiny\" stroke=\"black\"/>";
        }

        vector<Edge> edges;
        g->getAllEdges(&edges);
        int m = edges.size();
        pair<int,int> acoo, bcoo;
        for (Edge e : edges) {
            if (g->getNodeStorageOf(e.first)->peoPos != NONE || g->getNodeStorageOf(e.second)->peoPos != NONE) continue;
            acoo = g->getNodeStorageOf(e.first)->coordinates;
            bcoo = g->getNodeStorageOf(e.second)->coordinates;
            str += "<path layer=\"alpha\" stroke=\"black\" stroke-opacity=\"30%\">";
            str += to_string(acoo.first + this->xoffset) + " " + to_string(acoo.second + this->yoffset) + " m ";
            str += to_string(bcoo.first + this->xoffset) + " " + to_string(bcoo.second + this->yoffset) + " l";
            str += "</path>";
        }

        return str;
    }

    public:
    void prepare(Node n, Graph<TwStorage>* graph) {
        this->xoffset = (this->graphWidth + this->horSpace) * (this->count / this->graphsPerColumn);
        this->yoffset = IPE_HEIGHT - (this->graphHeight + this->vertSpace) * (this->count % this->graphsPerColumn);
        this->count++;
    }

    IpeGraphWriter() {}
    IpeGraphWriter(int horSpace, int vertSpace) {
        this->horSpace = horSpace;
        this->vertSpace = vertSpace;

        this->clear();
    }

    void clear() {
        this->count = 0;
        this->xoffset = 0;
        this->yoffset = 0;
    }

    void init(Graph<TwStorage>* g) {
        int maxX = 0;
        int maxY = 0;
        int n = g->getNodeAmount();
        for (int i = 0; i < n; i++) {
            maxX = max(maxX, g->getNodeStorageOf(i)->coordinates.first);
            maxY = max(maxY, g->getNodeStorageOf(i)->coordinates.second);
        }
        this->graphWidth = maxX;
        this->graphHeight = maxY;

        this->graphsPerColumn = 800 / (this->graphHeight + this->vertSpace);
    }

    string before() const {
        return "Ipe: <ipeselection pos=\"0 0\">";
    }

    string after() const {
        return "</ipeselection>";
    }
};

#endif