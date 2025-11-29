/*#pragma once
#include <sfml/graphics.hpp>
#include <pilka.h>
#include "paletka.h"
#include "cegla.h"
#include <fstream>
#include <string>

struct blockdata {
	float x, y;
	int hp;
};

class gamestate {
private:
	sf::Vector2f paddleposition;
	sf::Vector2f ballposition;
	sf::Vector2f ballvelocity;
	std::vector<blockdata> blocks;
public:
	void capture(const Paletka& paletka, const Pilka& pilka, const std::vector<Cegla>&);
	bool savetofile(const std::string& filename);
	bool loadfromfile(const std::string& filename);
};

void gamestate::capture(const Paletka& paletka, const Pilka& pilka, const std::vector<Cegla>&) {
	paddleposition.x = paletka.getX();
	paddleposition.y = paletka.getY();
	ballposition.x = pilka.getX();
	ballposition.y = pilka.getY();
	ballvelocity.x = pilka.getVelX();
	ballvelocity.y = pilka.getVelY();
}
bool gamestate::savetofile(const std::string& filename) {
	std::ofstream file(filename);
	if (!file.is_open()) return false;

	//zapis paletki
	file << paddleposition.x << " " << paddleposition.y << "\n";

	//zapis pilki
	file << ballposition.x << " " << ballposition.y << "\n"
		<< ballvelocity.x << " " << ballvelocity.y << "\n";

	//zapis liczby blokow
	file << blocks.size() << "\n";

	//zapis blokow
	for (const auto& block : blocks) {
		file << block.x << " " << block.y << " " << block.hp << "\n";
	}

	file.close();
	return true;
}

bool gamestate::loadfromfile(const std::string& filename) {

}*/