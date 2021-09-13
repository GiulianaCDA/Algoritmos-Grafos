#ifndef GRAPH_H
#define GRAPH_H

#include <bits/stdc++.h>

using namespace std;

typedef struct Node node;

struct Node
{
    int dest;
    int weight;
    node* next;
};

class Graph
{
private:
    int size = 1000;
    vector <node*> adjlist;

public:
    Graph(int s)
    {
        size = s;
        for (int i = 0; i < size; i++)
        {
            adjlist.push_back(NULL);
        }
    }
    
    void add_edge(int source, int dest, int w)
    {
        node* edge = (node*) malloc(sizeof(node));
        edge->dest = dest;
        edge->weight = w;
        edge->next = adjlist[source];
        adjlist[source] = edge;
    }

    void print_graph()
    {
        for (int i = 0; i < size; i++)
        {
            printf("Node %d connections:\n", i);
            node *ll = adjlist[i];
            while (ll != NULL)
            {
                printf("-> %d ", ll->dest);
                ll = ll->next;
            }
            printf("\n");
        }
    }
};

#endif