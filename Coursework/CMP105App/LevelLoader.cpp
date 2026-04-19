#include "LevelLoader.h"

LevelLoader::LevelLoader() : m_resumeButtonLabel(m_font), m_menuButtonLabel(m_font){

	//Setup tilemap and background
	TileMapSetup(m_tilemap, "data/Tilemap.txt", { 40, 8 }, 18, 4, 20, 9, 1, "gfx/tilemap.png");
	TileMapSetup(m_bgtilemap, "data/BgTilemap.txt", { 14, 3 }, 24, 9, 8, 3, 1, "gfx/tilemap-backgrounds.png");

	if(!m_font.openFromFile("font/bitcount.ttf")) std::cerr << "no font found";

	//setup text to pause menu
	UI_Text(m_resumeButtonLabel, 24, { 135, 243 }, "Resume", sf::Color::Black);
	UI_Text(m_menuButtonLabel, 24, { 350, 243 }, "Menu", sf::Color::Black);

	//Setup pause buttons
	UI_Object(m_resumeButton, { 216, 100 }, { 58, 208 }, m_defaultButtonColour);
	UI_Object(m_menuButton, { 216, 100 }, { 280, 208 }, m_defaultButtonColour);

	//Setup pause panel
	UI_Object(m_PausePanel, { 500, 300 }, { 50, 200 }, sf::Color::Yellow);
}

void LevelLoader::TileMapSetup(TileMap& tilemap, std::string tileMapData, sf::Vector2u mapDimensions, int tile_size, int scaling, int num_columns, int num_rows, int sheet_spacing, std::string Texture) {
	GameObject tile;
	std::vector<GameObject> tileSet;

	// Set GameObject size (Scaling up 4x for visibility)
	// 4 * 18 = 3 * 24 = 72 (dino size is 24).
	tile.setSize(sf::Vector2f(tile_size * scaling, tile_size * scaling));
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

	tilemap.loadTexture("gfx/tilemap.png");
	tilemap.setTileSet(tileSet);
	tilemap.setTileMap(tileMap, mapDimensions);
	tilemap.setPosition({ 0, 100 });
	tilemap.buildLevel();

	tileSet.clear();
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


void LevelLoader::draw(sf::RenderWindow& window, State state) {
	m_tilemap.render(window);
	m_bgtilemap.render(window); 

	if (state == State::PAUSE) {
		window.draw(m_PausePanel);
		window.draw(m_resumeButton);
		window.draw(m_resumeButtonLabel);
		window.draw(m_menuButton);
		window.draw(m_menuButtonLabel);
	}
}


void LevelLoader::PausebuttonsInput(Input& input, GameState& gameState){
	if (gameState.getCurrentState() != State::PAUSE) return;

	sf::Vector2i mousePos {input.getMouseX(), input.getMouseY()};
	if (input.isLeftMousePressed() && Collision::checkBoundingBox(m_resumeButton, mousePos))
	{
		gameState.setCurrentState(State::LEVELONE);
	}
	if (input.isLeftMousePressed() && Collision::checkBoundingBox(m_menuButton, mousePos))
	{
		gameState.setCurrentState(State::MENU);
	}
	if (Collision::checkBoundingBox(m_resumeButton, mousePos))
	{
		m_resumeButton.setFillColor(sf::Color::Red);
	}
	else{ m_resumeButton.setFillColor(m_defaultButtonColour); }
	if (Collision::checkBoundingBox(m_menuButton, mousePos))
	{
		m_menuButton.setFillColor(sf::Color::Red);
	}
	else { m_menuButton.setFillColor(m_defaultButtonColour); }
}