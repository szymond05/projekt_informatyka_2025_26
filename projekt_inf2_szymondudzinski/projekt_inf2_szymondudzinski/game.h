#pragma once
#include <SFML/Graphics.hpp>
#include <paletka.h>
#include <pilka.h>
#include <cegla.h>

class Game {
private:
	std::vector<Cegla> cegly;
	const int SZEROKOSC = 800;
	const int WYSOKOSC = 600;
	const int ILE_KOLUMN = 12;
	const int ILE_WIERSZY = 4;
	float ROZMIAR_BLOKU_X;
	float ROZMIAR_BLOKU_Y = 20.f;

	Paletka paletka;
	Pilka pilka;
	sf::Clock deltaClock;

public:
	Game();
	void update(sf::Time dt);
	void render(sf::RenderTarget& target);
};
