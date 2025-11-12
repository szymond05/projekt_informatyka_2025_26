#pragma once
#include <SFML/Graphics.hpp>
#include <paletka.h>

class Pilka {
private:
	sf::CircleShape m_shape;
	sf::Vector2f velocity{ 200.f, 200.f };
public:
	Pilka(sf::Vector2f startPos, float radius, sf::Vector2f startVel);
	void odbijY();
	void draw(sf::RenderTarget& window);
	void ruch(sf::Time dt, sf::Vector2f windowWH, Paletka& pdl);
	sf::FloatRect getGlobalBounds() { return m_shape.getGlobalBounds(); }
};

Pilka::Pilka(sf::Vector2f startPos, float radius, sf::Vector2f startVel) {
	velocity = startVel;
	m_shape.setPosition(startPos);
	m_shape.setRadius(radius);
	m_shape.setFillColor(sf::Color::Green);
	m_shape.setOrigin(radius, radius);
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