#include <iostream>
#include <string>
#include "Pokemon.h"

using namespace std;

Pokemon::Pokemon(string name, int type, string path){
    nome = name;
    tipo = type;
    imagem_path = path;
}

// Provavelmente não será utilizado no projeto, mas está aqui por precaução
Pokemon::Pokemon(){
    nome = "";
    tipo = 0;
    imagem_path = "";
}


string Pokemon::get_nome(){
    return nome;
}

int Pokemon::get_tipo(){
    return tipo;
}

string Pokemon::get_imagem(){
    return imagem_path;
}