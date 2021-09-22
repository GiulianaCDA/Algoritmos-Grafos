#include <bits/stdc++.h>
#include "../graph.h"

using namespace std;

vector<int> dijkstra(Graph g, int source){
    int v = g.get_size();
    vector<node*> edges = g.get_edges(); 
    vector<int> parents;
    vector<int> distances;

    for(int i=0; i < v; i++){
        distances.push_back(INT_MAX);
        parents.push_back(-1);
    }

    //implementação da heap miníma de c++
    priority_queue< pair<int,int>, vector <pair<int,int>> , greater<pair<int,int>> > min_heap;

    distances[source] = 0;
    min_heap.push(make_pair(distances[source], source));

    while(min_heap.size() > 0 ){
        int u = min_heap.top().second;
        min_heap.pop();
        node *current = edges[u];
        while(current != NULL){
            int weight = current->weight;
            int dest = current->dest;

            if(distances[dest] > distances[u] + weight){
                distances[dest] = distances[u] + weight;
                parents[dest] = u;
                min_heap.push(make_pair(distances[dest], dest));
            }
            current = current->next;
        }
    }

    return distances;

}

void help(){
    printf("Algoritmo de Dijkstra para caminhos mínimos:\n"
    "Para saber a distância mínima de um vértice x a y, use: \n./dijkstra -f entrada.in -i x -l y\n"
    "Para saber a distância mínima de um vértice x para todos, use: \n./dijkstra -f entrada.in -i x\n"
    "Para mostrar o caminho completo, use: \n./dijkstra -f entrada.in -i x -s\n");
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
            vector<int> dists = dijkstra(g, source);
            if (!o) printf("distância de %d para %d = %d\n", source, dest, dists[dest]);
            else{
                output_file << "distância de " << source << " para " << dest <<" = " << dists[dest] << endl; 
            }
        }
        else if(s || in){
            vector<int> dists = dijkstra(g, source);
            if (!o) printf("distância de %d para todos os outros vértices:\n", source);
            else{
                output_file << "distância de " << source << " para todos os outros vértices:" << endl;
            }
            for (int i = 0; i < dists.size(); i++){
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