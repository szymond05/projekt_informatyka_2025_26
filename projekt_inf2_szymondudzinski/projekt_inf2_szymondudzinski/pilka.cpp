#include "pilka.h"

Pilka::Pilka(sf::Vector2f startPos, float radius, sf::Vector2f startVel) {
	velocity = startVel;
	m_shape.setPosition(startPos);
	m_shape.setRadius(radius);
	m_shape.setFillColor(sf::Color::Green);
	m_shape.setOrigin(radius, radius);
	x = m_shape.getPosition().x;
	y = m_shape.getPosition().y;
	velX = velocity.x;
	velY = velocity.y;
}

void Pilka::draw(sf::RenderTarget& window) {
	window.draw(m_shape);
}

void Pilka::ruch(sf::Time dt, sf::Vector2f windowWH, Paletka& pdl) {
	m_shape.move(velocity * dt.asSeconds());
	float xp = m_shape.getPosition().x;
	float yp = m_shape.getPosition().y;
	float rp = m_shape.getRadius();

	if (xp - rp <= 0 || xp + rp >= windowWH.x) {
		velocity.x = -velocity.x;
	}
	if (yp - rp <= 0) {
		velocity.y = -velocity.y;
	}
	if (yp + rp >= windowWH.y) {
		velocity.y = -velocity.y;
	}

	//odbicie od paletki
	if (getGlobalBounds().intersects(pdl.getGlobalBounds())) {
		velocity.y = -velocity.y;
	}
}
void Pilka::odbijY() {
	velocity.y = -velocity.y;
}

void Pilka::reset(sf::Vector2f pos, sf::Vector2f vel) {
	m_shape.setPosition(pos);
	velocity = vel;
	velX = velocity.x;
	velY = velocity.y;
}