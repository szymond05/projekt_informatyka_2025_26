#include "game.h"


Game::Game() :
	window(sf::VideoMode(SZEROKOSC, WYSOKOSC), "gra"),
	paletka({ SZEROKOSC / 2.f, WYSOKOSC / 2.f }, { 200.f, 20.f }, { 400.f, 0.f }),
	pilka({ SZEROKOSC / 2.f, WYSOKOSC - 30.f }, 20.f, { -300.f, -300.f })

{
	window.setFramerateLimit(60);
	ROZMIAR_BLOKU_X = (SZEROKOSC - (ILE_KOLUMN - 1) * 2.f) / ILE_KOLUMN;
	ROZMIAR_BLOKU_Y = 20.f;
}

void Game::run() {
	while (window.isOpen())
	{
		sf::Time dt = deltaClock.restart();

		processEvents();
		update(dt);
		render();

		window.display();
	}
}

void Game::processEvents() {
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Game::update(sf::Time dt) {
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
}

void Game::render() {
	window.clear(sf::Color(40, 30, 20));
	pilka.draw(window);
	paletka.draw(window);
	//rysowanie cegiel
	for (auto& blk : cegly) {
		blk.draw(window);
	};

	window.display();
}