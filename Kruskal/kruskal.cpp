#include <bits/stdc++.h>
#include "../graph.h"

using namespace std;
typedef struct edge Edge;
typedef struct UnionFind uf;

//struct UnionFind{
//    int rank[]; int parent[];
//};
struct edge{
    int src; int dest; int weight;
};

void Union(int x, int y, int parent[], int rank[])
{
    if (rank[x] >= rank[y]){
        parent[y] = x;
        if (rank[x] == rank[y]){
            rank[x]++;
        }
        return;
    }
    parent[x] = y;
}

int Find(int x, int parent[], int rank[])
{
    if (parent[x] != x){
        parent[x] = Find(parent[x], parent, rank);
    }
    return parent[x];
}

bool compareEdges(Edge a, Edge b)
{
    return (a.weight < b.weight);
}

vector<Edge> make_edges(vector<node*> g)
{
    vector<Edge> edges;
    for (int i = 0; i < g.size(); i++){
        node* current = g[i];
        while (current != NULL){
            Edge new_edge;
            new_edge.src = i;
            new_edge.dest = current->dest;
            new_edge.weight = current->weight;
            edges.push_back(new_edge);
            current = current->next;
        }
    }

    return edges;
}

vector<Edge> kruskal(Graph g, int source){
    
    vector<Edge> MST;
    int v = g.get_size();

    // Criando array com arestas ordenadas
    vector<Edge> sorted_edges = make_edges(g.get_edges());
    sort(sorted_edges.begin(), sorted_edges.end(), compareEdges);

    // Inicializando todas as componentes no Union-Find
    int rank[v], parent[v];
    for (int i = 0; i < v; i++){
        parent[i] = i;
        rank[v] = v;
    }
    // Iterar por todas as arestas
    for (int i = 0; i < sorted_edges.size(); i++){
        int u = sorted_edges[i].src;
        int v = sorted_edges[i].dest;
        int c1 = Find(u, parent, rank);
        int c2 = Find(v, parent, rank);

        if (c1 != c2){
            MST.push_back(sorted_edges[i]);
            Union(c1, c2, parent, rank);
        }
    }
    
    return MST;
}

int get_weight(vector<Edge> MST){
    int total_weight = 0;
    for (int i = 0; i < MST.size(); i++){
        total_weight += MST[i].weight;
    }
    return total_weight;
}

void help(){
    printf("Algoritmo de Kruskal para Árvores Geradoras mínimas:\n"
    "Para saber o custo da árvore geradora mínima, use: \n./kruskal -f entrada.in\n"
    "Para mostrar o árvore geradora mínima completa, use: \n./kruskal -f entrada.in -s\n");
}

int main(int argc, char* argv[]){
    int f = 0, o = 0, s = 0, in = 0, l = 0;
    int source, dest;
    char* input_name;
    char* output_name;
    // Recebendo e tratando os argumentos
    for (int i = 0; i < argc; i++){
        if(!strcmp(argv[i], "-h")) help();
        if(!strcmp(argv[i], "-o")){o++; output_name = argv[i+1]; }
        if(!strcmp(argv[i], "-f")){f++; input_name = argv[i+1]; }
        if(!strcmp(argv[i], "-i")){ in++; source = stoi(argv[i+1]); }
        if(!strcmp(argv[i], "-l")){ l++; dest = stoi(argv[i+1]); }
        if(!strcmp(argv[i], "-s")) s++;
    }
    ofstream output_file;
    output_file.open(output_name);
    
    if(f){
        Graph g = read_graph_file(input_name);
        
        if (!s){
            vector<Edge> MST = kruskal(g, source);
            int w = get_weight(MST);
            if (!o) printf("Peso da AGM: %d\n", w);
            else{
                output_file << "Peso da AGM: " << w << endl; 
            }
        }
        else{
            vector<Edge> MST = kruskal(g, source);
            if (!o) printf("Árvore geradora mínima:\n");
            else{
                output_file << "Árvore geradora mínima:"<< endl;
            }
            for (int i = 0; i < MST.size(); i++){
                if (!o) printf("(%d,%d)  ", MST[i].src, MST[i].dest);
                else{
                    output_file << "(" << MST[i].src << "," << MST[i].dest << ")  ";
                }
            }
            printf("\n");
            output_file << endl;
        }
    }
    output_file.close(); 
    return 0;
}