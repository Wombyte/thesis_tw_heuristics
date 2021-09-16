#include <vector>
#include "IndexedList.hpp"
#include "TwHeuristic.hpp"
#include "TwHeuristicGraphWriter.hpp"
#include "Graph.hpp"
#include "TwStorage.hpp"

using namespace std;

#ifndef HEURISTIC_EXECUTER_H
#define HEURISTIC_EXECUTER_H

extern const int NONE;

class HeuristicExecutor {
    private:
    Heuristic* heu;
    vector<TwHeuristicGraphWriter*> writers;
    int result;

    vector<Node> getRemainingNeighbors(Node node, Graph<TwStorage>* graph) {
        vector<Node> remainingNeighbors;
        for (Node n : *(graph->getNeighborhoodOf(node))) {
            if (graph->getNodeStorageOf(n)->peoPos == NONE) {
                remainingNeighbors.push_back(n);
            }   
        }
        return remainingNeighbors;
    }

    vector<Edge> getEdgesToFillIn(Node node, Graph<TwStorage>* graph) {
        vector<Edge> missingEdges;
        if (graph->getNodeStorageOf(node)->peoPos != NONE) {
            return missingEdges;
        }

        vector<int> remainingNeighbors = this->getRemainingNeighbors(node, graph);
        int from, to;
        for (int fromid = 0; fromid < remainingNeighbors.size(); fromid++) {
            from = remainingNeighbors[fromid];
            vector<int>* fromadjlist = graph->getNeighborhoodOf(from);

            for (int toid = fromid+1; toid < remainingNeighbors.size(); toid++) {
                to = remainingNeighbors[toid];

                if (from == to) continue;
                if (find(fromadjlist->begin(), fromadjlist->end(), to) != fromadjlist->end()) continue;

                missingEdges.push_back({from,to});
            }
        }
        
        return missingEdges;
    }

    public:
    HeuristicExecutor(Heuristic* heu) {
        this->heu = heu;
    }

    int run(Graph<TwStorage>* graph) {
        // init
        int nodes = graph->getNodeAmount();
        for (int i = 0; i < nodes; i++) {
            graph->getNodeStorageOf(i)->setPeoPos(NONE);
        }

        for (int i = 0; i < nodes; i++) {
            graph->getNodeStorageOf(i)->setDegree(graph->getNeighborhoodOf(i)->size());
            graph->getNodeStorageOf(i)->setEdgesToFillIn(this->getEdgesToFillIn(i,graph));
        }

        vector<int> metricValueVec (nodes);
        for (int i = 0; i < nodes; i++) {
            metricValueVec[i] = this->heu->metric(i, graph);
        }
        IndexedList metricValue (&metricValueVec);

        int maxNeighbors = 0;
        for (int i = 0; i < nodes; i++) {
            // selection
            metricValue.sort(i, nodes);
            int curNode = metricValue.getIndexAtPos(i);

            // update result
            int curNeighbors = this->getRemainingNeighbors(curNode, graph).size();
            maxNeighbors = max(maxNeighbors, curNeighbors);

            // writers
            for (TwHeuristicGraphWriter* w : this->writers) {
                w->prepare(curNode, graph);
                w->add(graph);
            }

            // elimination
            for (Edge e : graph->getNodeStorageOf(curNode)->edgesToFillIn) {
                graph->addEdge(e);
            }
            graph->getNodeStorageOf(curNode)->setPeoPos(i);

            // update node storages
            vector<Node> changedNodes = *graph->getNeighborhoodOf(curNode);
            for (Node n : changedNodes) {
                if (graph->getNodeStorageOf(n)->peoPos != NONE) continue;
                graph->getNodeStorageOf(n)->setDegree(this->getRemainingNeighbors(n, graph).size());
            }
            vector<Node> changedNodesNeighborhood = graph->getkNeighborhood(&changedNodes, 1);
            for (Node nn : changedNodesNeighborhood) {
                if (graph->getNodeStorageOf(nn)->peoPos != NONE) continue;
                graph->getNodeStorageOf(nn)->setEdgesToFillIn(this->getEdgesToFillIn(nn, graph));
                metricValue.setAtIndex(nn, this->heu->metric(nn, graph));
            }

        }

        this->result = maxNeighbors;

        return maxNeighbors;
    }

    void addWriter(TwHeuristicGraphWriter* w) {
        writers.push_back(w);
    }

    void resetAllWriters() {
        for (TwHeuristicGraphWriter* w : this->writers) {
            w->reset();
        }
    }

    void printResult() {
        cout << "treewidth: " << this->result << endl;
        for (TwHeuristicGraphWriter* w : writers) {
            w->print();
        }
        cout << endl;
    }

};

#endif