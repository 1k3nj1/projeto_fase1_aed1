#include <iostream>
#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "src/funcs_jogo.hpp"

/*
    g++ main.cpp src/funcs_jogo.cpp src/Fila.cpp src/PokemonEntity.cpp -o app -lsfml-graphics -lsfml-window -lsfml-system
    ./app
*/

int main() {
    srand(time(nullptr));

    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Pokemon Fila emulator", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    window.setView(sf::View(sf::FloatRect({0.f, 0.f}, {static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT)})));

    GameData game;

    // Fonte temporária (ou não)
    if (!game.fonte.openFromFile("src/arial.ttf")) {
        std::cerr << "Erro ao carregar fonte em src/arial.ttf!\n";
    }

    // Criando botões
    Botao btn_continuar({500.f, 500.f}, {220.f, 50.f}, "Ir para captura", game.fonte);
    Botao btn_capturar({400.f, 550.f}, {150.f, 50.f}, "Capturar", game.fonte);
    Botao btn_pular({650.f, 550.f}, {150.f, 50.f}, "Pular", game.fonte);


    // Carrega tela inicial
    if (game.splash_textura.loadFromFile(CAMINHO_IMAGEM)) {
        game.splash_sprite.setTexture(game.splash_textura, true);
        auto sz = game.splash_textura.getSize();
        game.splash_sprite.setScale({static_cast<float>(SCREEN_WIDTH) / sz.x, static_cast<float>(SCREEN_HEIGHT) / sz.y});
    }

    sf::Clock relogio;

    while (window.isOpen()) {
        
        // verificando pressionar o close
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // Passar mais de 3 segundos e prosseguir da tela inicial
        if (game.estado_atual == Estado::TELA_INICIAL) {
            if (relogio.getElapsedTime().asSeconds() >= 3.0f) {
                game.estado_atual = Estado::ESCOLHA;
            }
        } 

        // limpando o frame anterior
        window.clear(sf::Color(30, 30, 30));

        switch (game.estado_atual) {
            case Estado::TELA_INICIAL:
                window.draw(game.splash_sprite);
                break;
        }

        window.display();
    }

    return 0;
}