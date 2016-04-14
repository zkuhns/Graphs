#include <iostream>

#include <Graph.h>

using namespace std;

int main()
{
    Graph graph(true, false);

    graph.insert_vertex("A");
    graph.insert_vertex("C");
    graph.insert_vertex("B");
    graph.insert_vertex("D");

    graph.insert_edge("A", "B", 3);
    graph.insert_edge("A", "C", 4);
    graph.insert_edge("C", "D", 5);

    cout << graph.to_string();

    cout << graph.is_connected() << endl;
    return 0;
}
