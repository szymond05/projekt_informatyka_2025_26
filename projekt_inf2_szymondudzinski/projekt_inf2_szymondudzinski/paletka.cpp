#include "paletka.h"

Paletka::Paletka(sf::Vector2f startPos, sf::Vector2f rozmiar, sf::Vector2f startVel) {
	velocity = startVel;
	m_shape.setSize(rozmiar);
	m_shape.setPosition(startPos);
	m_shape.setFillColor(sf::Color::Green);
	m_shape.setOrigin(rozmiar.x / 2.f, rozmiar.y / 2.f);
	x = m_shape.getPosition().x;
	y = m_shape.getPosition().y;
}

void Paletka::draw(sf::RenderTarget& window) {
	window.draw(m_shape);
}

void Paletka::ruch(sf::Time dt, sf::Vector2f windowWidth) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		m_shape.move(-velocity.x * dt.asSeconds(), 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		m_shape.move(velocity.x * dt.asSeconds(), 0.f);
	}
}