#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using std::vector, std::string, std::cerr, std::cout, std::endl;
#include "tiles.h"
#include "grid.h"

// updates score, only called on keypress
void updateScore(int *moves, sf::Text *score);
int main() {
    srand(time(0));
    // setting up grid
    const int DIMENSION = 4; // grid size, 4 recommended
    const int START_STAGE = 0; // starting point of tiles, 0 recommended

    int sizeScreen = 800; // must be divisible by dimension
    double scale   = 1.2; // reccomended to be 1 <--> 2
    sizeScreen *= scale;  // scales the size
    if (sizeScreen % 4 != 0) {
        cerr << "Unsupported resolution" << endl;
        return 1;
    }

    // setting up window
    sf::RenderWindow window(sf::VideoMode(sizeScreen+sizeScreen/2, sizeScreen), "2048");
    window.setKeyRepeatEnabled(false);

    int tileSize = sizeScreen / DIMENSION;
    Grid grid(DIMENSION, tileSize, START_STAGE);

    // sets up rightmost grey rectangle for score area
    sf::RectangleShape scoreRectangle;
    scoreRectangle.setSize(sf::Vector2f(sizeScreen/2, sizeScreen));
    scoreRectangle.setOutlineThickness(2);
    scoreRectangle.setOutlineColor(sf::Color(64, 69, 71, 255));
    scoreRectangle.setFillColor(sf::Color(99, 106, 110, 255));
    scoreRectangle.setPosition(tileSize*DIMENSION, 0);

    // sets up the score object
    sf::Font font;
    font.loadFromFile("to_load/ArialCE.ttf");
    sf::Text score;
    score.setFont(font);
    score.setFillColor(sf::Color(250, 245, 225, 255));
    score.setString("Score:");
    score.setCharacterSize(50*scale);
    score.setPosition(tileSize*DIMENSION+tileSize/4, tileSize/4);

    sf::Texture resetTexture;
    resetTexture.loadFromFile("to_load/reset2.png");
    resetTexture.setSmooth(true);
    sf::Sprite button;
    button.setTexture(resetTexture);
    button.setScale(1*scale,1*scale);
    button.setPosition(tileSize*DIMENSION+tileSize/4, tileSize*DIMENSION - tileSize/2);
    
    // updates score initially
    int numMoves = -1;
    bool gameOver = false;
    updateScore(&numMoves, &score);
    while (window.isOpen()) {
        gameOver = grid.gameOver();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || gameOver) {
                window.close();
                cout << "Game Over" << endl;
                cout << "Score: " << numMoves << endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                if (grid.left()) {
                    updateScore(&numMoves, &score);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                if (grid.right()) {
                    updateScore(&numMoves, &score);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                if (grid.up()) {
                    updateScore(&numMoves, &score);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                if (grid.down()) {
                    updateScore(&numMoves, &score);
                }
            }
            if ((sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
                sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                sf::FloatRect bounds = button.getGlobalBounds();
                // hit test
                if (bounds.contains(mouse)) {
                    numMoves = -1;
                    updateScore(&numMoves, &score);
                    grid.resetGrid();

                }
            }
        }
        // clears the screen for clean draw
        window.clear(sf::Color(82, 86, 87, 255));
        // draws all objects in the matrix
        for (int i = 0; i < DIMENSION; i++) {
            for (int j = 0; j < DIMENSION; j++) {
                if (grid.tiles[i][j] != nullptr) {
                    window.draw(*grid.tiles[i][j]);
                }
            }
        }
        window.draw(scoreRectangle);
        window.draw(score);
        window.draw(button);
        window.display();
    }
    return 0;
}



void updateScore(int *moves, sf::Text *score) {
    (*moves)++;

    string current = "Moves: ";
    string to_add = std::to_string(*moves);
    current.append(to_add);

    score->setString(current);

}
