#include <SFML/Graphics.hpp>
#include "game.h"
#include <iostream>

#define MAX_LICZBA_POZIOMOW 3

enum class GameState { Menu, Playing, Scores, Exiting };

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
	menu[1].setString("Ostatnie wyniki");
	menu[1].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 2));
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Wyjscie");
	menu[2].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 3));
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

	GameState currentState = GameState::Menu;

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
			case GameState::Menu:
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Up)
					{
						myDelay(250);
						menu.przesunG();
					}
					else if (event.key.code == sf::Keyboard::Down)
					{
						myDelay(250);
						menu.przesunD();
					}
					else if (event.key.code == sf::Keyboard::Enter)
					{
						int selected = menu.getSelectedItem();
						if (selected == 0) { //nowa gra
							currentState = GameState::Playing;
							std::cout << "Uruchamiam gre..." << std::endl;
						}
						else if (selected == 1) {
							currentState = GameState::Scores;
							std::cout << "Najlepsze wyniki..." << std::endl;
						}
						else if (selected == 2) {
							currentState = GameState::Exiting;
						}
					}
				}
				break;
			case GameState::Playing:
				break;
			case GameState::Scores:
				break;
			}

			
		}

		//logika stanu
		if (currentState == GameState::Playing) {
			game.update(dt);
		}
		else if (currentState == GameState::Exiting) {
			window.close();
			return 0;
		}

		// rysowanie
		window.clear(sf::Color(40, 30, 20));

		switch (currentState)
		{
		case GameState::Menu:
			menu.draw(window);
			break;
		case GameState::Playing:
			game.render(window);
			break;
		case GameState::Scores:

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
