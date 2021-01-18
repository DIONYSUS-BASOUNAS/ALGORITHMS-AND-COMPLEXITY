#include "GraphColoring.hpp"
Graph::Graph() {}
Graph::Graph(int exams, std::string problemName)
{
    this->exams = exams;
    this->problemName = problemName;
    adj_Matrix = new std::list<Vertex>[exams];
    adj = new std::list<int>[exams];
    colors.insert(1);
}
Graph::~Graph()
{
    delete[] adj_Matrix;
    delete[] adj;
}
void Graph::initaiLizedAdj_Martix(std::vector<std::set<int>> examStudents)
{
    std::cout << "Adjacency Matrix" << std::endl;
    for (int i = 0; i < exams; i++)
    {
        std::cout << i+1<<":";
        for (int j = 0; j < exams; j++)
        {
            if (i == j)
            {
               
                continue;
            }
            int c = commonElements(examStudents[i + 1], examStudents[j + 1]);
            if (c > 0){
            if(j>i)
                addEdge(i, j);
            std:: cout << j +1 <<"";
        }
    }
     std::cout << std::endl;
    }
}
void Graph::addEdge(int i, int j)
{
    Vertex v1(j);
    adj_Matrix[i].push_back(v1);
    adj[i].push_back(j);
    Vertex v2(i);
    adj_Matrix[j].push_back(v2);
    adj[j].push_back(i);
}
int Graph::commonElements(std::set<int> s1, std::set<int> s2)
{
    int c = 0;
    for (int x : s1)
    {
        for (int y : s2)
        {
            if (x == y)
            {
                c++;
                break;
            }
        }
    }
    return c;
}

void Graph::conflictDensity()
{
     int c = 0;
    for (int i = 0; i < exams; i++) {
        for (auto j = adj_Matrix[i].begin(); j != adj_Matrix[i].end(); ++j) {
            c++;
        }
    }
    this -> confDen = double(c) / double(exams * exams);
}
void Graph::stats()
{
    this->max = 0;
    this->min = (2 ^ 31) - 1;
    for (int i = 0; i < exams; i++)
    {
        int degree = adj_Matrix[i].size();
        Vertex v(i, degree);
        this -> vertices.push_back(v);

        this -> sequenceDegree.push_back(degree);
           if(degree > max)
           this -> max = degree;
           if(degree < min)
           this -> min = degree;
        

       
    }
    std::sort(sequenceDegree.begin(), sequenceDegree.end());
    int indexMed;
    if (sequenceDegree.size() % 2 == 0) {
        indexMed = sequenceDegree.size() / 2;
    } else {
        indexMed = (sequenceDegree.size() + 1) / 2;
    }

    this -> med = sequenceDegree[indexMed];
}
void Graph::degMean(){
    int sum=0;
    for (int i=0;i<int(sequenceDegree.size());i++){
    sum+=sequenceDegree[i];
    }
    this ->mean=double(sum)/double(sequenceDegree.size());
}
void Graph::coefVar(){
    double sum =0.0;
    double a,b;
    for(int i=0;i<int(sequenceDegree.size());i++){
        a=double(sequenceDegree[i])-mean;
        b=pow(a,2.0);
        sum+=b;
    }
    double S2=sum/double(sequenceDegree.size());
    double S= sqrt(S2);
    this -> CV=(S/mean)*100;
}
void Graph::greedyColoring()
{
   int result[exams];
    int Csize=0;
    // Assign the first color to first vertex
    result[0] = 0;

    // Initialize remaining V-1 vertices as unassigned
    for (int u = 1; u < exams; u++)
        result[u] = -1; // no color is assigned to u

    // A temporary array to store the available colors. True
    // value of available[cr] would mean that the color cr is
    // assigned to one of its adjacent vertices
    bool available[exams];
    for (int cr = 0; cr < exams; cr++)
        available[cr] = true;

    // Assign colors to remaining V-1 vertices
    for (int u = 1; u < exams; u++)
    {
        // Process all adjacent vertices and flag their colors
        // as unavailable
        std::list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (result[*i] != -1)
                available[result[*i]] = false;

        // Find the first available color
        int cr;
        for (cr = 0; cr < exams; cr++){
            if(Csize<cr)
                Csize=cr;
            if (available[cr])
                break;
        }
        result[u] = cr; // Assign the found color

        // Reset the values back to true for the next iteration
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (result[*i] != -1)
                available[result[*i]] = true;
    }

    // print the result
    for (int u = 0; u < exams; u++)
        std::cout << "Vertex " << u << " --->  Color "
             << result[u] << std::endl;

    std::cout<< "size "<<Csize+1<<std::endl;
}

void Graph::DSatur() {

    int colorOfVertex[exams];

    int mvd = maximumVertexDegree();

    for (int v = 0; v < exams; v++) 
        colorOfVertex[v] = -1;
    //xromatismos protis korifis
    colorOfVertex[mvd] = *colors.end();
    vertices[mvd].setSatur(-1);
    vertices[mvd].setVertexColored(true);
    //
    for (auto it = adj_Matrix[mvd].begin(); it != adj_Matrix[mvd].end(); ++it) {
        if (!(vertices[it->getVertex()].checkNeighborColor(colorOfVertex[mvd], mvd, adj_Matrix[it->getVertex()], colorOfVertex, vertices)))
           vertices[it->getVertex()].raiseSatur();

    }

    while (!graphIsColored()) {
        int maxSaturDegree = -1;
        for (auto it = vertices.begin(); it != vertices.end(); ++it)
            if ((it->getSatur() > maxSaturDegree) && !(it->isVertexColored()))
                maxSaturDegree = it->getSatur();

        int maxSaturVertex;
        int degree = -1;
        for (auto it : vertices) {
            if ((it.getSatur() == maxSaturDegree) && !(it.isVertexColored())) {
                if (it.getDegree() > degree) {
                    degree = it.getDegree();
                    maxSaturVertex = it.getVertex();
                }
            }
        }

        //color vertex
        std::set< int, std::greater<int> > aux;
        std::set< int, std::greater<int> > diff;
        for (auto it = adj_Matrix[maxSaturVertex].begin(); it != adj_Matrix[maxSaturVertex].end(); ++it)
            if (vertices[it->getVertex()].isVertexColored())
                aux.insert(colorOfVertex[it->getVertex()]);

        std::set_difference(
            colors.begin(), colors.end(),
            aux.begin(), aux.end(),
            std::inserter(diff, diff.end())
        );

        if (diff.size() > 0) {
            colorOfVertex[maxSaturVertex] = *diff.end();
        } else {
            int newColor = *colors.end() + 1;
            colors.insert(newColor);
            colorOfVertex[maxSaturVertex] = *colors.end();
        }

        vertices[maxSaturVertex].setVertexColored(true);

        //update Neighbors
        for (auto it = adj_Matrix[maxSaturVertex].begin(); it != adj_Matrix[maxSaturVertex].end(); ++it)
            if (!(vertices[it->getVertex()].checkNeighborColor(colorOfVertex[maxSaturVertex], maxSaturVertex, adj_Matrix[it->getVertex()], colorOfVertex, vertices)))
                vertices[it->getVertex()].raiseSatur();
    }

    //print colored graph
    for (int u = 0; u < exams; u++)
        std::cout << "Vertex " << u << " --->  Color "
             << colorOfVertex[u] - 1 << std::endl;
    std::cout << "size "<< colors.size()<<std::endl;
}
int Graph::maximumVertexDegree() {
    int max = getDegree(0);
    int vertex = 0;
  
    for (int i = 1; i <exams; i++) {
        if (getDegree(i) > max) {
            max = getDegree(i);
            vertex = i;
        }
    }
    return vertex;
}
bool Graph::graphIsColored() {
    for (auto it : vertices)
        if (!it.isVertexColored())
            return false;
    return true;
}
void Graph::printStatisticArray(){
    for (int i=0;i<13;i++){
        std::cout<<statisticArray[i]<<std::endl;
    }
}
int Graph::getDegree(int vertex) {
    return adj_Matrix[vertex].size();
}
std::list<Vertex>* Graph::getadj_Matrix() {return adj_Matrix;}
int Graph::getVertices(){return exams;}

std::string Graph::toString() {
    return "Name: " + this -> problemName.substr(12, 8) + " |V|: " + std::to_string(exams) + " Conflict Density: "+ std::to_string(confDen) +
                                        " Min: " + std::to_string(min) + " Med: " + std::to_string(med) + " Max: " + std::to_string(max) +
                                        " Mean: " + std::to_string(mean) + " CV(%): " + std::to_string(CV) + "%";
}