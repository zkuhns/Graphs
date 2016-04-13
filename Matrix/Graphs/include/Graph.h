#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <iostream>

class Graph
{
    public:
        Graph();
        virtual ~Graph();

        bool isDirected();
        bool isWeighted();

        void setDirected(bool directed);
        void setWeighted(bool weighted);

        /* Vertex manipulation */
        bool hasVertex(std::string name_one);
        bool addVertex(std::string name_one);
        bool deleteVertex(std::string name_one);

        /* Edge manipulation */
        bool hasEdge(std::string name_one, std::string name_two);
        bool addEdge(std::string name_one, std::string name_two, float weight);
        bool deleteEdge(std::string name_one, std::string name_two);

        /* Connectivity */
        bool isFullyConnected();
        bool isFullyDisconnected();
        bool isConnected();

        void printGraph();
    protected:
    private:
        bool weighted;
        bool directed;

        int edge_count;
        int vertex_count;

        std::vector < std::string > vertices;
        std::vector < std::vector <float > > weights;

        int vertexIndex(std::string name_one);
        int insertIndex(std::string name_one);
};

#endif // GRAPH_H
