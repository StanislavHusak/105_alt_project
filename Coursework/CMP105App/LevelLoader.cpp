#include "LevelLoader.h"

LevelLoader::LevelLoader(sf::RenderWindow& window, Input& input, GameState& gameState, AudioManager& audio) : Scene(window, input, gameState, audio), m_alertText(m_font) {
	

}

void LevelLoader::MapSetup(std::string tileMapData, sf::Vector2u mapDimensions, int tile_size, int num_columns, int num_rows, int sheet_spacing, std::string Texture) {
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
	int a;
	std::vector<int> tileMap;
	std::ifstream data(tileMapData);
	if (!data.is_open()) std::cerr << "Failed to open data \n";
	int i = 0;
	while (data >> a) {
		tileMap.push_back(a);
	}
	data.close();
	//__________//

	m_tilemap.loadTexture("gfx/tilemap.png");
	m_tilemap.setTileSet(tileSet);
	m_tilemap.setTileMap(tileMap, mapDimensions);
	m_tilemap.setPosition({ 0, 100 });
	m_tilemap.buildLevel();

	tileSet.clear();
}


void LevelLoader::BackGroundSetup(std::string tileMapData, sf::Vector2u mapDimensions, int tile_size, int num_columns, int num_rows, int sheet_spacing, std::string Texture) {
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
	int a;
	std::vector<int> tileMap;
	std::ifstream data(tileMapData);
	if (!data.is_open()) std::cerr << "Failed to open data \n";
	int i = 0;
	while (data >> a) {
		tileMap.push_back(a);
	}
	data.close();
	//__________//

	m_bgtilemap.loadTexture("gfx/tilemap.png");
	m_bgtilemap.setTileSet(tileSet);
	m_bgtilemap.setTileMap(tileMap, mapDimensions);
	m_bgtilemap.setPosition({ 0, 100 });
	m_bgtilemap.buildLevel();

	tileSet.clear();
}