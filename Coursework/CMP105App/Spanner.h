#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include <iostream>
#include "Framework/AudioManager.h"

class Spanner : public GameObject
{
public:
	Spanner();
	void update(float dt);
	void 


private:
	sf::Texture m_texture;
	sf::Vector2f m_velosity;
	sf::Vector2f m_acce;
	

	float GRAVITY = 200.f;
	float THROWINGFORCE = 100.f;
	float SPEED = 10.f;
};

