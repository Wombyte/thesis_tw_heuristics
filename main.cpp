#include "HeuristicExecuter.hpp"
#include "TwHeuristic.hpp"
#include "MinFillIn.hpp"
#include "MinDegree.hpp"
#include "Graph.hpp"
#include "TwGraphReader.hpp"
#include "TwHeuristicGraphWriter.hpp"
#include "IpeGraphWriter.hpp"
#include "PEOGraphWriter.hpp"

typedef int Node; // index as Node
typedef pair<Node,Node> Edge; 
typedef vector<Node> PEO; // perfect elimination ordering

const int NONE = -1;

int main() {
    TwGraphReader reader;
    IpeGraphWriter ipeWriter {12, 8};
    PEOGraphWriter peoWriter;
    HeuristicExecutor hex (new MinDegree);
    hex.addWriter(&ipeWriter);
    hex.addWriter(&peoWriter);

    Graph<TwStorage> g;

    while (reader.next(&g)) {
        hex.resetAllWriters();
        ipeWriter.init(&g);

        int tw = hex.run(&g);
        hex.printResult();
    }
}