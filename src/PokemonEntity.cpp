#include <iostream>
#include <string>
#include "PokemonEntity.hpp"

using namespace std;

PokemonEntity::PokemonEntity(string name, int type, string path){
    nome = name;
    tipo = type;
    imagem_path = path;
}

// Provavelmente não será utilizado no projeto, mas está aqui por precaução
PokemonEntity::PokemonEntity(){
    nome = "";
    tipo = 0;
    imagem_path = "";
}


string PokemonEntity::get_nome() const{
    return nome;
}

int PokemonEntity::get_tipo() const{
    return tipo;
}

string PokemonEntity::get_imagem() const{
    return imagem_path;
}