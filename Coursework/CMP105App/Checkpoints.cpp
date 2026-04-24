#include "Checkpoints.h"

Checkpoints::Checkpoints() {
	setSize({ 72, 72 });
	setCollisionBox({ {11, 11}, {50, 50} });
	setFillColor(m_defaultColor);
	m_isActive = false;
}
void Checkpoints::update(Player& player) {
	//Check collision with player
	if (!m_isActive && Collision::checkBoundingBox(player, *this)) {
		player.setSpawnPosition(getPosition());
		m_isActive = true;
	}
}