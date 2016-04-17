#include "Graph.h"

Graph::Graph(bool weighted, bool directed) {
    this->weighted = weighted;
    this->directed = directed;

    vertex_count = 0;
    edge_count = 0;
}

Graph::~Graph() {

}

int Graph::get_vertex_count() {
    return vertex_count;
}

int Graph::get_edge_count() {
    if (directed) {
        return edge_count;
    } else {
        return edge_count/2;
    }
}

bool Graph::has_vertex(std::string vertex_one) {
    if (get_vertex_index(vertex_one) == -1) {
        return false;
    }
    return true;
}

bool Graph::insert_vertex(std::string vertex_one) {
    int insert_index = get_insert_vertex_index(vertex_one);
    if (insert_index == -1) {
        return false;
    }

    vertices.insert(vertices.begin()+insert_index, vertex_one);
    vertex_count++;

    edges.insert(edges.begin()+insert_index, std::vector< std::string* >());
    weights.insert(weights.begin()+insert_index, std::vector< float >());

    return true;
}

bool Graph::remove_vertex(std::string vertex_one) {
    int remove_index = get_vertex_index(vertex_one);
    if (remove_index == -1) {
        return false;
    }

    vertices.erase(vertices.begin()+remove_index);
    vertex_count--;

    return true;
}

bool Graph::has_edge(std::string vertex_one, std::string vertex_two) {
    int vertex_index_one = get_vertex_index(vertex_one);
    if (vertex_index_one == -1) {
        return false;
    }

    int vertex_index_two = get_vertex_index(vertex_two);
    if (vertex_index_two == -1) {
        return false;
    }

    if (get_edge_index(vertex_two, edges[vertex_index_one]) == -1) {
        return false;
    }

    return true;
}

bool Graph::insert_edge(std::string vertex_one, std::string vertex_two, float weight) {
    int vertex_one_index = get_vertex_index(vertex_one);
    if (vertex_one_index == -1) {
        return false;
    }

    int vertex_two_index = get_vertex_index(vertex_two);
    if (vertex_two_index == -1) {
        return false;
    }

    if (!weighted) {
        weight = 0;
    }

    int edge_one_index = get_insert_edge_index(vertex_two, edges[vertex_one_index]);
    if (edge_one_index == -1) {
        return false;
    }

    edges[vertex_one_index].insert(edges[vertex_one_index].begin() + edge_one_index, &vertices[vertex_two_index]);
    weights[vertex_one_index].insert(weights[vertex_one_index].begin() + edge_one_index, weight);
    edge_count++;
    if (!directed) {
        int edge_two_index = get_insert_edge_index(vertex_one, edges[vertex_two_index]);
        edges[vertex_two_index].insert(edges[vertex_two_index].begin() + edge_two_index, &vertices[vertex_one_index]);
        weights[vertex_two_index].insert(weights[vertex_two_index].begin() + edge_two_index, weight);
        edge_count++;
    }

    return true;
}

bool Graph::remove_edge(std::string vertex_one, std::string vertex_two) {
    int vertex_one_index = get_vertex_index(vertex_one);
    if (vertex_one_index == -1) {
        return false;
    }

    int vertex_two_index = get_vertex_index(vertex_two);
    if (vertex_two_index == -1) {
        return false;
    }

    int edge_one_index = get_edge_index(vertex_two, edges[vertex_one_index]);
    if (edge_one_index == -1) {
        return false;
    }

    edges[vertex_one_index].erase(edges[vertex_one_index].begin() + edge_one_index);
    weights[vertex_one_index].erase(weights[vertex_one_index].begin() + edge_one_index);
    edge_count--;
    if (!directed) {
        int edge_two_index = get_insert_edge_index(vertex_one, edges[vertex_two_index]);
        edges[vertex_two_index].erase(edges[vertex_two_index].begin() + edge_two_index);
        weights[vertex_two_index].erase(weights[vertex_two_index].begin() + edge_two_index);
        edge_count--;
    }

    return true;
}

bool Graph::is_connected() {
    if (vertex_count < 2) {
        return true;
    }

    if (!is_connected(vertices[0])) {
        return false;
    }

    std::vector< std::string > connected;
    std::vector< std::string > disconnected = vertices;
    connected.push_back(disconnected[0]);
    disconnected.erase(disconnected.begin());

    for (int i = 0; i < disconnected.size(); i++) {
        for (int j = 0; j < connected.size(); j++) {
            if (has_edge(disconnected[i], connected[j])) {
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

bool Graph::is_connected(std::string vertex_one) {
    int index = get_vertex_index(vertex_one);
    if (index == -1) {
        return false;
    }

    std::vector< std::string > connected;
    std::vector< std::string > disconnected = vertices;
    connected.push_back(vertex_one);
    disconnected.erase(disconnected.begin() + index);

    while (connected.size() > 0) {
        for (int i = 0; i < disconnected.size(); i++) {
            if (has_edge(connected[0], disconnected[i])) {
                connected.push_back(disconnected[i]);
                disconnected.erase(disconnected.begin() + i);
                i--;
            }
        }

        connected.erase(connected.begin());
    }

    if (disconnected.size() > 0) {
        return false;
    }

    return true;
}

bool Graph::is_fully_connected() {
    if (edge_count == (vertex_count-1)*vertex_count) {
        return true;
    }
    return false;
}

bool Graph::is_fully_disconnected() {
    if (edge_count == 0) {
        return true;
    }
    return false;
}

std::string Graph::to_string() {
    std::ostringstream ss;
    std::string return_string;

    for (int i = 0; i < vertex_count; i++) {
        return_string += vertices[i] + "| ";
        for (int j = 0; j < edges[i].size(); j++) {
            ss << *edges[i][j] << weights[i][j];
            return_string += ss.str();
            ss.str("");
        }
        return_string += "\n";
    }

    return_string += "\n";
    ss << get_vertex_count();
    return_string += "Vertex Count: " + ss.str();
    ss.str("");
    return_string += "\n";
    ss << get_edge_count();
    return_string += "Edge Count: " + ss.str();
    ss.str("");
    return_string += "\n";

    return return_string;
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

int Graph::get_edge_index(std::string edge_one, std::vector< std::string* > edges) {
    int min = 0;
    int mid;
    int max = edges.size()-1;

    while (min <= max) {
        mid = (min + max) / 2;

        if (edge_one.compare(*edges[mid]) == 0) {
            return mid;
        }

        if (edge_one.compare(*edges[mid]) < 0) {
            max = mid - 1;
        } else {
            min = mid + 1;
        }
    }

    return -1;
}

int Graph::get_insert_edge_index(std::string edge_one, std::vector< std::string* > edges) {
    if (edges.size() == 0) {
        return 0;
    }

    int min = 0;
    int mid;
    int max = edges.size()-1;

    while (min <= max) {
        mid = (min + max) / 2;

        if (edge_one.compare(*edges[mid]) == 0) {
            return -1;
        }

        if (edge_one.compare(*edges[mid]) < 0) {
            max = mid - 1;
        } else {
            min = mid + 1;
        }
    }

    if (mid == 0) {
        if (edge_one.compare(*edges[mid]) >= 0) {
            mid++;
        }
    } else {
        if (edge_one.compare(*edges[mid]) > 0) {
            mid++;
        }
    }

    return mid;
}
