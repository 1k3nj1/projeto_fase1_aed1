#pragma once

#include <SFML/Graphics.hpp>

namespace Pokemon
{
    class InputManager
    {
    public:
        InputManager() = default;
        ~InputManager() = default;

        bool IsSpriteClicked(
            const sf::Sprite& object,
            sf::Mouse::Button button,
            sf::RenderWindow& window
        );

        sf::Vector2i GetMousePosition(sf::RenderWindow& window);
    };
}