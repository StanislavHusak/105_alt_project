#pragma once

#include "Scene.h"
#include "Framework/Collision.h"
#include "Framework/TileMap.h"
#include "Player.h"
#include "Lever.h"
#include "Flag.h"
#include <algorithm>
#include <fstream>

class LevelLoader
{
public:
	LevelLoader();
	
	void draw(sf::RenderWindow& window);

	void MapSetup(std::string tileMapData, sf::Vector2u mapDimensions, int tile_size, int num_cols, int num_row, int sheet_spacing, std::string Texture);
    TileMap& getTileMap() { return m_tilemap; };
    void BackGroundSetup(std::string tileMapData, sf::Vector2u mapDimensions, int tile_size, int num_cols, int num_row, int sheet_spacing, std::string Texture);
    TileMap& getBgTileMap() { return m_bgtilemap; };

private:
    void updateCameraAndBackground();

    TileMap m_tilemap;
    TileMap m_bgtilemap;
    sf::Texture m_tileTexture;

    Player m_player;
    Lever m_lever;
    /*sf::Text m_alertText;
    sf::Font m_font;*/
    std::vector<Flag*> m_flags;
    bool m_flagLeverPulled = false;
    float m_promptTimer;

    const float PROMPT_TIME = 2.f;
    const sf::Vector2i WORLD_SIZE = { 2880, 648 };
    const sf::Vector2i VIEW_SIZE = { 432, 432 };

};

