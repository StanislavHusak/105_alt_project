#include "TextureManager.h"

TextureManager::TextureManager() {

}

TextureManager::~TextureManager() {

}

void TextureManager::loadTexture(std::string& name, std::string& filename) {


	if (m_textures.find(name) != m_textures.end()) {
		std::cerr << "Texture alredy loaded: " << name << std::endl;
		return;
	}
	sf::Texture texture;
	
	if (texture.loadFromFile(filename)) {
		std::cerr << "Failed to load texture: " << name << std::endl;
		return;
	}

	m_textures.emplace(name, texture);
}


sf::Texture TextureManager::getTexture(std::string& name) {
	auto it = m_textures.find(name);

	if (it == m_textures.end()) {
		std::cerr << "ERROR: Texture not found: " << name << std::endl;
	}

	return it->second;
}