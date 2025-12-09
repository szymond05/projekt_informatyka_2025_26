#include "cegla.h"

Cegla::Cegla(sf::Vector2f startPos, sf::Vector2f rozmiar, int L) {
	punktyZycia = L;
	jestZniszczony = false;
	this->setSize(rozmiar);
	this->setPosition(startPos);
	this->setFillColor(sf::Color::Yellow);
	this->setOutlineColor(sf::Color::White);
	aktualizujKolor();
};

const std::array<sf::Color, 4> Cegla::colorLUT = {
	sf::Color::Red,
	sf::Color::Magenta,
	sf::Color::Yellow,
	sf::Color::Transparent
};

void Cegla::trafienie() {
	if (jestZniszczony == true)
		return;
	punktyZycia--;
	aktualizujKolor();
	if (punktyZycia <= 0)
		jestZniszczony = true;
}

void Cegla::aktualizujKolor() {
	this->setFillColor(colorLUT[punktyZycia]);
}

void Cegla::draw(sf::RenderTarget& window) {
	window.draw(*this);
}

int Cegla::getHP() {
	return punktyZycia;
}