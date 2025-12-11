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
	sf::Color::Transparent, // 0 dead
	sf::Color::Red,         // 1
	sf::Color::Magenta,     // 2
	sf::Color::Yellow       // 3
};


void Cegla::trafienie() {
	if (jestZniszczony) return;

	punktyZycia--;

	if (punktyZycia <= 0) {
		jestZniszczony = true;
		return;
	}

	aktualizujKolor();
}

void Cegla::aktualizujKolor() {
	int hp = std::max(0, punktyZycia);
	this->setFillColor(colorLUT[hp]);
}

void Cegla::draw(sf::RenderTarget& window) {
	window.draw(*this);
}

int Cegla::getHP() const {
	return punktyZycia;
}