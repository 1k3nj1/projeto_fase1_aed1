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

    carregar_dex(game);
    randomiza_fila(game);

    Fila random_escolha(6);
    randomiza_fila_escolha(game, random_escolha);

    // Fonte temporária (ou não)
    if (!game.fonte.openFromFile("src/arial.ttf")) {
        std::cerr << "Erro ao carregar fonte em src/arial.ttf!\n";
    }

    // Criando botões
    Botao btn_comecar({500.f, 500.f}, {220.f, 50.f}, "Play", game.fonte);
    Botao btn_continuar({500.f, 600.f}, {220.f, 50.f}, "Ir para captura", game.fonte);
    Botao btn_capturar({400.f, 600.f}, {150.f, 50.f}, "Capturar", game.fonte);
    Botao btn_pular({650.f, 600.f}, {150.f, 50.f}, "Pular", game.fonte);


    // Carrega tela inicial
    if (game.splash_textura.loadFromFile(CAMINHO_IMAGEM)) {
        game.splash_sprite.setTexture(game.splash_textura, true);
        auto sz = game.splash_textura.getSize();
        game.splash_sprite.setScale({static_cast<float>(SCREEN_WIDTH) / sz.x, static_cast<float>(SCREEN_HEIGHT) / sz.y});
    }

    sf::Clock relogio;

    while(window.isOpen()) {
        
        // verificando pressionar o close
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    if(game.estado_atual == Estado::MENU && btn_comecar.clicado(window)){
                        std::cout << "Botao de play clicado" << std::endl;
                        game.estado_atual = Estado::VER_TIME_PC;
                    }

                    else if(game.estado_atual == Estado::VER_TIME_PC && btn_continuar.clicado(window)){
                        std::cout << "Botao de continuar clicado" << std::endl;
                        game.estado_atual = Estado::ESCOLHA;
                    }

                    else if(game.estado_atual == Estado::ESCOLHA){
                        if(btn_capturar.clicado(window)){
                            PokemonEntity aux1;
                            bool baux1;

                            random_escolha.desenfileira(&aux1, &baux1);
                            game.fila_jogador.enfileira(aux1, &baux1);

                            if(game.fila_jogador.cheia()){
                                game.estado_atual = Estado::BATALHA;
                            }

                            std::cout << "Botao de captura clicado" << std::endl;

                        }

                        if(btn_pular.clicado(window)){
                            PokemonEntity aux2;
                            bool baux2;

                            random_escolha.desenfileira(&aux2, &baux2); 
                            std::cout << "Botao de pular clicado" << std::endl;
                        }
                    }

                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << mouseButtonPressed->position.x << std::endl;
                    std::cout << "mouse y: " << mouseButtonPressed->position.y << std::endl;
                }
            }
        }

        // Passar mais de 3 segundos e prosseguir da tela inicial
        if (game.estado_atual == Estado::TELA_INICIAL) {
            if (relogio.getElapsedTime().asSeconds() >= 3.0f) {
                game.estado_atual = Estado::MENU;
            }
        }

        if(game.estado_atual == Estado::MENU){
            if (game.textura_atual.loadFromFile(CAMINHO_TELA_MENU)) {
                game.sprite_atual.setTexture(game.textura_atual, true);
                auto sz = game.textura_atual.getSize();
                game.sprite_atual.setScale({static_cast<float>(SCREEN_WIDTH) / sz.x, static_cast<float>(SCREEN_HEIGHT) / sz.y});
            }
        }

        /*
        
        if(game.estado_atual == Estado::VER_TIME_PC){
            
        }
        */

        // limpando o frame anterior
        window.clear(sf::Color(30, 30, 30));
        bool mostrou = false;

        switch (game.estado_atual) {
            case Estado::TELA_INICIAL:
                window.draw(game.splash_sprite);
                break;
            
            case Estado::MENU:
                window.draw(game.sprite_atual);
                btn_comecar.desenhar(window);
                break;
            
            case Estado::VER_TIME_PC:
                if(!mostrou){
                    exibir_time_pc(game, window);
                    mostrou = true;
                }

                btn_continuar.desenhar(window);
                break;
            
            case Estado::ESCOLHA: {
                PokemonEntity paux;
                bool baux;

                if(random_escolha.vazia()){
                    randomiza_fila_escolha(game, random_escolha);
                }

                if(!game.fila_jogador.cheia()){
                    random_escolha.pegaPrimeiro(paux);
                }


                sf::Text nome_p(game.fonte, paux.get_nome());
                nome_p.setPosition({600.f, 100.f});
                game.textura_atual.loadFromFile(paux.get_imagem());

                if(paux.get_tipo() == TipoPokemon::FOGO){
                    nome_p.setFillColor(sf::Color(255, 0, 0));
                }

                if(paux.get_tipo() == TipoPokemon::PLANTA){
                    nome_p.setFillColor(sf::Color(0, 255, 0));
                }

                if(paux.get_tipo() == TipoPokemon::AGUA){
                    nome_p.setFillColor(sf::Color(0, 0, 255));
                }

                game.sprite_atual.setTexture(game.textura_atual);
                game.sprite_atual.setPosition({500.f, 150.f});
                auto sz = game.textura_atual.getSize();
                game.sprite_atual.setScale({static_cast<float>(300) / sz.x, static_cast<float>(300) / sz.y});
            
                btn_capturar.desenhar(window);
                btn_pular.desenhar(window);
                window.draw(game.sprite_atual);
                window.draw(nome_p);
                break;
            }
            case Estado::BATALHA: {
                game.fila_jogador.pegaPrimeiro(game.poke_atual_jogador);
                game.fila_PC.pegaPrimeiro(game.poke_atual_PC);
                
                sf::Texture poke_jogador_texture;
                sf::Texture poke_pc_texture;

                poke_jogador_texture.loadFromFile(game.poke_atual_jogador.get_imagem());
                poke_pc_texture.loadFromFile(game.poke_atual_jogador.get_imagem());

                sf::Sprite poke_jogador_sprite(poke_jogador_texture);
                sf::Sprite poke_pc_sprite(poke_pc_texture);

                poke_jogador_sprite.setPosition({200.f, 500.f});
                poke_pc_sprite.setPosition({400.f, 500.f});

                // Aqui precisa escalar as imagens dos pokemons

                window.draw(poke_jogador_sprite);
                window.draw(poke_pc_sprite);

                break;
            }
        }

        window.display();
    }

    return 0;
}