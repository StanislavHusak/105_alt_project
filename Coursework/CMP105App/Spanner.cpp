#include "Spanner.h"

Spanner::Spanner() {
	
	setSize({ 32, 32 });
	setFillColor(sf::Color::White);
	setPosition({ 100, 300 });

	m_velocity = { THROWINGFORCE, -THROWINGFORCE };
	m_acce = { 0.f, GRAVITY };
	


}

void Spanner::update(float dt) {
	m_velocity += m_acce * dt;

	std::cerr << "Velosity" << m_velocity.x << " " << m_velocity.y << "\n";
	move(m_velocity * dt);
	

}

