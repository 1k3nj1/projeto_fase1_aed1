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

    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Pokemon Fila simulator", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    window.setView(sf::View(sf::FloatRect({0.f, 0.f}, {static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT)})));

    GameData game;

    carregar_dex(game);
    bool ja_randomizou = false;
    // randomiza_fila(game);

    Fila random_escolha(QTD_POKEMONS);
    Fila time_jogador_aux(TAMANHO_TIMES);
    // randomiza_fila_escolha(game, random_escolha);

    // Fonte temporária (ou não)
    if (!game.fonte.openFromFile("src/arial.ttf")) {
        std::cerr << "Erro ao carregar fonte em src/arial.ttf!\n";
    }

    // Criando botões
    Botao btn_batalhar({540.f, 600.f}, {150.f, 50.f}, "Batalhar", game.fonte);
    Botao btn_resultado({500.f, 400.f}, {220.f, 50.f}, "Resultado", game.fonte);
    Botao btn_comecar({500.f, 500.f}, {220.f, 50.f}, "Play", game.fonte);
    Botao btn_continuar({500.f, 600.f}, {220.f, 50.f}, "Ir para captura", game.fonte);
    Botao btn_capturar({400.f, 600.f}, {150.f, 50.f}, "Capturar", game.fonte);
    Botao btn_pular({650.f, 600.f}, {150.f, 50.f}, "Pular", game.fonte);
    Botao btn_terminar({350.f, 600.f}, {150.f, 50.f}, "Terminar", game.fonte);
    Botao btn_continuar_jogando({750.f, 600.f}, {150.f, 50.f}, "Continuar", game.fonte);
    Botao btn_proxima_batalha({500.f, 600.f}, {220.f, 50.f}, "Proxima Batalha", game.fonte);

    // Carrega tela inicial
    if (game.splash_textura.loadFromFile(CAMINHO_TELA_INICIAL)) {
        game.splash_sprite.setTexture(game.splash_textura, true);
        auto sz = game.splash_textura.getSize();
        game.splash_sprite.setScale({static_cast<float>(SCREEN_WIDTH) / sz.x, static_cast<float>(SCREEN_HEIGHT) / sz.y});
    }
    
    sf::Clock relogio;
    sf::Clock timer_batalha;
    bool batalhou = false;

    while(window.isOpen()) {
        bool mostrou = false;
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
                    else if(game.estado_atual == Estado::BATALHA && btn_batalhar.clicado(window)){
                        std::cout << "Botao de batalhar clicado" << std::endl;

                        if(!batalhou){
                            calcular_resultado_batalha(game);
                        }

                        timer_batalha.restart();
                        batalhou = true;
                    }
                    else if(game.estado_atual == Estado::BATALHA && btn_resultado.clicado(window)){
                        game.estado_atual = Estado::TELA_FINAL;
                        game.pontuacao_combate.setString("" + std::to_string(game.pontos_jogador) + " X " + std::to_string(game.pontos_PC));
                        game.pontuacao_combate.setPosition({530.f, 300.f});
                        game.pontuacao_combate.setScale({3.f, 3.f});
                        calcular_resultado_combate(game);
                    }
                    else if(game.estado_atual == Estado::TELA_FINAL){
                        game.pontos_jogador = 0;
                        game.pontos_PC = 0;

                        if(btn_terminar.clicado(window)){
                            ja_randomizou = false;
                            game.estado_atual = Estado::MENU;
                        }

                        if(btn_continuar_jogando.clicado(window)){
                            mostrou = false;
                            /*while(!time_jogador_aux.vazia()){
                                PokemonEntity aux;
                                bool baux;

                                time_jogador_aux.desenfileira(&aux, &baux);
                                game.fila_jogador.enfileira(aux, &baux);
                            }
                            */
                            randomiza_fila_pc(game);
                            randomiza_fila_escolha(game, random_escolha);
                            game.estado_atual = Estado::VER_TIME_PC;
                        }

                    }
                    else if(game.estado_atual == Estado::VER_TIME_JOGADOR && btn_proxima_batalha.clicado(window)){
                        game.estado_atual = Estado::VER_TIME_PC;
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

            if(!ja_randomizou){
                randomiza_fila_pc(game);
                randomiza_fila_escolha(game, random_escolha);
                ja_randomizou = true;
            }
        }

        if(game.estado_atual == Estado::BATALHA){
            if (game.textura_atual.loadFromFile(CAMINHO_TELA_BATALHA)) {
                game.sprite_atual.setTexture(game.textura_atual, true);
                auto sz = game.textura_atual.getSize();
                game.sprite_atual.setScale({static_cast<float>(SCREEN_WIDTH) / sz.x, static_cast<float>(SCREEN_HEIGHT) / sz.y});
            }
        }
        
        /*
        if(game.estado_atual == Estado::TELA_FINAL){
            if (game.textura_atual.loadFromFile(CAMINHO_TELA_FINAL)) {
                game.sprite_atual.setTexture(game.textura_atual, true);
                auto sz = game.textura_atual.getSize();
                game.sprite_atual.setScale({static_cast<float>(SCREEN_WIDTH) / sz.x, static_cast<float>(SCREEN_HEIGHT) / sz.y});
            }
        }
        */

        // limpando o frame anterior
        window.clear(sf::Color(30, 30, 30));

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
                    sf::Text texto_titulo(game.fonte, "TIME DO OPONENTE");
                    texto_titulo.setPosition({300.f, 100.f});
                    texto_titulo.setScale({2.f, 2.f});
                    window.draw(texto_titulo);
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

                //if(!game.fila_jogador.cheia()){
                    random_escolha.pegaPrimeiro(paux);
                //}

                sf::Text nome_p(game.fonte, paux.get_nome());
                nome_p.setPosition({600.f, 100.f});
                game.textura_atual.loadFromFile(paux.get_imagem());

                adicionar_tipo(paux, nome_p);

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
                game.sprite_atual.setPosition({0.0, 0.0});
                window.draw(game.sprite_atual);

                PokemonEntity aux2;
                bool baux2;
                if(!game.fila_jogador.vazia()){

                    game.fila_jogador.pegaPrimeiro(game.poke_atual_jogador);
                    game.fila_PC.pegaPrimeiro(game.poke_atual_PC);
                    
                    sf::Texture poke_jogador_texture;
                    sf::Texture poke_pc_texture;

                    sf::Text poke_jogador_nome(game.fonte, game.poke_atual_jogador.get_nome());
                    sf::Text poke_pc_nome(game.fonte, game.poke_atual_PC.get_nome());

                    poke_jogador_texture.loadFromFile(game.poke_atual_jogador.get_imagem());
                    poke_pc_texture.loadFromFile(game.poke_atual_PC.get_imagem());

                    sf::Sprite poke_jogador_sprite(poke_jogador_texture);
                    sf::Sprite poke_pc_sprite(poke_pc_texture);

                    poke_jogador_sprite.setPosition({300.f, 350.f});
                    poke_pc_sprite.setPosition({720.f, 150.f});

                    // Aqui precisa escalar as imagens dos pokemons
                    auto sz_jogador = poke_jogador_texture.getSize();
                    auto sz_pc = poke_pc_texture.getSize();

                    poke_jogador_sprite.setScale({static_cast<float>(250) / sz_jogador.x, static_cast<float>(250) / sz_jogador.y});
                    poke_pc_sprite.setScale({static_cast<float>(250) / sz_pc.x, static_cast<float>(250) / sz_pc.y});
                    
                    adicionar_tipo(game.poke_atual_jogador, poke_jogador_nome);
                    adicionar_tipo(game.poke_atual_PC, poke_pc_nome);

                    poke_jogador_nome.setPosition({360.f, 600.f});
                    poke_pc_nome.setPosition({780.f, 400.f});

                    btn_batalhar.desenhar(window);
                    window.draw(poke_jogador_sprite);
                    window.draw(poke_pc_sprite);
                    window.draw(poke_jogador_nome);
                    window.draw(poke_pc_nome);

                    if(batalhou){
                        float tempo = timer_batalha.getElapsedTime().asSeconds();

                        std::cout << "Tempo: " << tempo << std::endl;

                        window.draw(game.resultado_batalha);

                        if(tempo >= 1.5f){
                            std::cout << "PASSOU DOS 1.5 SEGUNDOS!" << std::endl;
                            game.fila_jogador.desenfileira(&aux2, &baux2);
                            time_jogador_aux.enfileira(aux2, &baux2);
                            game.fila_PC.desenfileira(&aux2, &baux2);
                            batalhou = false;
                        }
                    }

                } else {
                    btn_resultado.desenhar(window);
                }
                    break;
            }

            case Estado::TELA_FINAL: {
                /*
                game.sprite_atual.setPosition({0.0, 0.0});
                window.draw(game.sprite_atual);
                */

                std::cout << "Tela final" << std::endl;
                window.draw(game.resultado_batalha);
                window.draw(game.pontuacao_combate);
                btn_terminar.desenhar(window);
                btn_continuar_jogando.desenhar(window);
                break;
            }

            case Estado::VER_TIME_JOGADOR:{
                if(!mostrou){
                    sf::Text texto_titulo(game.fonte, "SEU TIME");
                    texto_titulo.setPosition({500.f, 100.f});
                    texto_titulo.setScale({2.f, 2.f});
                    window.draw(texto_titulo);
                    exibir_time_jogador(game, window);
                    mostrou = true;
                }
                btn_proxima_batalha.desenhar(window);
            }
            break;
        }

        window.display();
    }

    return 0;
}
