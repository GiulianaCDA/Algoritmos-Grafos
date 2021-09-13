#ifndef GRAPH_H
#define GRAPH_H

#include <bits/stdc++.h>

using namespace std;

typedef struct Node node;

struct Node{
    int dest;
    int weight;
    node* next;
};

class Graph{
private:
    int size = 1000;
    vector <node*> adjlist;

public:
    Graph(int s){
        size = s;
        for (int i = 0; i < size; i++)
        {
            adjlist.push_back(NULL);
        }
    }
    
    void add_edge(int source, int dest, int w){ 
        node* edge = (node*) malloc(sizeof(node));
        edge->dest = dest;
        edge->weight = w;
        edge->next = adjlist[source];
        adjlist[source] = edge;
    }

};
void split(string line, int* source, int* dest, int* weight){ //separa a linha nos parâmetros source, dest e weight
    string delimiter = " "; 
    size_t pos = 0;
    string token;
    vector <int> values;
    line = line + " ";
    while ((pos = line.find(delimiter)) != string::npos) {
        token = line.substr(0, pos);
        values.push_back(stoi(token));
        line.erase(0, pos + delimiter.length());
    }

    *source = values[0];
    *dest = values[1];
    
    (values.size() == 2) ? *weight = 1 : *weight = values[2];
}

Graph read_graph(){ //lê um grafo 
    int edges;
    int vertexes;
    

    scanf("%d%d\n", &edges, &vertexes);

    Graph grafo(vertexes);

    for (int i = 0; i < edges; i++){
        int source, dest, weight;
        string line;
        getline(cin, line);
        split(line, &source, &dest, &weight);
        printf("source: %d dest: %d weight: %d\n", source, dest, weight);
        grafo.add_edge(source, dest, weight);
    }


    return grafo;
}

#endif