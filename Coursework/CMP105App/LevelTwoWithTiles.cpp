#include "LevelTwoWithTiles.h"

LevelTwoWithTiles::LevelTwoWithTiles(sf::RenderWindow& window, Input& input, GameState& gameState, AudioManager& audio)
	: Scene(window, input, gameState, audio), m_levelLoader(window, input, gameState, audio, m_player), m_alertText(m_font)
{
	m_levelLoader.setLeaderboard("Level2Leaderboard.txt");
	m_levelLoader.setLevelState(State::LEVELTWO);

	m_levelLoader.TileMapSetup("data/TilemapLevel2.txt", {40, 8}, 18, 20, 9, 1,"gfx/tilemap.png");
	m_levelLoader.BgTileMapSetup("data/TilemapBackgroundLevel2.txt", {14, 5}, 24, 8, 3, 1,"gfx/tilemap-backgrounds.png");
	
	m_levelLoader.SetupGremlins("data/GremlinsPosition.txt");
	m_levelLoader.SetUpCheckPoints("data/Level2_CheckpointsPosition.txt");

	// setup player 
	m_player.setInput(&m_input);
	m_player.setEdges(0, WORLD_SIZE.x);
	m_player.setPosition({ 100, 100 });
	m_player.setAudio(&m_audio);

	// other bits
	sf::Vector2f boop_location = { 100, 72 * 2 + 100 };

	if (!m_tileTexture.loadFromFile("gfx/tilemap.png")) std::cerr << "failed to find tile images";
	m_coin.setTexture(&m_tileTexture);
	m_coin.setPosition(boop_location);
	m_coin.setSize({ 72,72 });
	m_coin.setAlive(false);
	m_coin.setCollisionBox({ { 0,0 }, { 72,72 } });

	m_boopBlock.setTexture(&m_tileTexture);
	m_boopBlock.setTextureRect({ {10 * 19,0}, { 18,18 } });
	m_boopBlock.setAlive(false);
	m_boopBlock.setCollisionBox({ { 0,0 }, { 72,72 } });
	m_boopBlock.setPosition(boop_location);
	m_boopBlock.setSize({ 72, 72 });

	m_flag.setPosition({ 38 * 72, 6 * 77 });
	m_flag.setSize({ 72,72 });
	m_flag.setTexture(&m_tileTexture);

	if (!m_font.openFromFile("font/bitcount.ttf")) std::cerr << "no font found";
	m_alertText.setPosition({ 50, 150 });
	m_alertText.setCharacterSize(36);
	m_alertText.setFillColor(sf::Color::Black);

	

}

void LevelTwoWithTiles::onBegin()
{
	m_boopBlock.setAlive(false);
	m_coin.setAlive(false);
	m_player.setPosition({ 100, 100 });
	m_audio.playMusicbyName("bgm3");
}

void LevelTwoWithTiles::onEnd()
{
	// reset player
	m_player.setCanDoubleJump(false);
	// sfx
	m_audio.stopAllSounds();
	m_audio.stopAllMusic();
}

void LevelTwoWithTiles::handleInput(float dt)
{
	m_levelLoader.handleInput(dt);

	// if I press F on the flag  / I press escape.
	if (((m_flag.getPosition() - m_player.getPosition()).length() < 75 &&
		m_input.isPressed(sf::Keyboard::Scancode::F)))
	{
		m_player.setGameEndTriggered(true);
		m_boopBlock.setAlive(false);
	}
}
void LevelTwoWithTiles::update(float dt)
{


	m_levelLoader.update(dt);
	m_levelLoader.updateCameraAndBackground(WORLD_SIZE, VIEW_SIZE);

	m_flag.update(dt);
	if (m_coin.isAlive()) m_coin.update(dt);

	// handle collisions

	if (m_boopBlock.isAlive())
	{
		if (Collision::checkBoundingBox(m_player, m_boopBlock))
		{
			if (m_player.getPosition().y >= m_boopBlock.getPosition().y)
			{
				// if booped from below
				m_boopBlock.setAlive(false);
				m_coin.setAlive(true);
			}
			m_player.collisionResponse(m_boopBlock);

		}
	}

	if (m_coin.isAlive())
	{
		if (Collision::checkBoundingBox(m_player, m_coin))
		{
			m_coin.setAlive(false);
			m_player.setCanDoubleJump(true);
		}
	}

	// turn block on when at wall.
	if ((m_wallPos - m_player.getPosition()).length() < 75)
	{
		m_boopBlock.setAlive(true);
	}
	checkAndSetMessages();
}


// sets prompt text and position 
void LevelTwoWithTiles::checkAndSetMessages()
{
	// get position 25% in from top and left (get middle, half both dimensions)
	sf::Vector2f inner_top_left = m_window.getView().getCenter();
	sf::Vector2f window_size = { 
		static_cast<float>(m_window.getSize().x), 
		static_cast<float>(m_window.getSize().y) };
	inner_top_left -= window_size * 0.25f;
	// big wall 
	if (!m_player.canDoubleJump() && 
		(m_wallPos - m_player.getPosition()).length() < 75)
	{
		m_alertText.setCharacterSize(24);
		m_alertText.setPosition(inner_top_left);
		m_alertText.setString(m_promptMessages[0]);
		
	}
	// double jump unlocked
	else if (m_player.canDoubleJump() && 
		(m_boopBlock.getPosition() - m_player.getPosition()).length() < 150)
	{
		m_alertText.setCharacterSize(24);
		m_alertText.setPosition(inner_top_left);
		m_alertText.setString(m_promptMessages[1]);
	}

	// complete level
	else if ((m_flag.getPosition() - m_player.getPosition()).length() < 75)
	{
		m_alertText.setCharacterSize(24);
		m_alertText.setPosition(inner_top_left);
		m_alertText.setString(m_promptMessages[2]);
	}
	else
	{
		m_alertText.setPosition({ 0,-100 });
	}
}

void LevelTwoWithTiles::render()
{
	beginDraw();
	m_levelLoader.render();
	if (m_boopBlock.isAlive()) m_window.draw(m_boopBlock);
	m_window.draw(m_flag);
	m_window.draw(m_player);
	if (m_coin.isAlive()) m_window.draw(m_coin);
	m_window.draw(m_alertText);

	m_levelLoader.drawUI();
	endDraw();
}