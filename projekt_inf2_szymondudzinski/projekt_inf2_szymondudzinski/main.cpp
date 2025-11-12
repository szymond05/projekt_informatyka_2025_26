#include <SFML/graphics.hpp>
#include <vector>
#include <pilka.h>
#include <paletka.h>
#include <cegla.h>
int main() {

	const int SZEROKOSC = 800;
	const int WYSOKOSC = 600;
	sf::RenderWindow window(sf::VideoMode(SZEROKOSC, WYSOKOSC), "gierka");
	window.setFramerateLimit(60);
	sf::Clock deltaClock;

	sf::Time czas;

	//tworzenie obiektow gry
	Paletka paletka({ SZEROKOSC / 2.f, WYSOKOSC / 2.f }, { 200.f, 20.f }, { 400.f, 0.f });
	Pilka pilka({ SZEROKOSC / 2.f, WYSOKOSC - 30.f }, 20.f, { - 300.f, -300.f});

	std::vector<Cegla> cegly;
	const int ILE_KOLUMN = 12;
	const int ILE_WIERSZY = 4;
	float ROZMIAR_BLOKU_X = (SZEROKOSC - (ILE_KOLUMN - 1) * 2.f) / ILE_KOLUMN;
	float ROZMIAR_BLOKU_Y = 20.f;

	//procedura rysowania blokow
	for (int y = 0; y < ILE_WIERSZY; y++) {
		for (int x = 0; x < ILE_KOLUMN; x++) {
			float posX = x * (ROZMIAR_BLOKU_X + 2.f);
			float posY = y * (ROZMIAR_BLOKU_Y + 2.f) + 60.f;
			//ustalanie koloru wzgledem zycia
			int zycie = 0;
			if (y == 0)
				zycie = 1;
			if (y >= 1)
				zycie = 2;
			cegly.emplace_back(sf::Vector2f(posX,posY), sf::Vector2f(ROZMIAR_BLOKU_X,ROZMIAR_BLOKU_Y),zycie);
		}
	}


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
		pilka.ruch(dt, { SZEROKOSC,WYSOKOSC },paletka);

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
		window.clear(sf::Color(40,30,20));
		pilka.draw(window);
		paletka.draw(window);
		//rysowanie cegiel
		for (auto& blk : cegly) {
			blk.draw(window);
		};
			
		window.display();
	}
	return 0;
}
