#include "Graph.h"

Graph::Graph() {
    directed = false;
    weighted = true;

    edge_count = 0;
    vertex_count = 0;
}

Graph::~Graph() {

}

/* Getter for the directed variable */
bool Graph::isDirected() {
    return directed;
}

/* Getter for the weighted variable */
bool Graph::isWeighted() {
    return weighted;
}

/* Setter for the directed variable */
void Graph::setDirected(bool directed) {
    this->directed = directed;
}

/* Setter for the weighted variable */
void Graph::setWeighted(bool weighted) {
    this->weighted = weighted;
}

bool Graph::hasVertex(std::string name_one) {
    if (vertexIndex(name_one) == -1) {
        return false;
    }

    return true;
}

bool Graph::addVertex(std::string name_one) {
    if (hasVertex(name_one)) {
        return false;
    }

    int insert = insertIndex(name_one);

    for (int i = 0; i < vertex_count; i++) {
        weights[i].push_back(-1);
        for (int j = vertex_count-1; j > insert; j--) {
            weights[i][j] = weights[i][j-1];
        }
        weights[i][insert] = -1;
    }

    vertices.push_back(std::string());
    weights.push_back(std::vector< float >());
    vertex_count++;

    for (int i = vertex_count-1; i > insert; i--) {
        vertices[i] = vertices[i-1];
        weights[i] = weights[i-1];
    }

    vertices[insert] = name_one;
    weights[insert] = std::vector< float >();

    for (int i = 0; i < vertex_count; i++) {
        weights[insert].push_back(-1);
    }

    std::cout << "true" << std::endl;

    return true;
}

bool Graph::deleteVertex(std::string name_one) {
    int index = vertexIndex(name_one);

    if (index == -1) {
        return false;
    }

    for (int i = 0; i < vertex_count; i++) {
        if (weights[index][i] > -1) {
            edge_count--;
        }

        if (weights[i][index] > -1) {
            edge_count--;
        }

        weights[i].erase(weights[i].begin() + index);
    }

    weights.erase(weights.begin() + index);
    vertices.erase(vertices.begin() + index);
    vertex_count--;

    return true;
}

bool Graph::hasEdge(std::string name_one, std::string name_two) {
    int index_one = vertexIndex(name_one);

    if (index_one == -1) {
        return false;
    }

    int index_two = vertexIndex(name_two);

    if (index_two == -1) {
        return false;
    }

    if (weights[index_one][index_two] >= 0) {
        return true;
    }

    return false;
}

bool Graph::addEdge(std::string name_one, std::string name_two, float weight) {
    int index_one = vertexIndex(name_one);

    if (index_one == -1) {
        return false;
    }

    int index_two = vertexIndex(name_two);

    if (index_two == -1) {
        return false;
    }

    if (directed) {
        if (weights[index_one][index_two] >= 0) {
            return false;
        }

        weights[index_one][index_two] = weight;
        edge_count++;
    } else {
        if (weights[index_one][index_two] >= 0) {
            return false;
        }

        if (weights[index_two][index_one] >= 0) {
            return false;
        }

        weights[index_one][index_two] = weight;
        edge_count++;
        weights[index_two][index_one] = weight;
        edge_count++;
    }

    return true;
}

bool Graph::deleteEdge(std::string name_one, std::string name_two) {
    int index_one = vertexIndex(name_one);

    if (index_one == -1) {
        return false;
    }

    int index_two = vertexIndex(name_two);

    if (index_two == -1) {
        return false;
    }

    if (directed) {
        if (weights[index_one][index_two] == -1) {
            return false;
        }

        weights[index_one][index_two] = -1;
        edge_count--;
    } else {
        if (weights[index_one][index_two] == -1) {
            return false;
        }

        if (weights[index_two][index_one] == -1) {
            return false;
        }

        weights[index_one][index_two] = -1;
        edge_count--;
        weights[index_two][index_one] = -1;
        edge_count--;
    }

    return true;
}

bool Graph::isFullyConnected() {
    if (edge_count == (vertex_count * (vertex_count + 1) / 2)) {
        return true;
    }

    return false;
}

bool Graph::isFullyDisconnected() {
    if (edge_count == 0) {
        return true;
    }

    return false;
}

bool Graph::isConnected() {

}

void Graph::printGraph() {
    for (int i = 0; i < vertex_count; i++) {
        std::cout << vertices[i] << " ";
        for (int j = 0; j < vertex_count; j++) {
            std::cout << "|" << vertices[j] << " " << weights[i][j] << "|";
        }
        std::cout << std::endl;
    }

    std::cout << "Edge Count: " << edge_count << std::endl;
    std::cout << "Vertex Count: " << vertex_count << std::endl;
}

int Graph::vertexIndex(std::string name_one) {
    int low = 0;
    int mid;
    int high = vertex_count-1;

    while (low <= high) {
        mid = (low + high) / 2;

        if (vertices[mid].compare(name_one) == 0) {
            return mid;
        }

        if (vertices[mid].compare(name_one) < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

int Graph::insertIndex(std::string name_one) {
    if (vertex_count == 0) {
        std::cout << 0 << std::endl;
        return 0;
    }

    int low = 0;
    int mid;
    int high = vertex_count-1;

    while (low <= high) {
        mid = (low + high) / 2;

        if (vertices[mid].compare(name_one) < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (name_one.compare(vertices[mid]) < 0) {
        mid--;
    }

    if (mid < 0) {
        mid = 0;
    }

    if (name_one.compare(vertices[mid]) > 0) {
        mid++;
    }

    std::cout << mid << std::endl;

    return mid;
}
