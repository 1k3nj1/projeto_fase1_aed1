#ifndef FILA_UTIL
#define FILA_UTIL

#include <iostream>
#include <string>
#include "Pokemon.h"

struct NodePokemon{
    Pokemon poke;
    NodePokemon* next;
};

typedef struct NodePokemon *NodePtr;

class Fila {
    private:
        NodePtr inicio;
        NodePtr fim;
        int tamanho;
        int capacidade_maxima;
    
    public:
        Fila(int t);
        void enfileira(Pokemon p, bool *ok);
        void desenfileira(Pokemon *p, bool *ok);
        bool cheia();
        bool vazia();

        int get_tamanho() const;
};

#endif