#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using std::vector, std::string, std::cerr, std::cout, std::endl;
#include "tiles.h"
#include "grid.h"

int main() {
    srand(time(0));
    // setting up grid
    const int DIMENSION = 4; // grid size, 4 recommended
    const int START_STAGE = 0; // starting point of tiles, 0 recommended

    int sizeScreen = 800; // must be divisible by dimension
    double scale   = 1.2; // reccomended to be 1 <--> 2
    sizeScreen *= scale;
    if (sizeScreen % 4 != 0) {
        cerr << "Unsupported resolution" << endl;
        return 1;
    }

    // setting up window
    sf::RenderWindow window(sf::VideoMode(sizeScreen, sizeScreen), "2048");
    window.setKeyRepeatEnabled(false);

    int tileSize = sizeScreen / DIMENSION;
    Grid grid(DIMENSION, tileSize, START_STAGE);
    grid.show();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                cout << "Game Over" << endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                grid.left();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                grid.right();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                grid.up();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                grid.down();
            }
        }
        // clears the screen for clean draw
        window.clear();
        // draws all objects in the matrix
        for (int i = 0; i < DIMENSION; i++) {
            for (int j = 0; j < DIMENSION; j++) {
                if (grid.tiles[i][j] != nullptr) {
                    window.draw(*grid.tiles[i][j]);
                }
            }
        }
        window.display();
    }
    return 0;
}