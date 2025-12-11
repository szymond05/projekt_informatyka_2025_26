#include <SFML/Graphics.hpp>
#include "game.h"
#include <gamestate.h>
#include <iostream>

#define MAX_LICZBA_POZIOMOW 4

enum class AppState { Menu, Playing, Scores, GameOver, Victory, Exiting };

class Menu
{

private:
	sf::Font font;
	sf::Text menu[MAX_LICZBA_POZIOMOW];//maksymalna liczba poziomow
	int selectedItem = 0;


public:
	sf::Font& getFont() { return font; }
	Menu(float width, float height);
	~Menu() {};
	void przesunG();//przesun do gory
	void przesunD();//przesun w dol
	int getSelectedItem() { return selectedItem; }//zwroc poziom menu
	void draw(sf::RenderWindow& window);//rysuj menu w oknie
};


Menu::Menu(float width, float height)
{	//laduj czcionke
	if (!font.loadFromFile("Coolvetica.otf"))
	{
		return;
	}
	//rysowanie elementow menu
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Cyan);
	menu[0].setString("Nowa gra");
	menu[0].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Wczytaj gre");
	menu[1].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Ostatnie wyniki");
	menu[2].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 3));

	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Wyjscie");
	menu[3].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 4));
}

//rysowanie menu w biezacym oknie
void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++)
	{
		window.draw(menu[i]);
	}
}


void Menu::przesunG()
{
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem--;
		if (selectedItem < 0)
			selectedItem = MAX_LICZBA_POZIOMOW - 1;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}


}

void Menu::przesunD()
{
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem++;
		if (selectedItem >= MAX_LICZBA_POZIOMOW)
			selectedItem = 0;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}

}

//funklcja opozniajaca
void myDelay(int opoznienie)
{
	sf::Clock zegar;
	sf::Time czas;
	while (1)
	{
		czas = zegar.getElapsedTime();
		if (czas.asMilliseconds() > opoznienie)
		{
			zegar.restart();
			break;
		}

	}
}


int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Arkanoid");
	window.setFramerateLimit(60);

	Menu menu(window.getSize().x, window.getSize().y);
	Game game;

	sf::Clock deltaClock;

	AppState currentState = AppState::Menu;

	int menu_selected_flag = 0;
	int lastScore = 0;

	// petla wieczna - dopoki okno jest otwarte
	while (window.isOpen())
	{
		sf::Time dt = deltaClock.restart();

		// w kazdej iteracji petli sprawdzaj zdarzenia
		sf::Event event;
		while (window.pollEvent(event))
		{
			// jezeli odebrano zdarzenie "Closed" zamknij okno
			if (event.type == sf::Event::Closed)
				window.close();

			switch (currentState) {
			case AppState::Menu:
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Up)
					{
						menu.przesunG();
					}
					else if (event.key.code == sf::Keyboard::Down)
					{
						menu.przesunD();
					}
					else if (event.key.code == sf::Keyboard::Enter)
					{
						int selected = menu.getSelectedItem();
						if (selected == 0) { //nowa gra
							game.resetScore();
							currentState = AppState::Playing;
							std::cout << "Uruchamiam gre..." << std::endl;
						}
						else if (selected == 1) {
							::GameState saveState;
							if (saveState.loadFromFile("zapis.txt")) {
								saveState.apply(game.getPaletka(), game.getPilka(), game.getCegly());
								currentState = AppState::Playing;
								std::cout << "Wczytano gre." << std::endl;
							}
							else {
								std::cerr << "Blad: Nie znaleziono pliku zapisu (zapis.txt)." << std::endl;
							}
						}
						else if (selected == 2) {
							currentState = AppState::Scores;
							std::cout << "Najlepsze wyniki..." << std::endl;
						}
						else if (selected == 3) {
							currentState = AppState::Exiting;
						}
					}
				}
				break;
			case AppState::Playing:
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::F5) { // wcisniecie f5 powoduje zapis
						::GameState saveState;
						saveState.capture(game.getPaletka(), game.getPilka(), game.getCegly(), game.getBlockSize());
						if (saveState.saveToFile("zapis.txt")) {
							std::cout << "Gra zostala zapisana." << std::endl;
						}
					}
				}
				break;
			case AppState::Scores:
				//powrot do menu przy wcisnieciu enter
				if (event.type == sf::Event::KeyPressed &&
					event.key.code == sf::Keyboard::Enter)
				{
					currentState = AppState::Menu;
				}
				break;
			case AppState::GameOver:
				//powrot do menu przy wcisnieciu enter
				if (event.type == sf::Event::KeyPressed &&
					event.key.code == sf::Keyboard::Enter)
				{
					currentState = AppState::Menu;
				}
				break;
			case AppState::Victory:
			{
				if (event.type == sf::Event::KeyPressed &&
					event.key.code == sf::Keyboard::Enter)
				{
					currentState = AppState::Menu;
				}
				break;
			}
			}

			
		}

		//logika stanu
		if (currentState == AppState::Playing) {
			game.update(dt);


			// czy pi³ka spad³a? jesli tak to przegrana
			if (game.getPilka().getPosition().y > 600) {
				lastScore = game.getScore();
				currentState = AppState::GameOver;
			}
		}

		bool wszystkieZniszczone = true;
		for (auto& c : game.getCegly()) {
			if (!c.czyZniszczony()) {
				wszystkieZniszczone = false;
				break;
			}
		}
		if (wszystkieZniszczone) {
			lastScore = game.getScore();
			currentState = AppState::Victory;
		}
		else if (currentState == AppState::Exiting) {
			window.close();
			return 0;
		}

		// rysowanie
		window.clear(sf::Color(40, 30, 20));

		switch (currentState)
		{
		case AppState::Menu:
			menu.draw(window);
			break;
		case AppState::Playing:
		{
			game.render(window);

			// wyswietlanie punktów
			{
				sf::Text wynikText("Punkty: " + std::to_string(game.getScore()), menu.getFont(), 24);
				wynikText.setFillColor(sf::Color::White);
				wynikText.setPosition(650, 10); // górny prawy róg
				window.draw(wynikText);
			}

			break;
		}
		case AppState::Scores:
		{
			sf::Text scoreText("Ostatni wynik: " + std::to_string(lastScore),
				menu.getFont(), 40);
			scoreText.setStyle(sf::Text::Bold);
			scoreText.setPosition(
				window.getSize().x / 2.f - scoreText.getGlobalBounds().width / 2.f,
				20
			);
			window.draw(scoreText);

			sf::Text scoreInfo("Nacisnij ENTER aby wrocic do menu",
				menu.getFont(), 30);
			scoreInfo.setFillColor(sf::Color::White);
			scoreInfo.setPosition(
				window.getSize().x / 2.f - scoreInfo.getGlobalBounds().width / 2.f,
				window.getSize().y - 50
			);
			window.draw(scoreInfo);

			break;
		}
		case AppState::GameOver:
		{
			sf::Text loseText("PRZEGRALES", menu.getFont(), 60);
			loseText.setStyle(sf::Text::Bold);
			loseText.setFillColor(sf::Color::Red);
			loseText.setPosition(
				window.getSize().x / 2.f - loseText.getGlobalBounds().width / 2.f,
				window.getSize().y / 2.f - 100
			);
			window.draw(loseText);

			sf::Text info("Nacisnij ENTER aby wrocic do menu",
				menu.getFont(), 30);
			info.setFillColor(sf::Color::White);
			info.setPosition(
				window.getSize().x / 2.f - info.getGlobalBounds().width / 2.f,
				window.getSize().y / 2.f + 10
			);
			window.draw(info);
		}
			break;
		case AppState::Victory:
		{
			sf::Text winText("KONIEC GRY: WYGRALES", menu.getFont(), 60);
			winText.setStyle(sf::Text::Bold);
			winText.setFillColor(sf::Color::Green);
			winText.setPosition(
				window.getSize().x / 2.f - winText.getGlobalBounds().width / 2.f,
				window.getSize().y / 2.f - 100
			);
			window.draw(winText);

			sf::Text info("Nacisnij ENTER aby wrocic do menu",
				menu.getFont(), 30);
			info.setFillColor(sf::Color::White);
			info.setPosition(
				window.getSize().x / 2.f - info.getGlobalBounds().width / 2.f,
				window.getSize().y / 2.f + 10
			);
			window.draw(info);
		}
		}

		// Ostatnia czynnoœæ: wyœwietl okno wraz z zawartoœci¹
		window.display();
		
	}
	return 0;
}
