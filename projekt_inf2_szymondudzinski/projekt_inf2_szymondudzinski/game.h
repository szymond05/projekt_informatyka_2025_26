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

	sf::RenderWindow window;
	Paletka paletka;
	Pilka pilka;
	sf::Clock deltaClock;

	void processEvents();
	void update(sf::Time dt);
	void render();
public:
	Game();
	void run();
};

void Game::run() {
	while (window.isOpen())
	{
		sf::Time dt = deltaClock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//aktualizacja logiki
		paletka.ruch(dt, { SZEROKOSC,WYSOKOSC });
		pilka.ruch(dt, { SZEROKOSC,WYSOKOSC }, paletka);

		//kolizja z ceglami
		for (auto& blk : cegly) {
			if (!blk.czyZniszczony() && pilka.getGlobalBounds().intersects(blk.getGlobalBounds())) {
				blk.trafienie();
				pilka.odbijY();
			}
		}
		//usuwanie zniszczonych cegiel
		for (int i = cegly.size() - 1; i >= 0; i--) {
			if (cegly[i].czyZniszczony()) {
				cegly.erase(cegly.begin() + i);
			}
		}
		window.clear(sf::Color(40, 30, 20));
		pilka.draw(window);
		paletka.draw(window);
		//rysowanie cegiel
		for (auto& blk : cegly) {
			blk.draw(window);
		};

		window.display();
	}
}