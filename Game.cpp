#include "InputManager.hpp"

namespace Pokemon
{
    bool InputManager::IsSpriteClicked(
        const sf::Sprite& object,
        sf::Mouse::Button button,
        sf::RenderWindow& window
    )
    {
        if (sf::Mouse::isButtonPressed(button))
        {
            sf::Vector2f mousePosition =
                window.mapPixelToCoords(
                    sf::Mouse::getPosition(window)
                );

            return object.getGlobalBounds().contains(mousePosition);
        }

        return false;
    }

    sf::Vector2i InputManager::GetMousePosition(
        sf::RenderWindow& window)
    {
        return sf::Mouse::getPosition(window);
    }
}