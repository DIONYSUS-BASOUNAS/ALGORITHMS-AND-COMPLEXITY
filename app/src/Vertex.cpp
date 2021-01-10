#include "Vertex.hpp"

Vertex::Vertex(){}

Vertex::Vertex(int vertex) {
    setVertex(vertex);
    setSatur(0);
    setVertexColored(false);
}

Vertex::Vertex(int vertex, int degree) {
    setVertex(vertex);
    setDegree(degree);
    setSatur(0);
    setVertexColored(false);
}

Vertex::Vertex(int vertex, int degree, int satur, bool isColored) {
    setVertex(vertex);
    setDegree(degree);
    setSatur(satur);
    setVertexColored(isColored);
}

bool Vertex::operator<(const Vertex& v) {
    return this->degree < v.degree;
}

void Vertex::setVertex(int vertex) {
    this -> vertex = vertex;
}

int Vertex::getVertex() {
    return this -> vertex;
}

void Vertex::setDegree(int degree) {
    this -> degree = degree;
}

int Vertex::getDegree() {
    return this -> degree;
}

void Vertex::setSatur(int satur) {
    this -> satur = satur;
}

int Vertex::getSatur() {
    return this -> satur;
}

void Vertex::raiseSatur() {
    this->satur++;
}

void Vertex::setVertexColored(bool isColored) {
    this -> isColored = isColored;
}

bool Vertex::isVertexColored() {
    return this -> isColored;
}

bool Vertex::checkNeighborColor(int color, int source, std::list<Vertex> adjList, int cv[], std::vector<Vertex> vertices) {
    for (auto i = adjList.begin(); i != adjList.end(); ++i)
        if (vertices[i->getVertex()].isVertexColored() && vertices[i->getVertex()].getVertex() != source)
            if (color == cv[i->getVertex()])
                return true;
    return false;
}

void Vertex::addNeighborColor(int color) {
    this -> neighborColors.insert(color);
}

int Vertex::getSizeOfNeighborColors() {
    return this -> neighborColors.size();
}

std::set<int, std::greater<int>> Vertex::getNeighborColors() {
    return this -> neighborColors;
}