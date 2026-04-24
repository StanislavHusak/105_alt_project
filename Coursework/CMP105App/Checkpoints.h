#pragma once

#include "Scene.h"
#include "Framework/Collision.h"
#include "Framework/TileMap.h"
#include "Player.h"
#include "Lever.h"
#include "Flag.h"
#include <algorithm>
#include <fstream>

class Checkpoints : public GameObject
{
public:
	Checkpoints();
	void setIsActive(bool isActive) { m_isActive = isActive; };

	void update(Player& player);
private:
	sf::Color m_defaultColor = sf::Color::Yellow;
	sf::Color m_activeColor;
	bool m_isActive;
};

