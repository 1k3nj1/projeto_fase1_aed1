#include "InputManager.hpp"

namespace Pokemon
{
    bool InputManager::IsSpriteClicked( const sf::Sprite& object, sf::Mouse::Button button,
            sf::RenderWindow& window)
    {
        if (sf::Mouse::isButtonPressed(button))
        {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

            sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);

            return object.getGlobalBounds().contains(worldPosition);
        }

        return false;
    }

    sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& window)
    {
        return sf::Mouse::getPosition(window);
    }
}