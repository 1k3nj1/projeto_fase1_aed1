#pragma once

#include "Fila.hpp"
#include <SFML/Graphics.hpp>    
#include "DEFINITIONS.hpp"

enum TipoPokemon {
    FOGO = 0,
    PLANTA = 1,
    AGUA = 2
};

enum Estado {
    TELA_INICIAL,
    MENU,
    VER_TIME_PC,
    ESCOLHA,
    BATALHA,
    TELA_FINAL
};

// 1 se tipoA vence, 0 caso contrário
int calcula_vantagem(int tipoA, int tipoB);

struct Botao {
    sf::RectangleShape box;
    sf::Texture imagem;
    sf::Text texto;

    Botao(sf::Vector2f pos, sf::Vector2f size, const std::string& label, const sf::Font& font);
    bool clicado(const sf::RenderWindow& window) const;
    void desenhar(sf::RenderWindow& window) const;
};

struct GameData{
    Estado estado_atual{Estado::TELA_INICIAL};
    
    Fila fila_jogador{5};
    Fila fila_PC{5};

    std::vector<PokemonEntity> Pokedex;
    int indice_atual{0};
    int tentativas_restantes{3};
    std::string mensagem_captura{""};

    // Lógica da Batalha
    int pontos_jogador{0};
    int pontos_PC{0};
    PokemonEntity poke_atual_jogador;
    PokemonEntity poke_atual_PC;
    // bool round_ativo{false};
    sf::Clock timer_batalha;

    // Recursos
    sf::Font fonte;
    sf::Texture splash_textura;
    sf::Sprite splash_sprite{splash_textura};
    sf::Texture textura_atual;
    sf::Sprite sprite_atual{textura_atual};
};

void carregar_dex(GameData& game);
void randomiza_fila(GameData &game);
void randomiza_fila_escolha(GameData &game, Fila &f);
void exibir_time_pc(GameData &game, sf::RenderWindow &w);
void adicionar_tipo(PokemonEntity p, sf::Text &tipo_texto);
void exibir_resultado_batalha(GameData &game, sf::RenderWindow &window);