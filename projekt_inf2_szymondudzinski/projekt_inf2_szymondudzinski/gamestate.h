#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>

#include "pilka.h"
#include "paletka.h"
#include "cegla.h"

struct BlockData {
    float x, y;
    int hp;
};

class GameState {
private:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;
    sf::Vector2f blockSize;

public:
    void capture(const Paletka& p, const Pilka& b, const std::vector<Cegla>& cegly, sf::Vector2f blkSize);
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
    void apply(Paletka& p, Pilka& b, std::vector<Cegla>& cegly);
};