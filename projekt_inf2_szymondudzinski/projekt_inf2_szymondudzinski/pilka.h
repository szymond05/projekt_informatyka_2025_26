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

	float x;
	float y;
	float velX;
	float velY;

	sf::Vector2f getPosition() const { return m_shape.getPosition(); }
	sf::Vector2f getVelocity() const { return velocity; }
	void reset(sf::Vector2f pos, sf::Vector2f vel);
};

