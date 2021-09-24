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
    int V = 1000;
    vector <node*> adjlist;

public:
    Graph(int vertexes){
        V = vertexes;
        for (int i = 0; i < V; i++)
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
    int get_size() { return V;}
    vector<node*> get_edges() {return adjlist;}
};
// separa a linha em parâmetros
void split(string line, int* source, int* dest, int* weight){
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

//lê o grafo de um arquivo
Graph read_graph_file(const char* file){
    int edges, vertexes, temp;
    string line;

    ifstream input_file(file);
    getline(input_file, line);
    split(line, &edges, &vertexes, &temp);
    Graph grafo(vertexes);

    if (input_file.is_open()){
        while (getline(input_file,line))
        {
            int source, dest, weight;
            split(line, &source, &dest, &weight);
            grafo.add_edge(source, dest, weight);
        }
        input_file.close();
    }
    else {printf("Não foi possível abrir o arquivo de entrada\n");}

    return grafo;
}

// Lê um grafo da entrada do terminal
Graph read_graph(){
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