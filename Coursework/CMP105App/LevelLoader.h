#pragma once

#include "Scene.h"
#include "Checkpoints.h"
#include "Framework/Collision.h"
#include "Framework/TileMap.h"
#include "Player.h"
#include "Lever.h"
#include "Flag.h"
#include <algorithm>
#include <fstream>
#include "Spanner.h"
#include "Gremlin.h"
#include "Leaderboard.h"

class LevelLoader : public BaseLevel
{
public:
	LevelLoader(sf::RenderWindow& window, Input& input, GameState& gameState, AudioManager& audio, Player& player);

    void drawUI();
    void handleInput(float dt) override;
    void update(float dt) override;
    void render() override;

    void reset();

    void SetUpLivesInScene();
    void SetUpCheckPoints(std::string filename);

    
    void TileMapSetup(std::string tileMapData, sf::Vector2u mapDimensions, int tile_size, int num_columns, int num_rows, int sheet_spacing, std::string Texture);
    void BgTileMapSetup(std::string tileMapData, sf::Vector2u mapDimensions, int tile_size, int num_columns, int num_rows, int sheet_spacing, std::string Texture);
    void SetupGremlins(std::string filename);

    GameObject UI_Object(sf::Vector2f size, sf::Vector2f position, sf::Color color);
    sf::Text UI_Text( int characterSize, sf::Vector2f position, std::string text, sf::Color color);

    TileMap& getTileMap() { return m_tilemap; }
    TileMap& getBGTilemap() { return m_bgtilemap; }

    void updateCameraAndBackground(sf::Vector2i WORLD_SIZE, sf::Vector2i VIEW_SIZE);

    void setLevelState(State state) { m_stateLevel = state; };

    

private:
    //Timer and leaderboard
    float m_timer = 0.f;
    bool m_isTimer;

    Leaderboard m_leaderboard;

    sf::Text m_timerText;
    sf::Text m_leaderboardText;
    GameObject m_leaderboardPanel;

    sf::Font m_font;
    sf::Color m_defaultButtonColour = sf::Color::White ;

    //UI Lives
    std::vector<GameObject> m_lives;

    //Map and Backgraund
    TileMap m_tilemap;
    TileMap m_bgtilemap;
    std::string m_tileMapData, m_bgtileMapData;

    //pause, gameover, win Menu
    sf::Text m_maineText;

    GameObject m_Panel;

    GameObject m_restartButton;
    sf::Text m_restartButtonLabel;
    GameObject m_resumeButton;
    sf::Text m_resumeButtonLabel;
    GameObject m_menuButton;
    sf::Text m_menuButtonLabel;

    State m_stateLevel;

    //Leader board



    //Player
    Player& m_player;

    //Spanner
    std::vector<Spanner> m_spanners;
    bool m_isSpannerActive;
    float m_timerCoulDownSpaner;
    float m_coulDownSpaner = 1.f;

    //Grimlins
    std::vector<Gremlin> m_grimlins;

    std::vector<Checkpoints> m_Checkpoints;
};

