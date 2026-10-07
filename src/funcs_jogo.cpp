#include "funcs_jogo.hpp"
#include <cstdlib>

int calcula_vantagem(int tipoA, int tipoB) {
    if (tipoA == FOGO && tipoB == PLANTA) return 1;
    if (tipoA == PLANTA && tipoB == AGUA) return 1;
    if (tipoA == AGUA && tipoB == FOGO) return 1;
    if(tipoA == FOGO && tipoB == FOGO) return 2;
    if(tipoA == AGUA && tipoB == AGUA) return 2;
    if(tipoA == PLANTA && tipoB == PLANTA) return 2;
    return 0;
}

Botao::Botao(sf::Vector2f pos, sf::Vector2f size, const std::string& label, const sf::Font& font):texto(font, label, 20) {
    box.setPosition(pos);
    box.setSize(size);
    box.setFillColor(sf::Color(70, 70, 70));
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(2.f);

    texto.setFillColor(sf::Color::White);
    // Centraliza o texto no botão
    texto.setPosition({pos.x + 15.f, pos.y + 10.f});
}

bool Botao::clicado(const sf::RenderWindow& window) const {
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);    
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
    
    return box.getGlobalBounds().contains(worldPos);
}

// Procedimento para desenhar o botão
void Botao::desenhar(sf::RenderWindow& window) const {
    window.draw(box);
    window.draw(texto);
}

// Carregando a pokedex
void carregar_dex(GameData& game){
    game.Pokedex[0] = PokemonEntity("Bulbasaur", TipoPokemon::PLANTA, "imagens/bulbasaur.png");
    game.Pokedex[1] = PokemonEntity("Charmander", TipoPokemon::FOGO, "imagens/charmander.png");
    game.Pokedex[2] = PokemonEntity("Squirtle", TipoPokemon::AGUA, "imagens/squirtle.png");
    game.Pokedex[3] = PokemonEntity("Chikorita", TipoPokemon::PLANTA, "imagens/chikorita.png");
    game.Pokedex[4] = PokemonEntity("Cyndaquil", TipoPokemon::FOGO, "imagens/cyndaquil.png");
    game.Pokedex[5] = PokemonEntity("Totodile", TipoPokemon::AGUA, "imagens/totodile.png");
    game.Pokedex[6] = PokemonEntity("Treecko", TipoPokemon::PLANTA, "imagens/treecko.png");
    game.Pokedex[7] = PokemonEntity("Torchic", TipoPokemon::FOGO, "imagens/torchic.png");
    game.Pokedex[8] = PokemonEntity("Mudkip", TipoPokemon::AGUA, "imagens/mudkip.png");
    game.Pokedex[9] = PokemonEntity("Turtwig", TipoPokemon::PLANTA, "imagens/turtwig.png");
    game.Pokedex[10] = PokemonEntity("Chimchar", TipoPokemon::FOGO, "imagens/chimchar.png");
    game.Pokedex[11] = PokemonEntity("Piplup", TipoPokemon::AGUA, "imagens/piplup.png");
}

// criando filas aleatórias
void randomiza_fila(GameData &game){
    //std::vector<PokemonEntity> copia;
    PokemonEntity copia[QTD_POKEMONS];

    
    for(int i = 0; i < QTD_POKEMONS; i++){
        copia[i] = game.Pokedex[i];
    }
    

    /*
    for(PokemonEntity p: game.Pokedex){
        copia.push_back(p);
    }
    */

    for (int i = QTD_POKEMONS - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        PokemonEntity tmp = copia[i];
        copia[i] = copia[j];
        copia[j] = tmp;
    }

    for(int i = 0; i < TAMANHO_TIMES; i++){
        bool aux;
        game.fila_PC.enfileira(copia[i], &aux);
    }
}

// Procedimento para exibir time do computador no início
void exibir_time_pc(GameData &game, sf::RenderWindow &window){
    Fila temp(TAMANHO_TIMES);
    
    float posicaoX = 100.f;
    float posicaoY = 250.f;

    int cont = 0;
    while(!game.fila_PC.vazia()){
        cont++;
        PokemonEntity aux;
        bool baux;

        game.fila_PC.desenfileira(&aux, &baux);

        sf::Text nome_pokemon(game.fonte, aux.get_nome());
        sf::Texture imagem_poke;
        imagem_poke.loadFromFile(aux.get_imagem());

        temp.enfileira(aux, &baux);

        sf::Sprite sprite_pokemon(imagem_poke);
        sprite_pokemon.setPosition({posicaoX, posicaoY});
        auto sz = imagem_poke.getSize();
        sprite_pokemon.setScale({static_cast<float>(200) / sz.x, static_cast<float>(200) / sz.y});
        
        if(aux.get_tipo() == TipoPokemon::FOGO){
            nome_pokemon.setFillColor(sf::Color(255,0,0));
        }

        else if(aux.get_tipo() == TipoPokemon::AGUA){
            nome_pokemon.setFillColor(sf::Color(0,0,255));
        }

        else if(aux.get_tipo() == TipoPokemon::PLANTA){
            nome_pokemon.setFillColor(sf::Color(0,255,0));
        }
        // Centraliza o texto no botão
        nome_pokemon.setPosition({posicaoX, posicaoY + 200.f});
        
        posicaoX+=215.f;
    
        window.draw(sprite_pokemon);
        window.draw(nome_pokemon);
    }

    while(!temp.vazia()){
        PokemonEntity aux;
        bool baux;

        temp.desenfileira(&aux, &baux);
        game.fila_PC.enfileira(aux, &baux);
    }
    sf::Text texto_primeiro(game.fonte, "Primeiro");
    sf::Text texto_ultimo(game.fonte, "Ultimo");

    texto_primeiro.setPosition({120.f, 210.f});
    texto_ultimo.setPosition({980.f, 210.f});

    window.draw(texto_primeiro);
    window.draw(texto_ultimo);
}

void randomiza_fila_escolha(GameData &game, Fila &f){

    PokemonEntity copia[QTD_POKEMONS];

    
    for(int i = 0; i < QTD_POKEMONS; i++){
        copia[i] = game.Pokedex[i];
    }
    

    //std::vector<PokemonEntity> copia;

    /*
    for(PokemonEntity p: game.Pokedex){
        copia.push_back(p);
    }
    */

    for (int i = QTD_POKEMONS - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        PokemonEntity tmp = copia[i];
        copia[i] = copia[j];
        copia[j] = tmp;
    }

    
    for(int i = 0; i < QTD_POKEMONS; i++){
        bool aux;
        f.enfileira(copia[i], &aux);
    }
    

    /*
    for(PokemonEntity p: copia){
        bool aux;
        f.enfileira(p, &aux);
    }
    */
}

void adicionar_tipo(PokemonEntity p, sf::Text &tipo_texto){
    if(p.get_tipo() == TipoPokemon::FOGO){
        tipo_texto.setFillColor(sf::Color(255, 0, 0));
    }
    if(p.get_tipo() == TipoPokemon::PLANTA){
        tipo_texto.setFillColor(sf::Color(0, 255, 0));
    }
    if(p.get_tipo() == TipoPokemon::AGUA){
        tipo_texto.setFillColor(sf::Color(0, 0, 255));
    }
}
void calcular_resultado_batalha(GameData &game){
    int resultado = calcula_vantagem(game.poke_atual_jogador.get_tipo(), game.poke_atual_PC.get_tipo());
    if(resultado == 1){
        game.pontos_jogador++;
        game.resultado_batalha.setString("Voce Venceu Essa Rodada!");
        game.resultado_batalha.setFillColor(sf::Color(0, 255, 0));
    }
    else if(resultado == 2){
        game.resultado_batalha.setString("Empate!");
        game.resultado_batalha.setFillColor(sf::Color(255, 255, 255));
    }
    else if(resultado == 0){
        game.pontos_PC++;
        game.resultado_batalha.setString("Voce Perdeu Essa Rodada!");
        game.resultado_batalha.setFillColor(sf::Color(255, 0, 0));
    }
    game.resultado_batalha.setPosition({450.f, 300.f});
}

void exibir_resultado_batalha(GameData &game, sf::RenderWindow &window){

}
