# Algoritmos de Grafos 
Neste repositório, existem quatro algoritmos de grafos implementados em C++ para a disciplina de Teoria dos Grafos. Para executar um algoritmo, basta entrar na pasta do algoritmo desejado, compilar, e executar.

Exemplo com algoritmo de dijkstra:

Compile o código:

```
  g++ dijsktra.cpp -o dijkstra
```
## Como executar
Para a execução, existem alguns parâmetros que podem ser recebidos:
- -h : mostra o help 
- -o <arquivo> : redireciona a saida para o ‘‘arquivo’’
- -f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada
- -s : mostra a solução (em ordem crescente)
- -i : vértice inicial (dependendo do algoritmo)
- -l : vértice final (dependendo do algoritmo)


## Dijkstra
Um algoritmo de caminhos mínimos, com complexidade O(|E| + |V|log|V|), porém incapaz de calcular caminhos em grafos com arestas de pesos negativos.

## Bellman-ford

Também para caminhos mínimos, apesar de ser mais lento do que Dijkstra, com O(|V| * |E|), consegue calcular caminhos mínimos quando existem arestas de pesos negativos, bem como detectar ciclos negativos no grafo.

## Prim

Um algoritmo simples para achar a AGM (Árvore geradora mínima) do grafo, com complexidade O(|E| log|V|).

## Kruskal

Da mesma forma que o algoritmo de Prim, Kruskal encontra a AGM do grafo, porém utiliza-se de outro método, ordenando as arestas em ordem crescente e utilizando a estrutura de Union-Find para agrupar componentes conexas para impedir a formação de ciclos, sua complexidade é O(|E| log|V|)
