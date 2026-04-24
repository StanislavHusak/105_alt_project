#include "Gremlin.h"

Gremlin::Gremlin() {
	setSize({ 75, 75 });
	setCollisionBox({ { 5, 5 }, {65, 65} });
	setCollider(true);
	setFillColor(sf::Color::Black);

	setAlive(true);
}
