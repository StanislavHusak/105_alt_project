#include "LevelLoader.h"

LevelLoader::LevelLoader(sf::RenderWindow& window, Input& input, GameState& gameState, AudioManager& audio, Player& player) :BaseLevel(window, input, gameState, audio), m_player(player), m_resumeButtonLabel(m_font), m_menuButtonLabel(m_font), m_maineText(m_font), m_restartButtonLabel(m_font), m_timerText(m_font), m_leaderboardText(m_font) {


	if (!m_font.openFromFile("font/bitcount.ttf")) std::cerr << "no font found";

	//setup text to pause, game over, win menu
	m_resumeButtonLabel = UI_Text( 24, { 135, 243 }, "Resume", sf::Color::Black);
	m_menuButtonLabel = UI_Text(24, { 350, 243 }, "Menu", sf::Color::Black);
	m_restartButtonLabel = UI_Text(24, { 135, 243 }, "Restart", sf::Color::Black);

	//Setup pause, game over, restart buttons
	m_resumeButton = UI_Object({ 150, 80 }, { 0, 0 }, m_defaultButtonColour);
	m_restartButton = UI_Object({ 150, 80 }, { 0, 0 }, m_defaultButtonColour);
	m_menuButton = UI_Object({ 150, 80 }, { 0, 0 }, m_defaultButtonColour);

	//Setup pause panel
	
	m_Panel = UI_Object({ 432, 432 }, {0, 0 }, sf::Color::Yellow);

	m_leaderboardPanel = UI_Object({250, 300}, {0, 0}, sf::Color::White);
	m_leaderboardText = UI_Text(24, { 135, 243 }, "", sf::Color::Black);

	//Setup UI Lives
	for (int i = 0; i < 3; i++) {
		GameObject live;
		live = UI_Object( { 50, 50 }, { 0, 0 }, sf::Color::Red);
		m_lives.push_back(live);
	}

	Checkpoints checkpoint;
	checkpoint.setPosition({ 450, 250 });
	m_Checkpoints.push_back(checkpoint);

	m_isSpannerActive = false;

	m_timerText = UI_Text(24, { 0, 0 }, "", sf::Color::White);

	if (!m_tileTexture.loadFromFile("gfx/tilemap.png")) std::cerr << "failed to find tile images";
}

void LevelLoader::handleInput(float dt) {
	if (m_input.isPressed(sf::Keyboard::Scancode::Escape) && m_gameState.getCurrentState() != State::PAUSE) {
		m_gameState.setCurrentState(State::PAUSE);
		m_leaderboardText.setString(m_leaderboard.makeLeaderboard(m_fileLeaderBoard));
	}
	if (m_gameState.getCurrentState() == State::PAUSE || m_gameState.getCurrentState() == State::GAMEOVER || m_gameState.getCurrentState() == State::WIN) {

		sf::Vector2i pos = { m_input.getMouseX(), m_input.getMouseY() };
		sf::Vector2f mousePos = m_window.mapPixelToCoords(pos);
		if (m_gameState.getCurrentState() == State::PAUSE) {
			if (m_input.isLeftMousePressed() && m_resumeButton.getCollisionBox().contains(mousePos))m_gameState.setCurrentState(m_stateLevel);
			if (m_resumeButton.getCollisionBox().contains(mousePos))m_resumeButton.setFillColor(sf::Color::Red);
			else { m_resumeButton.setFillColor(m_defaultButtonColour); }
		}

		if (m_input.isLeftMousePressed() && m_restartButton.getCollisionBox().contains(mousePos))
		{
			m_gameState.setCurrentState(m_stateLevel);
			reset();
		}
		if (m_restartButton.getCollisionBox().contains(mousePos))m_restartButton.setFillColor(sf::Color::Red);
		else { m_restartButton.setFillColor(m_defaultButtonColour); }

		if (m_input.isLeftMousePressed() && m_menuButton.getCollisionBox().contains(mousePos))
		{
			m_gameState.setCurrentState(State::MENU);
			reset();
		}

		if (m_menuButton.getCollisionBox().contains(mousePos))m_menuButton.setFillColor(sf::Color::Red);
		else { m_menuButton.setFillColor(m_defaultButtonColour); }
		return;
	}

	
	m_player.handleInput(dt);

	//throw spaner
	if (!m_isSpannerActive && m_input.isKeyDown(sf::Keyboard::Scancode::R)) {
		Spanner spaner;
		spaner.setPosition(m_player.getPosition());
		spaner.Throwing(m_player.getFlip());
		m_isSpannerActive = true;
		m_timerCoulDownSpaner = m_coulDownSpaner;
		m_spanners.push_back(spaner);
	}
	
}

void LevelLoader::update(float dt) {
	if (m_gameState.getCurrentState() == State::PAUSE || m_gameState.getCurrentState() == State::GAMEOVER || m_gameState.getCurrentState() == State::WIN) return;

	m_player.update(dt);

	if (m_gameState.getCurrentState() != State::PAUSE && m_gameState.getCurrentState() != State::GAMEOVER) {
		m_isTimer = true;
	}

	if (m_isTimer) 
	{ 
		m_timer += dt;
		m_timerText.setString("Time: " + m_leaderboard.formattedTime(m_timer));
	}

	if (m_player.getLives() <= 0) { 
		m_gameState.setCurrentState(State::GAMEOVER);
		m_leaderboardText.setString(m_leaderboard.makeLeaderboard((m_fileLeaderBoard)));
	}
	// reset if fallen too far
	if (m_player.getPosition().y > 1200)
	{
		m_player.restart();
		m_audio.playSoundbyName("death");

	}

	//update Spanner
	for (auto& spanner : m_spanners) {
		if (spanner.isAlive()) {
			spanner.update(dt);
		}
	}

	//Couldown throw spanner
	if (m_isSpannerActive) {
		if (m_timerCoulDownSpaner <= 0) {
			m_isSpannerActive = false;
		}
		else
		{
			m_timerCoulDownSpaner -= dt;
		}
	}

	//Collision
	std::vector<GameObject>& level = *m_tilemap.getLevel();
	for (auto & t : level) {
		if (t.isCollider() && Collision::checkBoundingBox(m_player, t))
		{
			m_player.collisionResponse(t);
		}
		for (auto& spanner : m_spanners)
		{
			if (t.isCollider() && Collision::checkBoundingBox(spanner, t))
			{
				spanner.setAlive(false);
			}
			for (auto& grimlin : m_grimlins) {
				if (spanner.isAlive()) {
					if (grimlin.isAlive() && Collision::checkBoundingBox(spanner, grimlin)) {
						spanner.setAlive(false);
						grimlin.setAlive(false);
						grimlin.setCollider(false);
					}
				}
			}
		}
		for (auto& grimlin : m_grimlins) {
			
			if (Collision::checkBoundingBox(grimlin, m_player)) {
				//m_player.restart();
			}
		}
	}



	//Lives and pause menu move with screen
	auto view = m_window.getView().getCenter();

	m_Panel.setPosition({ view.x - 216, view.y - 216 });

	m_maineText.setPosition({ 0, 200});

	m_leaderboardPanel.setPosition({ view.x - 200, view.y - 100 });
	m_leaderboardText.setPosition({ m_leaderboardPanel.getPosition().x + 20, m_leaderboardPanel.getPosition().y + 20 });

	m_resumeButton.setPosition({ view.x + 54, view.y + 108 });
	m_resumeButtonLabel.setPosition({ m_resumeButton.getPosition().x + 10, m_resumeButton.getPosition().y + 10 });

	m_restartButton.setPosition({ view.x + 54, view.y });
	m_restartButtonLabel.setPosition({ m_restartButton.getPosition().x + 20, m_restartButton.getPosition().y + 10 });

	m_menuButton.setPosition({ view.x + 54, view.y - 108 });
	m_menuButtonLabel.setPosition({ m_menuButton.getPosition().x + 20, m_menuButton.getPosition().y + 10 });

	m_timerText.setPosition({ view.x + 50, view.y - 180 });

	for (int i = 0; i < 3; i++) {
		m_lives[i].setPosition({ view.x - 200 + i * 60, view.y - 200 });

		if (i < m_player.getLives()) {
			m_lives[i].setFillColor(sf::Color::Red);
		}
		else {
			m_lives[i].setFillColor(sf::Color::Black);
		}
	}

	for (int i = 0; i < m_Checkpoints.size();i++) {
		m_Checkpoints[i].update(m_player);
	}

	if (m_player.getGameEndTriggered()) {
		m_isTimer = false;
		m_leaderboard.addScore(m_timer);
		m_leaderboard.saveToFile(m_fileLeaderBoard);

		m_leaderboardText.setString(m_leaderboard.makeLeaderboard(m_fileLeaderBoard));

		m_gameState.setCurrentState(State::WIN);
	}
	
}

void LevelLoader::render() {
	m_bgtilemap.render(m_window);
	m_tilemap.render(m_window);


	for (int i = 0; i < m_Checkpoints.size();i++) {
		m_window.draw(m_Checkpoints[i]);
	}
	for (auto& spanner: m_spanners) {
		if (spanner.isAlive()) {
			m_window.draw(spanner);
		}
	}
	for (auto& grimlin : m_grimlins) {
		if (grimlin.isAlive()) {
			m_window.draw(grimlin);
		}
	}
}

void LevelLoader::drawUI() {

	for (int i = 0;i < 3; i++) {
		m_window.draw(m_lives[i]);
	}

	m_window.draw(m_timerText);

	if (m_gameState.getCurrentState() == State::PAUSE || m_gameState.getCurrentState() == State::GAMEOVER || m_gameState.getCurrentState() == State::WIN) {
		m_window.draw(m_Panel);

		m_window.draw(m_maineText);

		m_window.draw(m_leaderboardPanel);
		m_window.draw(m_leaderboardText);

		if (m_gameState.getCurrentState() == State::PAUSE) {
			m_window.draw(m_resumeButton);
			m_window.draw(m_resumeButtonLabel);
		}

		m_window.draw(m_restartButton);
		m_window.draw(m_restartButtonLabel);

		m_window.draw(m_menuButton);
		m_window.draw(m_menuButtonLabel);
	}
}

void LevelLoader::TileMapSetup(std::string tileMapData, sf::Vector2u mapDimensions, int tile_size, int num_columns, int num_rows, int sheet_spacing, std::string Texture) {

	GameObject tile;
	std::vector<GameObject> tileSet;

	// Set GameObject size (Scaling up 4x for visibility)
	// 4 * 18 = 3 * 24 = 72 (dino size is 24).
	tile.setSize(sf::Vector2f(tile_size * 4, tile_size * 4));
	tile.setCollisionBox({ { 0,0 }, tile.getSize() });

	for (int i = 0; i < num_columns * num_rows; i++)
	{
		int row = i / num_columns;
		int col = i % num_columns;

		tile.setTextureRect({
			{(tile_size + sheet_spacing) * col, (tile_size + sheet_spacing) * row},
			{tile_size, tile_size} });
		if (col <= 4 || col >= 12) tile.setCollider(true);
		else tile.setCollider(false);
		tileSet.push_back(tile);
	}

	// Add Blank
	tile.setTextureRect({ {0, 0}, {-24, -24} }); // Empty rect for blank
	int b = tileSet.size();
	tile.setCollider(false);
	tileSet.push_back(tile);

	//Get tileMap//
	std::string a;
	std::vector<int> tileMap;
	std::ifstream data(tileMapData);
	if (!data.is_open()) std::cerr << "Failed to open data \n";
	int i = 0;
	while (data >> a) {
		if (a == "b") {
			tileMap.push_back(b);
		}
		else {
			int c = stoi(a);
			tileMap.push_back(c);
		}

	};
	data.close();
	//__________//

	m_tilemap.loadTexture(Texture);
	m_tilemap.setTileSet(tileSet);
	m_tilemap.setTileMap(tileMap, mapDimensions);
	m_tilemap.setPosition({ 0, 100 });
	m_tilemap.buildLevel();

	std::cerr << m_tilemap.getLevel() << "\n";

	tileSet.clear();
}

void LevelLoader::BgTileMapSetup(std::string tileMapData, sf::Vector2u mapDimensions, int tile_size, int num_columns, int num_rows, int sheet_spacing, std::string Texture) {
	GameObject tile;
	std::vector<GameObject> tileSet;

	// Set GameObject size (Scaling up 4x for visibility)
	// 4 * 18 = 3 * 24 = 72 (dino size is 24).
	tile.setSize(sf::Vector2f(tile_size * 9, tile_size * 9));
	tile.setCollisionBox({ { 0,0 }, tile.getSize() });

	for (int i = 0; i < num_columns * num_rows; i++)
	{
		int row = i / num_columns;
		int col = i % num_columns;

		tile.setTextureRect({
			{(tile_size + sheet_spacing) * col, (tile_size + sheet_spacing) * row},
			{tile_size, tile_size} });
		if (col <= 4 || col >= 12) tile.setCollider(true);
		else tile.setCollider(false);
		tileSet.push_back(tile);
	}

	// Add Blank
	tile.setTextureRect({ {0, 0}, {-24, -24} }); // Empty rect for blank
	int b = tileSet.size();
	tile.setCollider(false);
	tileSet.push_back(tile);

	//Get tileMap//
	std::string a;
	std::vector<int> tileMap;
	std::ifstream data(tileMapData);
	if (!data.is_open()) std::cerr << "Failed to open data \n";
	int i = 0;
	while (data >> a) {
		if (a == "b") {
			tileMap.push_back(b);
		}
		else {
			int c = stoi(a);
			tileMap.push_back(c);
		}

	};
	data.close();
	//__________//

	m_bgtilemap.loadTexture(Texture);
	m_bgtilemap.setTileSet(tileSet);
	m_bgtilemap.setTileMap(tileMap, mapDimensions);
	m_bgtilemap.setPosition({ 0, 0 });
	m_bgtilemap.buildLevel();

	tileSet.clear();
}

void LevelLoader::SetupGremlins(std::string filename) {
	float x, y;
	std::ifstream data(filename);
	if (!data.is_open()) std::cerr << "Failed to open data \n";
	int i = 0;
	while (data >> x >> y) {
		Gremlin grimlin;
		grimlin.setPosition({ x, y });
		m_grimlins.push_back(grimlin);
	};
	data.close();
}

GameObject LevelLoader::UI_Object(sf::Vector2f size, sf::Vector2f position, sf::Color color) {
	GameObject UI_OBJECT;
	UI_OBJECT.setSize(size);
	UI_OBJECT.setPosition(position);
	UI_OBJECT.setFillColor(color);
	UI_OBJECT.setCollisionBox({ {0,0}, UI_OBJECT.getSize() });
	return UI_OBJECT;
}

sf::Text LevelLoader::UI_Text(int characterSize, sf::Vector2f position, std::string text, sf::Color color) {
	sf::Text UI_TEXT(m_font);
	UI_TEXT.setCharacterSize(characterSize);		// setup labels
	UI_TEXT.setPosition(position);
	UI_TEXT.setString(text);
	UI_TEXT.setFillColor(color);
	return UI_TEXT;
}

void LevelLoader::SetUpCheckPoints(std::string filename) {
	std::ifstream data;
	Checkpoints checkpoint;
	float x, y;
	while (data >> x >> y) {
		checkpoint.setPosition({ x, y });
		m_Checkpoints.push_back(checkpoint);
	}

}

void LevelLoader::updateCameraAndBackground(sf::Vector2i WORLD_SIZE, sf::Vector2i VIEW_SIZE)
{
	auto view = m_window.getView();
	auto player_pos = m_player.getPosition() + m_player.getSize() * 0.5f;

	float halfViewWidth = VIEW_SIZE.x / 2.0f;
	float halfViewHeight = VIEW_SIZE.y / 2.0f;

	player_pos.x = std::clamp(player_pos.x, halfViewWidth, WORLD_SIZE.x - halfViewWidth);
	player_pos.y = std::clamp(player_pos.y, halfViewHeight, WORLD_SIZE.y - halfViewHeight);

	view.setCenter(player_pos);
	m_window.setView(view);

	m_bgtilemap.setPosition({ player_pos.x - halfViewWidth, 0 });
}

void LevelLoader::reset() {
	m_player.reset();

	for (auto& grimlin : m_grimlins) {
		grimlin.setAlive(true);
		grimlin.setCollider(true);
	}

	m_spanners.clear();
	m_isSpannerActive = false;
	m_timerCoulDownSpaner = 0.f;
	m_isTimer = false;
	m_timer = 0.f;

	for (auto& checkpoint : m_Checkpoints) {
		checkpoint.setIsActive(false);
	}
}