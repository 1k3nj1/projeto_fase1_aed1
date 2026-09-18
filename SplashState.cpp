#include <sstream>
#include "SplashState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace Pokemon
{
    SplashState::SplashState( GameDataRef data) : _data(data)
    {
    }
    void SplashState::Init()
{
    this->_data->assets.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);

    this->_background.emplace(this->_data->assets.GetTexture("Splash State Background"));
}
    
    void SplashState::HandleInput()
    {
        while (const std::optional event = this->_data->window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                this->_data->window.close();
            }
        }
    }
    void SplashState::Update( float dt)
    {
        if(this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
        {
            std::cout << "Go to main Menu" << std::endl;
        }

    }
   void SplashState::Draw(float dt)
{
    this->_data->window.clear();

    if (this->_background)
    {
        this->_data->window.draw(*this->_background);
    }

    this->_data->window.display();
}
}