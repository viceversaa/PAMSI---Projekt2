#include <iostream>
#include <limits>
#include "bfData.cpp"

using namespace std;

class Graph
{
    const int n;
    double **tab; // tablica dwuwymiarowa, tablica krawedzi
public:
    Graph(Graph &g) = delete;
    Graph(int size) : n(size) 
    {
        tab = new double *[n];
        for (int i = 0; i < n; i++)
        {
            tab[i] = new double[n];
            for (int j = 0; j < n; j++)
            {
                tab[i][j] = numeric_limits<double>::infinity();
            }
        }
    }
    Graph(Graph &&g) : n(g.n)
    {
        tab = g.tab;
        g.tab = nullptr;
    }

    ~Graph()
    {
        if (tab != nullptr)
        {

            for (int i = 0; i < n; i++)
            {
                delete[] tab[i];
            }
            delete[] tab;
        }
    }
    void addEdge(int v1, int v2, double waga)
    {
        tab[v1][v2] = waga;
    }

    bfData *BellmanFord(int src)
    {
        bfData *dist = new bfData[n]; // odleglosc
        for (int i = 0; i < n; i++)
        {
            dist[i] = {numeric_limits<double>::infinity(),-1};
        }
        dist[src].dist = 0;
        for (int i = 0; i < n; i++) // ile razy
        {
            for (int j = 0; j < n; j++) // na wierzcholki
            {
                for (int k = 0; k < n; k++)
                {
                    if (dist[j].dist + tab[j][k] < dist[k].dist) // jesli po dodaniu wartosc bedzie mniejsza(bedzie to najkrotsza droga)
                    {
                        dist[k].dist = dist[j].dist + tab[j][k]; // to tu ja zapisujemy i ja bedziemy chcieli zwrocic
                        
                    }
                }
            }
        }
        return dist;
    }
};
