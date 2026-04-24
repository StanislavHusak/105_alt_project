#include "LevelLoader.h"

LevelLoader::LevelLoader(sf::RenderWindow& window, Input& input, GameState& gameState, AudioManager& audio, Player& player) :BaseLevel(window, input, gameState, audio), m_resumeButtonLabel(m_font), m_menuButtonLabel(m_font), m_player(player){


	if (!m_font.openFromFile("font/bitcount.ttf")) std::cerr << "no font found";

	//setup text to pause menu
	UI_Text(m_resumeButtonLabel, 24, { 135, 243 }, "Resume", sf::Color::Black);
	UI_Text(m_menuButtonLabel, 24, { 350, 243 }, "Menu", sf::Color::Black);

	//Setup pause buttons
	UI_Object(m_resumeButton, { 216, 100 }, { 58, 208 }, m_defaultButtonColour);
	UI_Object(m_menuButton, { 216, 100 }, { 280, 208 }, m_defaultButtonColour);

	//Setup pause panel
	UI_Object(m_PausePanel, { 500, 300 }, { 50, 200 }, sf::Color::Yellow);

	//Setup UI Lives
	for (int i = 0; i < 3; i++) {
		GameObject live;
		UI_Object(live, { 50, 50 }, { 0, 0 }, sf::Color::Red);
		m_lives.push_back(live);
	}

	Checkpoints checkpoint;
	checkpoint.setPosition({ 450, 250 });
	m_Checkpoints.push_back(checkpoint);

	m_isSpannerActive = false;

	

}

void LevelLoader::TileMapSetup( std::string tileMapData, sf::Vector2u mapDimensions, int tile_size, int num_columns, int num_rows, int sheet_spacing, std::string Texture) {
	
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

void LevelLoader::BgTileMapSetup( std::string tileMapData, sf::Vector2u mapDimensions, int tile_size, int num_columns, int num_rows, int sheet_spacing, std::string Texture) {
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

void LevelLoader::UI_Object(GameObject& Gameobject, sf::Vector2f size, sf::Vector2f position, sf::Color color) {
	Gameobject.setSize(size);
	Gameobject.setPosition(position);
	Gameobject.setCollisionBox({ {0,0}, Gameobject.getSize() });
	Gameobject.setFillColor(color);
}

void LevelLoader::UI_Text(sf::Text& textObj, int characterSize, sf::Vector2f position, std::string text, sf::Color color) {
	textObj.setCharacterSize(characterSize);		// setup labels
	textObj.setPosition(position);
	textObj.setString(text);
	textObj.setFillColor(color);
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

void LevelLoader::handleInput(float dt) {
	if (m_input.isPressed(sf::Keyboard::Scancode::Escape))
		m_gameState.setCurrentState(State::MENU);

	//throw spaner
	if (!m_isSpannerActive && m_input.isKeyDown(sf::Keyboard::Scancode::R)) {
		Spanner spaner;
		spaner.setPosition(m_player.getPosition());
		spaner.Throwing(m_player.getFlip());
		m_isSpannerActive = true;
		m_timerCoulDownSpaner = m_coulDownSpaner;
		m_spanners.push_back(spaner);
	}
	//Pause buttons
	if (m_gameState.getCurrentState() != State::PAUSE) return;

	sf::Vector2i mousePos{m_input.getMouseX(), m_input.getMouseY() };
	if (m_input.isLeftMousePressed() && Collision::checkBoundingBox(m_resumeButton, mousePos))
	{
		m_gameState.setCurrentState(State::LEVELONE);
	}
	if (m_input.isLeftMousePressed() && Collision::checkBoundingBox(m_menuButton, mousePos))
	{
		m_gameState.setCurrentState(State::MENU);
	}
}

void LevelLoader::update(float dt) {

	if (m_player.getLives() <= 0) { 
		m_gameState.setCurrentState(State::MENU); 
		m_player.setPosition({ 24, 100 });
		m_player.setLives(3);
		for (auto& checkpoint : m_Checkpoints) {
			checkpoint.setIsActive(false);
		}
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
	for (auto& spanner : m_spanners) {
		for (auto& t : level)
		{
			if (t.isCollider() && Collision::checkBoundingBox(m_player, t))
			{
				m_player.collisionResponse(t);
			}


			if (t.isCollider() && Collision::checkBoundingBox(spanner, t))
			{
				spanner.setAlive(false);

			}
		}
		for (auto& grimlin : m_grimlins) {
			if (spanner.isAlive()) {
				if (Collision::checkBoundingBox(spanner, grimlin)) {
					spanner.setAlive(false);
					grimlin.setAlive(false);
					grimlin.setCollider(false);
				}
				if (Collision::checkBoundingBox(grimlin, m_player)) {
					std::cerr << "Iam here\n";
					m_player.reset();
				}
			}
		}
	}

	//Lives move with screen
	auto view = m_window.getView().getCenter();
	for (int i = 0; i < 3; i++) {
		m_lives[i].setPosition({ view.x - 200 + i*60, view.y - 200 });

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

	//Pause hover button
	if (m_gameState.getCurrentState() != State::PAUSE) return;

	sf::Vector2i mousePos{ m_input.getMouseX(), m_input.getMouseY() };

	if (Collision::checkBoundingBox(m_resumeButton, mousePos))
	{
		m_resumeButton.setFillColor(sf::Color::Red);
	}
	else { m_resumeButton.setFillColor(m_defaultButtonColour); }
	if (Collision::checkBoundingBox(m_menuButton, mousePos))
	{
		m_menuButton.setFillColor(sf::Color::Red);
	}
	else { m_menuButton.setFillColor(m_defaultButtonColour); }
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

	if (m_gameState.getCurrentState() == State::PAUSE) {
		m_window.draw(m_PausePanel);
		m_window.draw(m_resumeButton);
		m_window.draw(m_resumeButtonLabel);
		m_window.draw(m_menuButton);
		m_window.draw(m_menuButtonLabel);
	}
}