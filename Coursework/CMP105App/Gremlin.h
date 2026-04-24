#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include <iostream>
#include "Framework/AudioManager.h"
#include "Spanner.h"

class Gremlin : public GameObject
{
public:
	Gremlin();
	//void update(float dt) override;
	

private:
	sf::Texture m_texture;
};

