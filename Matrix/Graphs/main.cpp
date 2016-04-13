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
    graph.insert_edge("C", "B", 5);
    graph.insert_edge("D", "B", 5);
    graph.insert_edge("E", "B", 5);
    graph.insert_edge("F", "B", 5);

    cout << graph.to_string();

    cout << graph.is_connected("A");
    cout << graph.is_connected();
}
