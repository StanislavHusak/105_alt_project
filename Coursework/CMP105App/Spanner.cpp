#include "Spanner.h"

Spanner::Spanner() {
	
	setSize({ 32, 32 });
	setCollisionBox({ {4, 4}, {24, 24} });
	setCollider(true);
	setFillColor(sf::Color::White);
	setPosition({ 100, 300 });

	
	m_acce = { 0.f, GRAVITY };

	m_isAllive = true;
}
Spanner::~Spanner() {

}

void Spanner::update(float dt) {
	m_velocity += m_acce * dt;

	std::cerr << "Velosity" << m_velocity.x << " " << m_velocity.y << "\n";
	move(m_velocity * dt);
	
}

void Spanner::Throwing(bool isRight) {
	std::cerr << isRight << "\n";

	if (isRight) {
		m_velocity = { THROWINGFORCE * HORRIZONTAL_SPEED, -THROWINGFORCE };
	}
	else {
		m_velocity = { -THROWINGFORCE * HORRIZONTAL_SPEED, -THROWINGFORCE };
	}
}

