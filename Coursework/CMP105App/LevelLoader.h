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

    void draw(sf::RenderWindow& window, State state);
    void PausebuttonsInput(Input& input, GameState& gameState);


    
    void TileMapSetup(TileMap& tilemap, std::string tileMapData, sf::Vector2u mapDimensions, int tile_size, int scaling, int num_columns, int num_rows, int sheet_spacing, std::string Texture);
    void UI_Object(GameObject& Gameobject,sf::Vector2f size, sf::Vector2f position, sf::Color color);
    void UI_Text(sf::Text& textObj, int characterSize, sf::Vector2f position, std::string text, sf::Color color);

    TileMap& getTileMap() { return m_tilemap; }
    TileMap& getBGTilemap() { return m_bgtilemap; }



private:
    void updateCameraAndBackground();


    sf::Font m_font;
    sf::Color m_defaultButtonColour = sf::Color::White ;


    //Map and Backgraund
    TileMap m_tilemap;
    TileMap m_bgtilemap;

    //Pause Menu
    GameObject m_PausePanel;

    GameObject m_resumeButton;
    sf::Text m_resumeButtonLabel;
    GameObject m_menuButton;
    sf::Text m_menuButtonLabel;
};

