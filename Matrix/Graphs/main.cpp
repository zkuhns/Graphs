#include <iostream>

#include <Graph.h>

using namespace std;

int main() {
    Graph graph(true, false);

    graph.insert_vertex("A");
    graph.insert_vertex("F");
    graph.insert_vertex("B");
    graph.insert_vertex("B");
    graph.insert_vertex("D");
    graph.insert_vertex("E");
    graph.insert_vertex("C");

    graph.insert_edge("A", "B", 5);
    graph.insert_edge("B", "C", 4);
    //graph.insert_edge("C", "D", 6);
    graph.insert_edge("B", "E", 1);
    graph.insert_edge("A", "F", 2);

    cout << graph.is_connected("A");

    cout << graph.to_string();
}
