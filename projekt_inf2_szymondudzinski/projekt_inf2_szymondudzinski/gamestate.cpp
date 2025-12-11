#include "gamestate.h"
#include "paletka.h"
#include "pilka.h"
#include "cegla.h"
#include <iostream>

void GameState::capture(const Paletka& p, const Pilka& b, const std::vector<Cegla>& cegly, sf::Vector2f blkSize) {
    paddlePosition = p.getPosition();
    ballPosition = b.getPosition();
    ballVelocity = b.getVelocity();
    blockSize = blkSize;
    blocks.clear();

    for (const auto& cegla : cegly) {
        if (!cegla.czyZniszczony()) {
            blocks.push_back({ cegla.getPosition().x, cegla.getPosition().y, cegla.getHP() });
        }
    }
}

bool GameState::saveToFile(const std::string& filename) const {

    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    // Zapis Paletki
    file << paddlePosition.x << " " << paddlePosition.y << "\n";

    // Zapis Pi³ki
    file << ballPosition.x << " " << ballPosition.y << " "
        << ballVelocity.x << " " << ballVelocity.y << "\n";

    // Zapis liczby bloków
    file << blocks.size() << "\n";

    // Zapis bloków
    for (const auto& block : blocks) {
        file << block.x << " " << block.y << " " << block.hp << "\n";
    }

    file.close();
    return true;
}

bool GameState::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Blad odczytu: nie mozna otworzyc pliku " << filename << std::endl;
        return false;
    }

    std::string label;
    blocks.clear();

    // 1. Wczytaj Paletkê
    if (file >> label >> paddlePosition.x >> paddlePosition.y) {
        // Dane wczytane do zmiennych tymczasowych w GameState
    }
    
    // 2. Wczytaj Pi³kê
    if (file >> label >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y) {
    }

    // 3. Wczytaj Bloki
    int blocksCount;
    file >> label >> blocksCount;

    blocks.clear(); // Czyœcimy stare dane
    for (int i = 0; i < blocksCount; ++i) {
        float x, y;
        int hp;
        file >> x >> y >> hp;
        blocks.push_back({ x, y, hp });
    }

    file.close();
    return true;
}

void GameState::apply(Paletka& p, Pilka& b, std::vector<Cegla>& cegly) {
    p.setPosition(paddlePosition);
    b.reset(ballPosition, ballVelocity);

    cegly.clear();
    for (const auto& data : blocks) {

    }
}