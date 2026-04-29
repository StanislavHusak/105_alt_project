#include "Spanner.h"

Spanner::Spanner() {
	
	setSize({ 32, 32 });
	setCollisionBox({ {4, 4}, {24, 24} });
	setCollider(true);
	setFillColor(sf::Color::Green);
	setPosition({ 100, 300 });

	
	m_acce = { 0.f, GRAVITY };

	m_isAllive = true;
}
Spanner::~Spanner() {

}

void Spanner::update(float dt) {
	m_velocity += m_acce * dt;
	move(m_velocity * dt);
	
}

void Spanner::Throwing(bool isRight) {

	if (isRight) {
		m_velocity = { THROWINGFORCE * HORRIZONTAL_SPEED, -THROWINGFORCE };
	}
	else {
		m_velocity = { -THROWINGFORCE * HORRIZONTAL_SPEED, -THROWINGFORCE };
	}
}

