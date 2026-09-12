#include <iostream>
#include <string>

using namespace std;

class Pokemon{
    private:
        string nome;
        int tipo;
        string imagem_path;
    
    public:
        Pokemon(string n, int t, string i);
        string get_nome();
        int get_tipo();
        string get_imagem();
        Pokemon();
};

