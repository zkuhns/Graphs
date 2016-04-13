#include "Vertex.h"

Vertex::Vertex(std::string id) {
    this->id = id;
    this->edge_count = 0;
}

Vertex::~Vertex() {

}

int Vertex::getEdgeIndex(std::string id) {
    int low = 0;
    int mid = 0;
    int high = edge_count - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if (edges[mid]->id.compare(id) == 0) {
            return mid;
        } else if (edges[mid]->id.compare(id) < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

int Vertex::getInsertIndex(std::string id) {
    if (edge_count == 0) {
        return 0;
    }

    int low = 0;
    int mid = 0;
    int high = edge_count - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if (edges[mid]->id.compare(id) < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (id.compare(edges[mid]->id) < 0) {
        mid--;
    }

    if (mid < 0) {
        mid = 0;
    }

    if (id.compare(edges[mid]->id) > 0) {
        mid++;
    }

    return mid;
}

float Vertex::getEdgeWeight(Vertex* pointer) {
    int index = getEdgeIndex(pointer->id);

    if (index > -1) {
        return weights[index];
    }

    return -1;
}

bool Vertex::hasEdge(Vertex* pointer) {
    if (getEdgeIndex(pointer->id) > -1) {
        return true;
    }

    return false;
}

bool Vertex::addEdge(Vertex* pointer) {
    int insert_index = getInsertIndex(pointer->id);

    edges.push_back(0);
    weights.push_back(0);
    edge_count++;

    for (int i = edge_count-1; i > insert_index; i--) {
        edges[i] = edges[i-1];
    }

    edges[insert_index] = pointer;

    return true;
}

bool Vertex::addEdge(Vertex* pointer, float weight) {
    int insert_index = getInsertIndex(pointer->id);

    edges.push_back(0);
    weights.push_back(-1);
    edge_count++;

    for (int i = edge_count-1; i > insert_index; i--) {
        edges[i] = edges[i-1];
        weights[i] = weights[i-1];
    }

    edges[insert_index] = pointer;
    weights[insert_index] = weight;

    return true;
}

bool Vertex::deleteEdge(Vertex* pointer) {
    int delete_index = getEdgeIndex(pointer->id);

    edges.erase(edges.begin() + delete_index);
    weights.erase(weights.begin() + delete_index);
    edge_count--;

    return true;
}

void Vertex::printVertex() {
    std::cout << id << "," << edge_count <<":";

    for (int i = 0; i < edge_count; i++) {
        std::cout << edges[i]->id << " ";
    }

    std::cout << std::endl;
}
