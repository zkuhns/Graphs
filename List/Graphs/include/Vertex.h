#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <vector>
#include <iostream>

class Vertex {
    public:
        Vertex(std::string id);
        virtual ~Vertex();

        int getEdgeIndex(std::string id);
        int getInsertIndex(std::string id);

        float getEdgeWeight(Vertex* pointer);
        bool hasEdge(Vertex* pointer);
        bool addEdge(Vertex* pointer);
        bool addEdge(Vertex* pointer, float weight);
        bool deleteEdge(Vertex* pointer);

        std::string id;
        int edge_count;

        void printVertex();
    protected:
    private:
        std::vector < Vertex* > edges;
        std::vector < float > weights;
};

#endif // VERTEX_H
