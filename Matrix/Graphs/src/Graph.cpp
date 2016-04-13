#include "Graph.h"

Graph::Graph(bool weighted, bool directed) {
    this->weighted = weighted;
    this->directed = directed;

    vertex_count = 0;
    edge_count = 0;

    insert_vertex("B");
    insert_vertex("A");
    insert_vertex("C");

    insert_edge("A", "B", 4);
    insert_edge("A", "C", 4);
    remove_edge("B", "C");

    insert_vertex("C");

    std::cout << to_string();
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

/* Returns true if the vertex exists within the graph
 * false otherwise. */
bool Graph::has_vertex(std::string vertex_one) {
    /* Vertex does not exist */
    if (get_vertex_index(vertex_one) == -1) {
        return false;
    }
    return true;
}

/* Attempts to insert a new vertex into the graph
 * returns true if the insertion was successful
 * false otherwise. */
bool Graph::insert_vertex(std::string vertex_one) {
    /* Vertex already exists */
    int insert_index = get_insert_vertex_index(vertex_one);
    if (insert_index == -1) {
        return false;
    }

    /* Insert a new vertex into the vertices vector */
    vertices.insert(vertices.begin()+insert_index, vertex_one);
    vertex_count++;

    edges.insert(edges.begin()+insert_index, std::vector<float>(vertex_count-1, -1));

    for (int i = 0; i < vertex_count; i++) {
        edges[i].insert(edges[i].begin()+insert_index, -1);
    }

    return true;
}

/* Attempts to remove a vertex from the graph
 * returns true if the removal was successful
 * false otherwise. */
bool Graph::remove_vertex(std::string vertex_one) {
    /* Vertex does not exist */
    int remove_index = get_vertex_index(vertex_one);
    if (remove_index == -1) {
        return false;
    }

    /* Remove the vertex from the vertices vector */
    vertices.erase(vertices.begin()+remove_index);
    vertex_count--;

    return true;
}

bool Graph::has_edge(std::string vertex_one, std::string vertex_two) {
    int index_one = get_vertex_index(vertex_one);
    if (index_one == -1) {
        return false;
    }
    int index_two = get_vertex_index(vertex_two);
    if (index_two == -1) {
        return false;
    }

    if (edges[index_one][index_two] == -1) {
        return false;
    }

    return true;
}

bool Graph::insert_edge(std::string vertex_one, std::string vertex_two, float weight) {
    int index_one = get_vertex_index(vertex_one);
    if (index_one == -1) {
        return false;
    }
    int index_two = get_vertex_index(vertex_two);
    if (index_two == -1) {
        return false;
    }

    if (!weighted) {
        weight = 0;
    }

    edges[index_one][index_two] = weight;
    edge_count++;
    if (!directed) {
        edges[index_two][index_one] = weight;
        edge_count++;
    }

    return true;
}

bool Graph::remove_edge(std::string vertex_one, std::string vertex_two) {
    int index_one = get_vertex_index(vertex_one);
    if (index_one == -1) {
        return false;
    }
    int index_two = get_vertex_index(vertex_two);
    if (index_two == -1) {
        return false;
    }

    if (edges[index_one][index_two] == -1) {
        return false;
    }

    edges[index_one][index_two] = -1;
    edge_count--;
    if (!directed) {
        edges[index_two][index_one] = -1;
        edge_count--;
    }
    return true;
}

std::string Graph::to_string() {
    std::ostringstream ss;
    std::string return_string;

    for (int i = 0; i < vertex_count; i++) {
        return_string += vertices[i] + " ";
    }
    return_string += "\n";

    for (int i = 0; i < vertex_count; i++) {
        for (int j = 0; j < vertex_count; j++) {
            ss << edges[i][j];
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

/* Returns the index of a vertex in the vertex
 * vector, -1 is returned if the vertex is not
 * found */
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
