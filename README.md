# Implementierung der MinDegree- und MinFillIn-Heuristik für meine Bachelorarbeit
Das Konzept der Baumweite spielt in vielen Bereichen, wie der parametrisierten Algorithmik und der Graphentheorie, eine wichtige Rolle. Es ist zwar für viele Anwendungen notwendig, die Baumweite eines Graphen zu bestimmen, allerdings ist das Problem für allgemeine Graphen NP-schwer. Um die Baumweite eines Graphens wenigstens zu approximieren, wurde verschiedenste Heuristiken entwickelt. In meiner Bachelorarbeit haben ich mich mit der MinDegree- und der MinFillIn-Heuristik beschäftigt, die u.a. von Bodlaender und Koster [\[BK10\]](#inhaltsverzeichnis) vorgstellt wurden. Im Folgenden erkläre ich kurz, wie der Code dazu benutzt werden kann.

## Übersicht über die Klassen
- [`HeuristicExecuter.hpp`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/HeuristicExecuter.hpp): enthält die grundlegenden Ablauf der Heuristiken
- [`MinDegree.hpp`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/MinDegree.hpp) / [`MinFillIn.hpp`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/MinFillIn.hpp): enthalten die Regeln, nach denen [`HeuristicExecuter.hpp`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/HeuristicExecuter.hpp) den nächsten Knoten ausgewählt
- [`TwGraphReader.hpp`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/TwGraphReader.hpp): liest die Graphen aus dem Input ein
- [`TwHeuristicGraphWriter.hpp`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/TwHeuristicGraphWriter.hpp): Oberklasse für Writer, die Ergebnisse aus der Heuristik ausgeben
  - [`IpeGraphWriter.hpp`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/IpeGraphWriter.hpp): gibt die Eliminations-Graphen im Ipe-Format aus
  - [`PEOGraphWriter.hpp`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/IpeGraphWriter.hpp): gibt das Eliminationsschema aus
- [`main.cpp`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/main.cpp): enthält einen Beispielablauf
- [`GraphGenerator.cpp`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/GraphGenerator.cpp): erzeugt Gitter beliebiger Größe und Knotennummerierung

&nbsp;
### Grundlagen
Grundlegend soll die [`main.cpp`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/main.cpp) dafür verwendet werden, eine der beiden Heuristiken auf einen oder mehrere Input-Graphen anzuwenden, und das Ergebnis mit Hilfe der [`TwHeuristicGraphWriter.hpp`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/TwHeuristicGraphWriter.hpp) ausgeben. Die Graphen sollten dazu im Folgenden Format angegeben sein: 
```
<Anzahl Knoten> <Anzahl Kanten>
<KnotenID> <x-Koordinate> <y-Koordinate>
...
<KnotenID> <x-Koordinate> <y-Koordinate>
<StartknotenID-Kante-1> <EndknotenID-Kante-1>
...
<StartknotenID-Kante-m> <EndknotenID-Kante-m>
```
Die [`main.cpp`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/main.cpp)-Datei ist dafür ausgelegt mehrere Graphen hintereinander auszuwerten. Dazu können die Graphen hintereinander in eine Datei (z.b. [`graph.txt`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/graph.txt)) geschrieben werden, die dann [`main.cpp`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/main.cpp)-Datei bei der Ausführung als Input mitgegeben wird. 

&nbsp;
### Ablauf in [`main.cpp`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/main.cpp)
```cpp
int main() {
    TwGraphReader reader;
    HeuristicExecutor hex (new MinDegree);
    IpeGraphWriter ipeWriter {12, 8};
    PEOGraphWriter peoWriter;
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
```
Der grundlegende Ablauf der Heuristiken ist in der Klasse [`HeuristicExecuter`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/HeuristicExecuter.hpp) festgelegt. Im Konstruktor der Klasse muss festgelegt werden, nach welchem Maß die zu eliminierenden Knoten ausgewählt werden sollen. Dort kann entweder eine Instanz der Klasse [`MinDegree`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/MinDegree.hpp) oder ein Instanz der Klasse [`MinFillIn`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/MinFillIn.hpp) übergeben werden, um die jeweilige Heuristik auszuwählen. In diesem Beispiel soll die MinDegree-Heuristik verwendet werden. 

Vor der `while`-Schleife werden all nötigen Objekte initialisiert und deklariert. Am Anfang wird ein [`TwGraphReader`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/TwGraphReader.hpp)-Objkt bereitgestellt, mit dem später die Graphen aus dem Input gelesen werden und in die [`Graph`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/Graph.hpp)-Struktur gespeichert werden. Danach wird ein Objekt der Klasse [`HeuristicExecuter`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/HeuristicExecuter.hpp) erstellt, das mit der MinDegree-Heuristik arbeiten soll. Danach werden die Writer initialisiert, die später die Ergebnisse des [`HeuristicExecuter`s](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/HeuristicExecuter.hpp) ausgeben. Der [`IpeGraphWriter`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/IpeGraphWriter.hpp) erstellt XML-Code der 1:1 in Ipe kopiert werden kann. Dort werden dann alle Eliminations-Graphen so dargestellt, dass sie auf eine ausreichend breite Ipe-Page passen (Standardhöhe: 800px). Die Werte, die im Konstruktor übergeben werden, geben an, wie viele Pixel horizontal (12) und vertical (8) zwischen zwei Eliminationsgraphen in Ipe liegen sollen. Der [`PEOGraphWriter`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/IpeGraphWriter.hpp) (PEO = perfect elimination ordering) gibt die Reihenfolge aus, mit der die Heuristik die Knoten des INput-Graphens eliminiert hat.

Mit dem Anfang der `while`-Schleife wird ein [`Graph`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/Graph.hpp)-Objekt angelegt, in die der aktuelle Graph aus dem Input vom [`TwGraphReader`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/TwGraphReader.hpp) eingespeichert wird. Dieses [`Graph`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/Graph.hpp)-Objekt wird dann in der `while`-Schleife durch den [`HeuristicExecuter`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/HeuristicExecuter.hpp) bearbeitet. Zunächst werden allerdings die Writer des [`HeuristicExecuter`s](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/HeuristicExecuter.hpp) resetet, und der [`PEOGraphWriter`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/IpeGraphWriter.hpp) bekommt gesagt, wie groß der aktuelle Input-Graph ist. Anschließend wird die ausgewähle Heuristik gestartet, und die Ergebnisse der angemeldeten Writer ausgegeben.

Der Beispielgraph, der in meiner Bachelorarbeit durch die MinDegree-Heuristik abgearbeitet wird, ist in der Datei [`graph.txt`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/graph.txt) angegeben. Die dazu passende Ausgabe, die diese [`main.cpp`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/main.cpp)-Datei daraus macht, ist in der Datei [`out.txt`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/out.txt) zu sehen.

&nbsp;
### Erzeugen der Gitter 
Um Gitter beliebiger Größe und Knotennummerierung zu erzeugen, kann die Klasse [`GraphGenerator.cpp`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/GraphGenerator.cpp) verwendet werden. Der notwendige Input für diese Datei sieht wie folgt aus:
```
grids <h1> <w1> <h2> <w2> <Anzahl-Permutationen>
```
Dabei sind alle Parameter als Integer anzugeben. Dieser Input erzeugt für alle h aus dem Interval \[`<h1>`;`<h2>`\] und alle w aus dem Intervall \[`<w1>`;`<w2>`\] genau `<Anzahl-Permutationen>` Gitter mit Höhe h, Breite w und zufälliger Knotennummerierung. Ist `<Anzahl-Permutationen>` auf `0` gesetzt, dann werden für jedes Gitter die Knoten von links nach rechts und von oben nach unten durchweg nummeriert. Die Ausgabe erfolgt in dem oben vorgstellten Format, das vom [`TwGraphReader`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/TwGraphReader.hpp) gelesen werden kann.

&nbsp;&nbsp;
## Mögliche Erweiterungen
- andere Input-Formate: Dazu muss eine neue Klasse erstellt werden, die von [`GraphReader<TwStorage>`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/GraphReader.hpp) erbt. Um entsprechende Graphen zu generieren, kann ebenso eine neue Klasse erstellt werden, die von [`GraphWriter`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/GraphWriter.hpp) erbt. Diese müsste dann in die Klasse [`GraphGenerator.cpp`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/GraphGenerator.cpp) eingebunden werden.
- andere Input-Graphen generieren: Dazu muss von der Klasse [`GraphGenerator`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/GraphGenerator.cpp) geerbt werden. Eine Beispiel-Implementierung ist der [`GridGenerator`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/GraphGenerator.cpp).
- neue Ergebnis-Writer: Dazu muss von der Klasse [`TwHeuristicGraphWriter`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/TwHeuristicGraphWriter.hpp) geerbt werden. Ein Objekt dieser Klasse muss dann in [`main.cpp`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/main.cpp) beim [`HeuristicExecuter`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/HeuristicExecuter.hpp) angemeldet werden.
- andere Heuristiken: solange das Grundprinzip der Heuristiken gleich bleibt, reicht es aus von der Klasse [`Heuristic`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/TwHeuristic.hpp) zu erben. Beispiel-Implementierungen sind die [`MinDegree`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/MinDegree.hpp)- und die [`MinFillIn`](https://github.com/Wombyte/thesis_tw_heuristics/blob/main/MinFillIn.hpp)-Klasse.

&nbsp;&nbsp;
---
## Inhaltsverzeichnis
- __\[BK10\]:__ Hans L. Bodlaender and Arie M. C. A. Koster. Treewidth computations i. upper bounds. _Information and Computation_ , 208(3):259–275, 2010.

