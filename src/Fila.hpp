#pragma once

#include <iostream>
#include <string>
#include "PokemonEntity.hpp"

struct NodePokemon{
    PokemonEntity poke;
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
        // Construtor e destrutor
        Fila(int t);
        
        // Get
        int get_tamanho() const;
        
        // Operações elementares da fila
        void enfileira(PokemonEntity p, bool *ok);
        void desenfileira(PokemonEntity *p, bool *ok);
        bool cheia();
        bool vazia();

        // Operações adicionais p/ o jogo
        void destroi();
};
