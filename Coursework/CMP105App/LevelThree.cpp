#include "LevelThree.h"
#include <iostream>

LevelThree::LevelThree(sf::RenderWindow& window, Input& input, GameState& gameState, AudioManager& audio)
    : Scene(window, input, gameState, audio),
    m_levelLoader(window, input, gameState, audio, m_player),
    m_alertText(m_font)
{
    m_levelLoader.setLevelState(State::LEVELTREE);
    m_levelLoader.setLeaderboard("data/Level3_leaderboard.txt");

    // TILEMAP (100 x 8)
    m_levelLoader.TileMapSetup("data/TilemapLevel3.txt", { 100, 8 }, 18, 20, 9, 1, "gfx/tilemap.png");
    m_levelLoader.BgTileMapSetup("data/TilemapBackgroundLevel3.txt", { 14, 5 }, 24, 8, 3, 1, "gfx/tilemap-backgrounds.png");

    // PLAYER
    m_player.setInput(&m_input);
    m_player.setEdges(0, WORLD_SIZE.x);
    m_player.setPosition({ 72 * 2, 72 * 5 }); // spawn zone
    m_player.setAudio(&m_audio);

    m_spawnPoint = m_player.getPosition();

    // FONT
    if (!m_font.openFromFile("font/bitcount.ttf"))
        std::cerr << "font missing\n";

    m_alertText.setFont(m_font);
    m_alertText.setCharacterSize(24);
    m_alertText.setFillColor(sf::Color::Black);

    // TILE TEXTURE
    if (!m_tileTexture.loadFromFile("gfx/tilemap.png"))
        std::cerr << "tile missing\n";

    m_boopBlock.setTexture(&m_tileTexture);
    m_boopBlock.setSize({ 72, 72 });
    m_boopBlock.setPosition({ 72 * 20, 72 * 4 });
    m_boopBlock.setAlive(true);
    m_boopBlock.setCollisionBox({ {0,0}, {72,72} });

    m_switch.setTexture(&m_tileTexture);
    m_switch.setSize({ 72, 72 });
    m_switch.setPosition({ 72 * 60, 72 * 4 });

    m_gate.setTexture(&m_tileTexture);
    m_gate.setSize({ 72, 144 });
    m_gate.setPosition({ 72 * 70, 72 * 3 });

    // GREMLINS
    m_levelLoader.SetupGremlins("data/GremlinsLevel3.txt");
}

void LevelThree::onBegin()
{
    std::cout << "Level 3 start\n";
    m_audio.playMusicbyName("bgm2");

    m_boopActivated = false;
    m_switchActivated = false;
}

void LevelThree::onEnd()
{
    std::cout << "Level 3 end\n";
    m_player.reset();
    m_audio.stopAllMusic();
    m_audio.stopAllSounds();
}

void LevelThree::handleInput(float dt)
{
    m_levelLoader.handleInput(dt);
}

void LevelThree::update(float dt)
{
    m_levelLoader.update(dt);
    m_levelLoader.updateCameraAndBackground(WORLD_SIZE, VIEW_SIZE);


    if (m_boopBlock.isAlive())
    {
        if (Collision::checkBoundingBox(m_player, m_boopBlock))
        {
            if (m_player.getPosition().y >= m_boopBlock.getPosition().y)
            {
                m_boopActivated = true;
                m_boopBlock.setAlive(false);
            }
            m_player.collisionResponse(m_boopBlock);
        }
    }

    if (m_switchActivated == false &&
        (m_player.getPosition() - m_switch.getPosition()).length() < 80 &&
        m_input.isPressed(sf::Keyboard::Scancode::F))
    {
        m_switchActivated = true;
    }

    // unlock gate
    if (m_switchActivated)
    {
        m_gate.setPosition({ 9999, 9999 }); // simple removal
    }

    if (!m_boopActivated &&
        (m_player.getPosition() - m_boopBlock.getPosition()).length() < 150)
    {
        m_alertText.setString("Hit the block from below");
        m_alertText.setPosition(m_window.getView().getCenter() + sf::Vector2f(-120, -150));
    }
    else if (!m_switchActivated &&
        (m_player.getPosition() - m_switch.getPosition()).length() < 150)
    {
        m_alertText.setString("Press F to activate switch");
        m_alertText.setPosition(m_window.getView().getCenter() + sf::Vector2f(-140, -150));
    }
    else
    {
        if (m_promptTimer > 0) m_promptTimer -= dt;
        else m_alertText.setString("");
    }
}

void LevelThree::render()
{
    beginDraw();

    m_levelLoader.render();

    if (m_boopBlock.isAlive())
        m_window.draw(m_boopBlock);

    m_window.draw(m_switch);

    if (m_gate.getPosition().x < 9000)
        m_window.draw(m_gate);

    m_window.draw(m_player);
    m_window.draw(m_alertText);

    m_levelLoader.drawUI();

    endDraw();
}