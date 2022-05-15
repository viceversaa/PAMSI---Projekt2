#include <limits>
#include "bfData.cpp"
using namespace std;

struct Edge
{
    int end;
    double weight;
};

struct Element
{
    Edge edge;
    Element *next;
};

class AdjacencyList
{
public:
    Element *first = nullptr;
    void addEdge(Edge edge)
    {
        first = new Element{edge, first};
    }
    ~AdjacencyList() //lista sasiedzctwa
    {
        Element *it = first;
        while (it != nullptr)
        {
            Element *next = it->next;
            delete it;
            it = next;
        }
    }
};

class Graph
{
    const int n;             // liczba wierzcholkow
    AdjacencyList *vertices; 

public:
    Graph(int n) : n(n), vertices(new AdjacencyList[n]) {}

    Graph(Graph &) = delete;

    Graph(Graph &&g) : n(g.n)
    {
        vertices = g.vertices;
        g.vertices = nullptr;
    }

    void addEdge(int v1, int v2, double weight)
    {
        vertices[v1].addEdge(Edge{v2, weight});
    }

    bfData *BellmanFord(int src)
    {
        bfData *dist = new bfData[n];
        for (int i = 0; i < n; i++)
        {
            dist[i] = {numeric_limits<double>::infinity(), -1};
        }
        dist[src].dist = 0;
        for (int i = 0; i < n; i++) 
        {
            for (int j = 0; j < n; j++) 
            {

                for (Element *k = vertices[j].first; k != nullptr; k = k->next) // k - krawedz
                {
                    if (dist[j].dist + k->edge.weight < dist[k->edge.end].dist)
                    {
                        dist[k->edge.end].dist = dist[j].dist + k->edge.weight;
                        dist[k->edge.end].prev = j;
                    }
                }
            }
        }
        return dist;
    }

    ~Graph()
    {
        delete[] vertices;
    }
};
