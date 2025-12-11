#pragma once
#include <SFML/Graphics.hpp>

class Paletka {
private:
	sf::RectangleShape m_shape;
	sf::Vector2f velocity{ 200.f, 0.f };
	float x;
	float y;
public:
	Paletka(sf::Vector2f startPos, sf::Vector2f rozmiar, sf::Vector2f startVel);
	void draw(sf::RenderTarget& window);
	void ruch(sf::Time dt, sf::Vector2f windowWidth);
	sf::FloatRect getGlobalBounds() { return m_shape.getGlobalBounds(); }
	sf::Vector2f getPosition() const { return m_shape.getPosition(); }
	void setPosition(sf::Vector2f pos) { m_shape.setPosition(pos); }
};

