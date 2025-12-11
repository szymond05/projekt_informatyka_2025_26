#include <SFML/Graphics.hpp>
#include "game.h"
#include <gamestate.h>
#include <iostream>

#define MAX_LICZBA_POZIOMOW 4

enum class AppState { Menu, Playing, Scores, Exiting };

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
	menu[1].setString("Wczytaj grê");
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
					if (event.key.code == sf::Keyboard::F5) { // Zapis (F5)
						::GameState saveState;
						saveState.capture(game.getPaletka(), game.getPilka(), game.getCegly(), game.getBlockSize());
						if (saveState.saveToFile("zapis.txt")) {
							std::cout << "Gra zostala zapisana." << std::endl;
						}
					}
				}
				break;
			case AppState::Scores:
				break;
			}

			
		}

		//logika stanu
		if (currentState == AppState::Playing) {
			game.update(dt);
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
			game.render(window);
			break;
		case AppState::Scores:

			sf::Text scoreText("EKRAN WYNIKOW", menu.getFont(), 40);
			scoreText.setStyle(sf::Text::Bold);
			scoreText.setPosition(window.getSize().x / 2.f - scoreText.getGlobalBounds().width / 2.f,
				window.getSize().y / 2.f - scoreText.getGlobalBounds().height / 2.f);
			window.draw(scoreText);
			break;
		}
		// Ostatnia czynnoœæ: wyœwietl okno wraz z zawartoœci¹
		window.display();
		
	}
	return 0;
}
