#include <iostream>
#include <string>
#include "Fila.hpp"
#include "PokemonEntity.hpp"

using namespace std;

Fila::Fila(int t){
    inicio = nullptr;
    fim = nullptr;
    tamanho = 0;
    capacidade_maxima = t;
}

void Fila::enfileira(PokemonEntity p, bool *ok){
    if(cheia()){
        *ok = false;
        return;
    }

    NodePtr novo = new NodePokemon;
    novo->poke = p;
    novo->next = nullptr;

    if(vazia()){
        inicio = novo;
        fim = novo;
    } else {
        fim->next = novo;
        fim = fim->next;
    }

    tamanho++;
    *ok = true;
}

void Fila::desenfileira(PokemonEntity *p, bool *ok){
    if(vazia()){
        *ok = false;
        return;
    }

    NodePtr excluido = inicio;
    inicio = inicio->next;

    if(inicio == nullptr){
        fim = nullptr;
    }

    *p = excluido->poke;
    delete excluido;
    tamanho--;
    *ok = true;

}

bool Fila::cheia(){
    return tamanho == capacidade_maxima;
}

bool Fila::vazia(){
    return (inicio == nullptr);
}

int Fila::get_tamanho() const{
    return tamanho;
}

void Fila::pegaPrimeiro(PokemonEntity &p) const{
    p = inicio->poke;
}
