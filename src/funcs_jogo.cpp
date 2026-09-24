#include "funcs_jogo.hpp"

int calculaVantagem(int tipoA, int tipoB) {
    if (tipoA == FOGO && tipoB == PLANTA) return 1;
    if (tipoA == PLANTA && tipoB == AGUA) return 1;
    if (tipoA == AGUA && tipoB == FOGO) return 1;
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

void Botao::desenhar(sf::RenderWindow& window) const {
    window.draw(box);
    window.draw(texto);
}