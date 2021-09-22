#include <bits/stdc++.h>
#include "../graph.h"

using namespace std;

vector<int> bellman(Graph g, int source){
    // Preparando as variáveis
    int v = g.get_size();
    vector<node*> edges = g.get_edges();
    int e = edges.size();
    vector<int> distances;
    
    for (int i = 0; i < v; i++)
    {
        distances.push_back(INT_MAX);
    }
    distances[source] = 0;

    // Calculando distâncias mínimas com até i vértices
    for (int i = 1; i <= v-1; i++)
    {
        // Iterar por cada aresta do grafo
        for (int j = 0; j < v; j++)
        {
            node* neighs = edges[j];
            while(neighs != NULL)
            {
                int d = neighs->dest;
                int w = neighs->weight;
                neighs = neighs->next;
                // Escolhendo o menor caminho
                if (distances[j] + w < distances[d] && distances[j] != INT_MAX)
                {
                    distances[d] = distances[j] + w;
                }
            }
        }
    }
    // Bônus: verificando se existe ciclo negativo!
    for (int j = 0; j < v; j++)
    {
        node* neighs = edges[j];
        while(neighs != NULL)
        {
            int d = neighs->dest;
            int w = neighs->weight;
            neighs = neighs->next;
            // Se após |V|-1 iterações ainda existe um melhor caminho
            if (distances[j] + w < distances[d] && distances[j] != INT_MAX)
            {
                printf("Ciclo negativo detectado!\n");
                break;
            }
        }
    }
    return distances;
}

void help(){
    printf("Algoritmo de Bellman-Ford para caminhos mínimos com arestas negativas:\n"
    "Para saber a distância mínima de um vértice x a y, use: \n./bellman-ford -f entrada.in -i x -l y\n"
    "Para saber a distância mínima de um vértice x para todos, use: \n./bellman-ford -f entrada.in -i x\n");
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
        
        if (in && l){
            vector<int> dists = bellman(g, source);
            if (!o) printf("distância de %d para %d = %d\n", source, dest, dists[dest]);
            else{
                output_file << "distância de " << source << " para " << dest <<" = " << dists[dest] << endl;
            }
        }
        else if(s || in){
            vector<int> dists = bellman(g, source);
            if (!o) printf("distância de %d para todos os outros vértices:\n", source);
            else{
                output_file << "distância de " << source << " para todos os outros vértices:" << endl;
            }
            for (int i = 0; i < dists.size(); i++)
            {
                if (!o) printf("%d:%d  ", i, dists[i]);
                else{
                    output_file << i << ":" << dists[i] << "  ";
                }
            }
            printf("\n");
            output_file << endl;
        }
    }
    output_file.close();
    return 0;
}