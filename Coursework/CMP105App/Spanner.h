#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include <iostream>
#include "Framework/AudioManager.h"

class Spanner : public GameObject
{
public:
	Spanner();
	~Spanner();
	void update(float dt);
	void Throwing(bool isRight);

	bool getAllive() {return m_isAllive;};
	void setAllive(bool allive) { m_isAllive = allive; };

private:
	sf::Texture m_texture;
	sf::Vector2f m_velosity;
	sf::Vector2f m_acce;

	bool m_isAllive;

	float GRAVITY = 500.f;
	float THROWINGFORCE = 200.f;
	float HORRIZONTAL_SPEED = 3.f;
};

