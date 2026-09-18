#pragma once

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

namespace Pokemon
{
    class AssetManager
    {
    public:
        AssetManager() = default;
        ~AssetManager() = default;

        void LoadTexture(
            const std::string& name,
            const std::string& fileName);

        sf::Texture& GetTexture(
            const std::string& name);

        void LoadFont(
            const std::string& name,
            const std::string& fileName);

        sf::Font& GetFont(const std::string& name);

    private:
        std::map<std::string, sf::Texture> _textures;
        std::map<std::string, sf::Font> _fonts;
    };
}