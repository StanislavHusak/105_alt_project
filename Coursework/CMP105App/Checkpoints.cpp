#include "Checkpoints.h"

Checkpoints::Checkpoints() {
	setSize({ 72, 72 });
	setCollisionBox({ {11, 11}, {50, 50} });
	setFillColor(m_defaultColor);
	isActive = false;
}
void Checkpoints::update(Player& player) {
	//Check collision with player
	if (!isActive && Collision::checkBoundingBox(player, *this)) {
		player.setSpawnPosition(getPosition());
		isActive = true;
	}
}