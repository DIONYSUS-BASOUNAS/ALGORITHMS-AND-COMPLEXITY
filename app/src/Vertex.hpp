#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <set>
#include <list>
#include <vector>

class Vertex {

    private:
        int vertex;
        int degree;
         int satur;
        bool isColored = false;

 std::set<int, std::greater<int>> neighborColors;
    public:
        Vertex();
        Vertex(int vertex);
        Vertex(int vertex, int degree);
        Vertex(int vertex, int degree, int satur, bool isColored);

        bool operator < (const Vertex& v);

        void setVertex(int vertex);
        int getVertex();

        void setDegree(int degree);
        int getDegree();
          
        void setSatur(int satur);
        int getSatur();
        void raiseSatur();

        void setVertexColored(bool isColored);
        bool isVertexColored();

        bool checkNeighborColor(int color, int source, std::list<Vertex> adjList, int cv[], std::vector<Vertex> vertices);

        void addNeighborColor(int color);
        int getSizeOfNeighborColors();
        std::set<int, std::greater<int>> getNeighborColors();
};

#endif /* VERTEX_HPP */