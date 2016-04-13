#include "Graph.h"

//List

Graph::Graph()
{
    this->weighted = 0;
    this->directed = 0;

    this->vertex_count = 0;
    this->edge_count = 0;
}

Graph::~Graph()
{
    //dtor
}

void Graph::set_directed(bool directed) {
    this->directed = directed;
}

bool Graph::is_directed() {
    return directed;
}

void Graph::set_weighted(bool weighted) {
    this->weighted = weighted;
}

bool Graph::is_weighted() {
    return weighted;
}
