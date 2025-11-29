#include <SFML/Graphics.hpp>
#include <array>

class Cegla : public sf::RectangleShape {
private:
	int punktyZycia;//0-3
	bool jestZniszczony;//zniszczony = true
	static const std::array<sf::Color, 4> colorLUT;


public:
	Cegla(sf::Vector2f startPos, sf::Vector2f rozmiar, int L);
	void aktualizujKolor();
	void trafienie();
	void draw(sf::RenderTarget& window);
	bool czyZniszczony() const { return jestZniszczony; };
	int getHP();
};

