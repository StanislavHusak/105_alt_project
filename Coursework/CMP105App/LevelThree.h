#pragma once
#include "Scene.h"
#include "LevelLoader.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

class LevelThree : public Scene
{
public:
    LevelThree(sf::RenderWindow& window, Input& input, GameState& gameState, AudioManager& audio);

    void handleInput(float dt) override;
    void update(float dt) override;
    void render() override;

    void onBegin() override;
    void onEnd() override;

private:
    LevelLoader m_levelLoader;
    Player m_player;

    sf::Font m_font;
    sf::Text m_alertText;

    sf::Texture m_tileTexture;

    GameObject m_boopBlock;
    GameObject m_switch;
    GameObject m_gate;

    sf::Vector2f m_spawnPoint;

    bool m_boopActivated = false;
    bool m_switchActivated = false;

    float m_promptTimer = 0.f;
    const float PROMPT_TIME = 3.f;

    const sf::Vector2i WORLD_SIZE = { 7000, 576 };
    const sf::Vector2i VIEW_SIZE = { 432, 432 };
};

