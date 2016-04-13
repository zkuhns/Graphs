/*
Matrix implementation
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

class Graph
{
    public:
        Graph();
        virtual ~Graph();

        bool has_vertex(std::string vertex_one);
        bool insert_vertex(std::string vertex_one);
        bool remove_vertex(std::string vertex_one);

        bool has_edge(std::string vertex_one, std::string vertex_two);
        bool insert_edge(std::string vertex_one, std::string vertex_two);
        bool remove_edge(std::string vertex_one, std::string vertex_two);

        bool is_connected();
        bool is_fully_connected();
        bool is_fully_disconnected();

        std::string to_string();
    protected:
    private:
        bool weighted;
        bool directed;

        int vertex_count;
        int edge_count;

        std::vector< std::string > vertices;
        std::vector< std::vector < float> > edges;

        int get_vertex_index(std::string vertex_one);
        int get_insert_vertex_index(std::string vertex_one);
};

#endif // GRAPH_H
