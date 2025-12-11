#include "game.h"
#include "pilka.h"
#include "paletka.h"


Game::Game() :
	paletka({ SZEROKOSC / 2.f, WYSOKOSC - 100.f }, { 200.f, 20.f }, { 400.f, 0.f }),
	pilka({ SZEROKOSC / 2.f, WYSOKOSC - 200.f }, 20.f, { -300.f, -300.f })

{
	ROZMIAR_BLOKU_X = (SZEROKOSC - (ILE_KOLUMN - 1) * 2.f) / ILE_KOLUMN;
	ROZMIAR_BLOKU_Y = 20.f;

	for (int y = 0; y < ILE_WIERSZY; y++) {
		for (int x = 0; x < ILE_KOLUMN; x++) {
			float posX = x * (ROZMIAR_BLOKU_X + 2.f);
			float posY = y * (ROZMIAR_BLOKU_Y + 2.f) + 60.f;
			//ustalanie koloru wzgledem zycia
			int zycie = 3;
			cegly.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), zycie);
		}
	}
}


void Game::update(sf::Time dt) {

	//ruch paletki i pilki
	paletka.ruch(dt, { (float)SZEROKOSC,(float)WYSOKOSC });
	pilka.ruch(dt, { (float)SZEROKOSC,(float)WYSOKOSC }, paletka);

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
}

void Game::render(sf::RenderTarget& target) {
	pilka.draw(target);
	paletka.draw(target);
	//rysowanie cegiel
	for (auto& blk : cegly) {
		blk.draw(target);
	};
}
