#include "Graph.h"

#include <iostream>

Graph::Graph() {
    weighted = 1;
    directed = 0;

    vertex_count = 0;
    edge_count = 0;

    vertices.push_back("A");
    vertices.push_back("C");
    vertices.push_back("E");
    vertices.push_back("G");

    vertex_count = 4;

    std::cout << get_insert_vertex_index("B");
    std::cout << get_insert_vertex_index("D");
    std::cout << get_insert_vertex_index("F");
    std::cout << get_insert_vertex_index("H");
}

Graph::~Graph() {

}

bool Graph::has_vertex(std::string vertex_one) {
    if (get_vertex_index(vertex_one)) {
        return true;
    }
    return false;
}

bool Graph::insert_vertex(std::string vertex_one) {


    return false;
}

bool Graph::remove_vertex(std::string vertex_one) {


    return false;
}

int Graph::get_vertex_index(std::string vertex_one) {
    int min = 0;
    int mid;
    int max = vertex_count-1;

    while (min <= max) {
        mid = (min + max) / 2;

        if (vertex_one.compare(vertices[mid]) == 0) {
            return mid;
        }

        if (vertex_one.compare(vertices[mid]) < 0) {
            max = mid - 1;
        } else {
            min = mid + 1;
        }
    }

    return -1;
}

int Graph::get_insert_vertex_index(std::string vertex_one) {
    if (vertex_count == 0) {
        return 0;
    }

    int min = 0;
    int mid;
    int max = vertex_count-1;

    while (min <= max) {
        mid = (min + max) / 2;

        if (vertex_one.compare(vertices[mid]) == 0) {
            return -1;
        }

        if (vertex_one.compare(vertices[mid]) < 0) {
            max = mid - 1;
        } else {
            min = mid + 1;
        }
    }

    if (mid == 0) {
        if (vertex_one.compare(vertices[mid]) >= 0) {
            mid++;
        }
    } else {
        if (vertex_one.compare(vertices[mid]) > 0) {
            mid++;
        }
    }

    return mid;
}
