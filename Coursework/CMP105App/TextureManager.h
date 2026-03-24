#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>


class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	void loadTexture(std::string& name, std::string& filename);

	sf::Texture getTexture(std::string& name);

private:
	std::map<std::string, sf::Texture> m_textures;
};

