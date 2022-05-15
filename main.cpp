#include <iostream>
#include <chrono>
#include <fstream>
#include "grafy.cpp"
//#include "lista.cpp"
using namespace std;
using namespace std::chrono;

bool draw(double possibility)
{
    int n = rand() % 1000000000;
    int m = possibility * 1000000000;
    return n < m;
}

Graph createGraph(double density, int v)
{
    Graph graph(v);
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            if (draw(density))
            {
                graph.addEdge(i, j, rand() % 1000000000);
            }
        }
    }
    return move(graph);
}

void measureExecutionTime()
{
    int sizes[5] = {10, 50, 100, 500, 1000}; //rozmiar
    double densities[4] = {0.25, 0.5, 0.75, 1}; //procent zapelnienia
    for (int size : sizes)
    {
        for (double density : densities)
        {
            long long int time = 0;
            for (int i = 0; i < 100; i++)
            {
                Graph graph = createGraph(density, size);
                auto start = high_resolution_clock::now();
                auto *distance = graph.BellmanFord(0);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<milliseconds>(stop - start);
                time += duration.count();
                delete[] distance;
            }
            cout << "Rozmiar: " << size << " Gestosc: " << density * 100 << "%"
                 << " Czas: " << time << " ms" << endl;
        }
    }
}

void analyzeGraphFromFile()
{
    ifstream input("input.txt");
    int e, v, start; // start-pierwszy wierz., e-liczba krawedzi, v - liczba wierzcholkow
    input >> e >> v >> start;
    Graph graph(v);
    for (int i = 0; i < e; i++)
    {
        int from, to, w;
        input >> from >> to >> w;
        graph.addEdge(from, to, w);
    }
    bfData *bf = graph.BellmanFord(start);
    ofstream output("output.txt");
    for (int i = 0; i < v; i++)
    {
        output << "Wierzcholek " << i << ": "
               << "Odleglosc " << bf[i].dist << "; "; // odleglosc
        if (bf[i].dist != numeric_limits<double>::infinity())
        {
            int it = i;
            output << "Sciezka: " << it;
            it = bf[it].prev;
            while (it != -1)
            {
                output << " <- " << it;
                it = bf[it].prev;
            }
        }
        output << endl;
    }
}

int main()
{
    cout << "Wybierz jedna z opcji" << endl;
    cout << "1 - badanie efektywnosci" << endl << "2 - wczytywanie grafu z pliku" << endl;
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        measureExecutionTime();
    }
    else
    { 
        cout << "Wejdz w plik output.txt aby zobaczyc wyniki" << endl;
        analyzeGraphFromFile();
    }
}
