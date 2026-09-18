#pragma once

#include <iostream>
#include <string>

class PokemonEntity{
    private:
        std::string nome;
        int tipo;
        std::string imagem_path;
    
    public:
        PokemonEntity(std::string n, int t, std::string i);
        PokemonEntity();
        
        std::string get_nome() const;
        int get_tipo() const;
        std::string get_imagem() const;
};
