#include <algorithm>
#include <set>
#include <queue>
#include <vector>
#include <random>
#include <chrono>
#include <iostream>
#include <string>

using namespace std;

#ifndef GRAPH_H
#define GRAPH_H

typedef int Node;
typedef pair<Node,Node> Edge; 

template <typename T>
class Graph {
    private:
    vector<T> nodeStorage;
    vector<vector<Node>> adj;

    public:
    Graph() {
        this->clear();
    }

    void clear() {
        this->adj = vector<vector<Node>> (0, vector<Node>());
        this->nodeStorage = vector<T> (0);
    }

    int addNode(T storage) {
        int index = this->getNodeAmount();
        this->adj.push_back(vector<Node>());
        this->nodeStorage.push_back(storage);
        return index;
    }

    void addEdge(Edge e) {
        Node a = e.first;
        Node b = e.second;
        this->adj[a].push_back(b);
        this->adj[b].push_back(a);
    }

    vector<Node>* getNeighborhoodOf(Node n) {
        return &(this->adj[n]);
    }

    vector<Node> getkNeighborhood(vector<Node>* nodes, int k) {
        set<Node> resultSet;
        queue<pair<Node,int>> q;  //nodeid, iteration
        
        for (Node n : *nodes) {
            q.push({n,0});
        }

        pair<Node,int> cur;
        while (!q.empty()) {
            cur = q.front();
            if (resultSet.find(cur.first) == resultSet.end()) {
                resultSet.insert(cur.first);
                if (cur.second < k) {
                    for (int nei : this->adj[cur.first]) {
                        q.push({nei,cur.second+1});
                    }
                }
            }
            q.pop();
        }

        return vector<Node> (resultSet.begin(), resultSet.end());
    }

    int getNodeAmount() {
        return this->adj.size();
    }

    void getAllEdges(vector<Edge>* edges) {
        int nodes = this->getNodeAmount();
        for (int a = 0; a < nodes; a++) {
            for (Node b : this->adj[a]) {
                if (a < b) {
                    edges->push_back({a,b});
                }
            }
        }
    }

    T* getNodeStorageOf(Node n) {
        return &this->nodeStorage[n];
    }

    void setNodeStorageOf(Node n, T content) {
        this->nodeStorage[n] = content;
    }
};

#endif