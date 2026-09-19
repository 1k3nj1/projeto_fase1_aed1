#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"

namespace Pokemon
{
    MainMenuState::MainMenuState(GameDataRef data)
        : _data(data)
    {
    }

    void MainMenuState::Init()
    {
        this->_data->assets.LoadTexture("Main Menu Background",MAIN_MENU_BACKGROUND_FILEPATH);

        this->_data->assets.LoadTexture("Game Title",GAME_TITLE_FILEPATH);

        this->_data->assets.LoadTexture("Play Button",PLAY_BUTTON_FILEPATH);

        this->_background.emplace(this->_data->assets.GetTexture("Main Menu Background"));

        this->_gameTitle.emplace(this->_data->assets.GetTexture("Game Title"));

        this->_playButton.emplace(this->_data->assets.GetTexture("Play Button"));

        float titleX = (SCREEN_WIDTH / 2.f) - (this->_gameTitle->getGlobalBounds().size.x / 2.f);

        float titleY = this->_gameTitle->getGlobalBounds().size.y * 0.1f;

        this->_gameTitle->setPosition({titleX, titleY});


        float buttonX = (SCREEN_WIDTH / 2.f) - (this->_playButton->getGlobalBounds().size.x / 2.f);

        float buttonY = (SCREEN_HEIGHT / 2.f) - (this->_playButton->getGlobalBounds().size.y / 2.f);

        this->_playButton->setPosition({buttonX, buttonY});
    }
    void MainMenuState::HandleInput()
    {
        while (const std::optional event = this->_data->window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                this->_data->window.close();
            }

            if (this->_playButton && this->_data->input.IsSpriteClicked(*this->_playButton, sf::Mouse::Button::Left,
                                         this->_data->window))
            {
                std::cout << "Play button clicked" << std::endl;
            }
            }
    }

    void MainMenuState::Update(float dt)
    {
    }

    void MainMenuState::Draw(float dt)
    {
        this->_data->window.clear();

        if (this->_background)
        {
            this->_data->window.draw(*this->_background);
        }

        if (this->_gameTitle)
        {
            this->_data->window.draw(*this->_gameTitle);
        }

        if (this->_playButton)
        {
            this->_data->window.draw(*this->_playButton);
        }

        this->_data->window.display();
    }
}