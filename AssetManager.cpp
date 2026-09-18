#include "AssetManager.hpp"

#include <utility>

namespace Pokemon
{
    void AssetManager::LoadTexture(
        const std::string& name,
        const std::string& fileName)
    {
        sf::Texture texture;

        if (texture.loadFromFile(fileName))
        {
            this->_textures[name] = std::move(texture);
        }
    }

    sf::Texture& AssetManager::GetTexture(
        const std::string& name)
    {
        return this->_textures.at(name);
    }

    void AssetManager::LoadFont(
        const std::string& name,
        const std::string& fileName)
    {
        sf::Font font;

        if (font.openFromFile(fileName))
        {
            this->_fonts[name] = std::move(font);
        }
    }

    sf::Font& AssetManager::GetFont(
        const std::string& name)
    {
        return this->_fonts.at(name);
    }
}