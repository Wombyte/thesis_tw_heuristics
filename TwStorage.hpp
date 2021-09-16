#include <vector>

using namespace std;

#ifndef TW_STOARGE_H
#define TW_STOARGE_H

typedef int Node;
typedef pair<Node,Node> Edge;

class TwStorage {
    public:
    pair<int,int> coordinates;
    int degree;
    vector<Edge> edgesToFillIn;
    int peoPos;

    void setDegree(int degree) { this->degree = degree; }
    void setEdgesToFillIn(vector<Edge> edges) { this->edgesToFillIn = edges; }
    void setPeoPos(int peoPos) { this->peoPos = peoPos; }

    int getFillIn() { return this->edgesToFillIn.size(); }
    int getDegree() { return this->degree; }
};

#endif