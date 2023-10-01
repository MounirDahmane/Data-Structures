#pragma once

#include <iostream>

class Graph
{
public:
    Graph(int vertices, int edges)
    {
        G = new Graph::_Graph;
        if (!G)
        {
            std::cout << "MEMORY_ERROR" << std::endl;
            return;
        }
        this->G->V = vertices;
        this->G->E = edges;
        auto memory = sizeof(node) * this->G->V;
        this->G->adj = new node[this->G->V];

        for (int i = 0; i < vertices; ++i)
            this->G->adj[i].next = nullptr;
    }
    ~Graph()
    {
        for (int i = 0; i < this->G->V; i++)
        {
            node* current = this->G->adj[i].next;
            while (current)
            {
                node* prev = current;
                current = current->next;
                delete prev;
            }
        }
        delete[] this->G->adj;
        delete this->G;
    }
    void addNode(int V1, int V2, int weight)
    {
        node* newElement_0 = new node(V2, weight);
        newElement_0->next = this->G->adj[V1].next;
        this->G->adj[V1].next = newElement_0;

        node* newElement_1 = new node(V1, weight);
        newElement_1->next = this->G->adj[V2].next;
        this->G->adj[V2].next = newElement_1;
    }
    void PrintConnection()
    {
        for (std::size_t i = 0; i < this->G->V; i++)
        {
            std::cout << "V" << i << " is connected to : ";
            node* current = this->G->adj[i].next;
            while (current)
            {
                std::cout << current->VertexNumber << " ";
                current = current->next;
            }
            std::cout<<std::endl;
        }
    }

private:
    struct node
    {
        int VertexNumber;
        int weight;
        node* next;
        node(int v, int w) : VertexNumber(v), next(nullptr) ,weight(w) {}
        node() {};
    };
    struct _Graph
    {
        int V;
        int E;
        node* adj;
    };
    _Graph* G;
};








