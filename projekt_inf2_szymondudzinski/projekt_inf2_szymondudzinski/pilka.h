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
	float getX() { return x; }
	float getY() { return y; }
	float getVelX() { return velX; }
	float getVelY() { return velY; }
};

