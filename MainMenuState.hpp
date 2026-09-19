#pragma once

#include <iostream>
#include <optional>
#include <SFML/Graphics.hpp>

#include "State.hpp"
#include "Game.hpp"

namespace Pokemon
{
    class MainMenuState : public State
    {
    public:
        MainMenuState(GameDataRef data);

        void Init();

        void HandleInput();
        void Update(float dt);
        void Draw(float dt);

    private:
        GameDataRef _data;

        std::optional<sf::Sprite> _background;
        std::optional<sf::Sprite> _gameTitle;
        std::optional<sf::Sprite> _playButton;
    };
}