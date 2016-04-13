#include "Graph.h"

Graph::Graph() {
    this->weighted = true;
    this->directed = false;

    this->vertex_count = 0;
    this->edge_count = 0;
}

Graph::~Graph() {
    for (int i = 0; i < vertex_count; i++) {
        delete vertices[i];
    }
}

/* Setter for the weighted variable */
void Graph::setWeighted(bool weighted) {
    this->weighted = weighted;
}

/* Setter for the directed variable */
void Graph::setDirected(bool directed) {
    this->directed = directed;
}

/* Getter for the weighted variable */
bool Graph::isWeighted() {
    return weighted;
}

/* Getter for the directed variable */
bool Graph::isDirected() {
    return directed;
}

int Graph::getVertexIndex(std::string id) {
    int low = 0;
    int mid = 0;
    int high = vertex_count - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if (vertices[mid]->id.compare(id) == 0) {
            return mid;
        } else if (vertices[mid]->id.compare(id) < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

int Graph::getInsertIndex(std::string id) {
    if (vertex_count == 0) {
        return 0;
    }

    int low = 0;
    int mid = 0;
    int high = vertex_count - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        if (vertices[mid]->id.compare(id) < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (id.compare(vertices[mid]->id) < 0) {
        mid--;
    }

    if (mid < 0) {
        mid = 0;
    }

    if (id.compare(vertices[mid]->id) > 0) {
        mid++;
    }

    return mid;
}

bool Graph::hasVertex(std::string id) {
    if (getVertexIndex(id) > -1) {
        return true;
    }

    return false;
}

bool Graph::addVertex(std::string id) {
    if (hasVertex(id)) {
        return false;
    }

    int insert_index = getInsertIndex(id);

    vertices.push_back(0);
    vertex_count++;

    for (int i = vertex_count-1; i > insert_index; i--) {
        vertices[i] = vertices[i-1];
    }

    Vertex* new_vertex = new Vertex(id);
    vertices[insert_index] = new_vertex;

    return true;
}

bool Graph::deleteVertex(std::string id) {
    if (!hasVertex(id)) {
        return false;
    }

    int delete_index = getVertexIndex(id);

    for (int i = 0; i < vertex_count; i++) {
        if (vertices[i]->hasEdge(vertices[delete_index])) {
            vertices[i]->deleteEdge(vertices[delete_index]);
            edge_count--;
        }
    }

    edge_count -= vertices[delete_index]->edge_count;
    delete vertices[delete_index];
    vertices.erase(vertices.begin() + delete_index);
    vertex_count--;
}

float Graph::getEdgeWeight(std::string id_one, std::string id_two) {
    int index_one = getVertexIndex(id_one);
    int index_two = getVertexIndex(id_two);

    if (index_one == -1 || index_two == -1) {
        return false;
    }

    return vertices[index_one]->getEdgeWeight(vertices[index_two]);
}

bool Graph::hasEdge(std::string id_one, std::string id_two) {
    int index_one = getVertexIndex(id_one);
    int index_two = getVertexIndex(id_two);

    if (index_one == -1 || index_two == -1) {
        return false;
    }

    return vertices[index_one]->hasEdge(vertices[index_two]);
}

bool Graph::addEdge(std::string id_one, std::string id_two) {
    int index_one = getVertexIndex(id_one);
    int index_two = getVertexIndex(id_two);

    if (index_one == -1 || index_two == -1) {
        return false;
    }

    if (directed) {
        if (vertices[index_one]->hasEdge(vertices[index_two])) {
            return false;
        }

        edge_count++;
        vertices[index_one]->addEdge(vertices[index_two]);
    } else {
        if (vertices[index_one]->hasEdge(vertices[index_two])) {
            return false;
        }

        if (vertices[index_two]->hasEdge(vertices[index_one])) {
            return false;
        }

        edge_count+=2;
        vertices[index_one]->addEdge(vertices[index_two]);
        vertices[index_two]->addEdge(vertices[index_one]);
    }

    return true;
}

bool Graph::addEdge(std::string id_one, std::string id_two, float weight) {
    int index_one = getVertexIndex(id_one);
    int index_two = getVertexIndex(id_two);

    if (index_one == -1 || index_two == -1) {
        return false;
    }

    if (directed) {
        if (vertices[index_one]->hasEdge(vertices[index_two])) {
            return false;
        }

        edge_count++;
        vertices[index_one]->addEdge(vertices[index_two], weight);
    } else {
        if (vertices[index_one]->hasEdge(vertices[index_two])) {
            return false;
        }

        if (vertices[index_two]->hasEdge(vertices[index_one])) {
            return false;
        }

        edge_count+=2;
        vertices[index_one]->addEdge(vertices[index_two], weight);
        vertices[index_two]->addEdge(vertices[index_one], weight);
    }

    return true;
}

bool Graph::deleteEdge(std::string id_one, std::string id_two) {
    int index_one = getVertexIndex(id_one);
    int index_two = getVertexIndex(id_two);

    if (index_one == -1 || index_two == -1) {
        return false;
    }

    if (directed) {
        if (!vertices[index_one]->hasEdge(vertices[index_two])) {
            return false;
        }

        edge_count--;
        return vertices[index_one]->deleteEdge(vertices[index_two]);
    } else {
        if (!vertices[index_one]->hasEdge(vertices[index_two])) {
            return false;
        }

        if (!vertices[index_two]->hasEdge(vertices[index_one])) {
            return false;
        }

        edge_count-=2;
        vertices[index_one]->deleteEdge(vertices[index_two]);
        vertices[index_two]->deleteEdge(vertices[index_one]);
    }

    return true;
}

double Graph::getDensity() {
    int max_edges = vertex_count * (vertex_count - 1);

    return (double)edge_count / max_edges;
}

bool Graph::isSparse() {
    if (getDensity() < 0.15) {
        return true;
    }

    return false;
}

bool Graph::isDense() {
    if (getDensity() > 0.85) {
        return true;
    }

    return false;
}

/* Returns true if a vertex has a path to every other vertex */
bool Graph::isConnected(Vertex* pointer) {
    std::vector < Vertex* > disconnected = vertices;
    std::vector < Vertex* > connected;

    connected.push_back(disconnected[0]);
    disconnected.erase(disconnected.begin());

    for (int i = 0; i < disconnected.size(); i++) {
        for (int j = 0; j < connected.size(); j++) {
            if (connected[j]->hasEdge(disconnected[i])) {
                connected.push_back(disconnected[i]);
                disconnected.erase(disconnected.begin() + i);
                i--;
                break;
            }
        }
    }

    if (disconnected.size() > 0) {
        return false;
    }

    return true;
}

/* This function returns true if all vertices in our graph */
/* have a path to all other vertices in the graph. */
bool Graph::isConnected() {
    if (!isConnected(vertices[0])) {
        return false;
    }

    std::vector < Vertex* > disconnected = vertices;
    std::vector < Vertex* > connected;
    connected.push_back(disconnected[0]);
    disconnected.erase(disconnected.begin());

    for (int i = 0; i < disconnected.size(); i++) {
        for (int j = 0; j < connected.size(); j++) {
            if (disconnected[i]->hasEdge(connected[j])) {
                connected.push_back(disconnected[i]);
                disconnected.erase(disconnected.begin() + i);
                i--;
                break;
            }
        }
    }

    if (disconnected.size() > 0) {
        return false;
    }

    return true;
}

bool Graph::isFullyConnected() {
    if (edge_count < (vertex_count) * (vertex_count-1)) {
        return false;
    }

     return true;
}

bool Graph::isFullyDisconnected() {
    if (edge_count > 0) {
        return false;
    }

    return true;
}

bool Graph::isStar() {
    if (edge_count != (vertex_count-1)*2) {
        return false;
    }

    for (int i = 0; i < vertex_count; i++) {
        if (vertices[i]->edge_count != 1 && vertices[i]->edge_count != vertex_count-1) {
            return false;
        }
    }

    return true;
}

bool Graph::isRing() {
    if (edge_count != vertex_count*2) {
        return false;
    }

    for (int i = 0; i < vertex_count; i++) {
        if (vertices[i]->edge_count != 2) {
            return false;
        }
    }

    return true;
}

int Graph::clique(int num) {
    if (vertex_count < num) {
        return 0;
    }

    if (num < 2) {
        return 0;
    }

    int cliques = 0;

    for (int i = 0; i < vertex_count-num+1; i++) {
        if (vertices[i]->edge_count < num) {
            continue;
        }

        std::vector < Vertex* > current_clique;
        current_clique.push_back(vertices[i]);
        cliques += clique(num, 1, i+1, current_clique);
        current_clique.pop_back();
    }

    return cliques;
}

int Graph::clique(int num, int current_num, int index, std::vector < Vertex* > current_clique) {
    int cliques = 0;

    if (current_num == num) {
        for (int i = 0; i < current_clique.size(); i++) {
            for (int j = 0; j < current_clique.size(); j++) {
                if (i == j) {
                    continue;
                }

                if (!current_clique[i]->hasEdge(current_clique[j])) {
                    return 0;
                }
            }
        }

        for (int i = 0; i < current_clique.size(); i++) {
            std::cout << current_clique[i]->id;
        }
        std::cout << std::endl;

        return 1;
    }

    for (int i = index; i < vertex_count; i++) {
        if (vertices[i]->edge_count < num) {
            continue;
        }

        current_clique.push_back(vertices[i]);
        cliques += clique(num, current_num+1, i+1, current_clique);
        current_clique.pop_back();
    }

    return cliques;
}

int Graph::getShortestDistance(std::string vertex_one, std::string vertex_two) {
    if (!isWeighted()) {
        return 0;
    }

    int index_one = getVertexIndex(vertex_one);
    int index_two = getVertexIndex(vertex_two);

    if (index_one < 0 || index_two < 0) {
        return -1;
    }

    std::vector< Vertex* > remaining_vertices;
    std::vector< Vertex* > checked_vertices;
    std::vector< float > distances;
    //std::vector< Vertex > previous_vertices;

    for (int i = 0; i < vertex_count; i++) {
        remaining_vertices.push_back(vertices[i]);
    }

    for (int i = 0; i < vertex_count; i++) {
        distances.push_back(std::numeric_limits<float>::max());
    }
    distances[index_one] = 0;

    //for (int i = 0; i < vertex_count; i++) {
    //    previous_vertices.push_back(vertices[i]);
    //}

    while (remaining_vertices.size() > 0) {
        checked_vertices.push_back(remaining_vertices[0]);
        remaining_vertices.erase(remaining_vertices.begin());

        for (int i = 0; i < remaining_vertices.size(); i++) {
            float weight = getEdgeWeight(checked_vertices[checked_vertices.size()-1]->id, remaining_vertices[i]->id);

            if (weight < 0) {
                continue;
            }

            if ((distances[checked_vertices.size()-1] + weight) < distances[i + checked_vertices.size()]) {
                distances[i + checked_vertices.size()] = distances[checked_vertices.size()-1] + weight;
                //previous_vertices[i + checked_vertices.size()] = vertices[checked_vertices.size()-1];
            }
        }
    }

    if (distances[index_two] == std::numeric_limits<float>::max()) {
        return -1;
    } else {
        return distances[index_two];
    }
}

std::vector < Vertex* > Graph::getShortestPath(std::string vertex_one, std::string vertex_two) {
    if (!isWeighted()) {
        return vertices;
    }

    int index_one = getVertexIndex(vertex_one);
    int index_two = getVertexIndex(vertex_two);

    if (index_one < 0 || index_two < 0) {
        return std::vector < Vertex* >();
    }

    std::vector< Vertex* > remaining_vertices;
    std::vector< Vertex* > checked_vertices;
    std::vector< float > distances;
    std::vector< Vertex* > previous_vertices;

    for (int i = 0; i < vertex_count; i++) {
        remaining_vertices.push_back(vertices[i]);
    }

    for (int i = 0; i < vertex_count; i++) {
        distances.push_back(std::numeric_limits<float>::max());
    }
    distances[index_one] = 0;

    for (int i = 0; i < vertex_count; i++) {
        previous_vertices.push_back(vertices[i]);
    }

    while (remaining_vertices.size() > 0) {
        checked_vertices.push_back(remaining_vertices[0]);
        remaining_vertices.erase(remaining_vertices.begin());

        for (int i = 0; i < remaining_vertices.size(); i++) {
            float weight = getEdgeWeight(checked_vertices[checked_vertices.size()-1]->id, remaining_vertices[i]->id);

            if (weight < 0) {
                continue;
            }

            if ((distances[checked_vertices.size()-1] + weight) < distances[i + checked_vertices.size()]) {
                distances[i + checked_vertices.size()] = distances[checked_vertices.size()-1] + weight;
                previous_vertices[i + checked_vertices.size()] = vertices[checked_vertices.size()-1];
            }
        }
    }

    for (int i = 0; i < previous_vertices.size(); i++) {
        std::cout << "[" << vertices[i]->id << " ";
        std::cout << previous_vertices[i]->id << "] ";
    }
    std::cout << std::endl;

    if (distances[index_two] == std::numeric_limits<float>::max()) {
        return std::vector < Vertex* >();
    } else {
        return previous_vertices;
    }
}

int Graph::getMaxEdges() {
    int max_edges = 0;

    /*for (int i = 0; i < vertex_count; i++) {
        if (vertices[i]->edge_count > max_edges) {
            max_edges = vertices[i]->edge_count;
        }
    }*/

    for (int i = 0; i < vertex_count; i++) {
        int count = 0;
        for (int j = 0; j < vertex_count; j++) {
            if (vertices[i]->hasEdge(vertices[j])) {
                count++;
            }
        }

        if (count > max_edges) {
            max_edges = count;
        }
    }

    return max_edges;
}

void Graph::printGraph() {
    for (int i = 0; i < vertex_count; i++) {
        vertices[i]->printVertex();
    }

    std::cout << "Vertices: " << vertex_count << std::endl;
    std::cout << "Edges: " << edge_count << std::endl;
}
