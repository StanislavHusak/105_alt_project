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

/// <summary>
///	Updates the spanner's movement using simple physics.
/// Applies acceleration (gravity) and moves the object each frame.
/// </summary>
/// <param name="dt"></param>
void Spanner::update(float dt) {
	m_velocity += m_acce * dt;
	move(m_velocity * dt);
}

/// <summary>
/// Initializes the spanner's velocity when thrown by the player.
/// Determines direction (left/right) and applies an upward force.
/// </summary>
/// <param name="isRight">
/// True = throw to the right ,
/// False = throw to the left
/// </param>
void Spanner::Throwing(bool isRight) {

	if (isRight) {
		m_velocity = { THROWINGFORCE * HORRIZONTAL_SPEED, -THROWINGFORCE };
	}
	else {
		m_velocity = { -THROWINGFORCE * HORRIZONTAL_SPEED, -THROWINGFORCE };
	}
}

