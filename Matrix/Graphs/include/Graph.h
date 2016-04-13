#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

// Matrix

class Graph
{
    public:
        Graph();
        virtual ~Graph();

        void set_directed(bool directed);
        bool is_directed();
        void set_weighted(bool weighted);
        bool is_weighted();

        bool has_vertex(std::string);
        bool insert_vertex(std::string);
        bool remove_vertex(std::string);

        bool has_edge(std::string);
        bool insert_edge(std::string);
        bool remove_edge(std::string);
    protected:
    private:
        std::vector< std::string > vertices;
        std::vector< std::vector< int > > edges;

        int vertex_count;
        int edge_count;

        bool weighted;
        bool directed;
};

#endif // GRAPH_H
