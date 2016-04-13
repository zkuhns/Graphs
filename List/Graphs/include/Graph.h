#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include <limits>

#include <Vertex.h>

class Graph {
    public:
        Graph();
        virtual ~Graph();

        void setWeighted(bool weighted);
        void setDirected(bool directed);

        bool isWeighted();
        bool isDirected();

        int getVertexIndex(std::string id);
        int getInsertIndex(std::string id);

        bool hasVertex(std::string id);
        bool addVertex(std::string id);
        bool deleteVertex(std::string id);

        float getEdgeWeight(std::string id_one, std::string id_two);
        bool hasEdge(std::string id_one, std::string id_two);
        bool addEdge(std::string id_one, std::string id_two);
        bool addEdge(std::string id_one, std::string id_two, float weight);
        bool deleteEdge(std::string id_one, std::string id_two);

        double getDensity();
        bool isSparse();
        bool isDense();

        bool isConnected(Vertex* pointer);
        bool isConnected();

        bool isFullyConnected();
        bool isFullyDisconnected();

        bool isStar();
        bool isRing();

        int clique(int num);
        int clique(int num, int current_num, int index, std::vector < Vertex* > clique);

        int getShortestDistance(std::string vertex_one, std::string vertex_two);
        std::vector < Vertex* > getShortestPath(std::string vertex_one, std::string vertex_two);

        int getMaxEdges();

        void printGraph();
    protected:
    private:
        bool weighted;
        bool directed;

        int vertex_count;
        int edge_count;

        std::vector < Vertex* > vertices;
};

#endif // GRAPH_H
