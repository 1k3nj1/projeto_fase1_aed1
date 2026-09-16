#ifndef POKEMON_UTIL
#define POKEMON_UTIL

#include <iostream>
#include <string>

class Pokemon{
    private:
        std::string nome;
        int tipo;
        std::string imagem_path;
    
    public:
        Pokemon(std::string n, int t, std::string i);
        std::string get_nome() const;
        int get_tipo() const;
        std::string get_imagem() const;
        Pokemon();
};

#endif