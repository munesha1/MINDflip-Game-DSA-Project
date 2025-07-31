#include "Game.h"
#include "Card.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    const int gridSize = 4;
    Game game(gridSize);

    // Create window
    sf::RenderWindow window(sf::VideoMode(800, 600), "MindFlip Game");
    window.setFramerateLimit(60);

    // Load font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font! Make sure arial.ttf is in the same directory.\n";
        return EXIT_FAILURE;
    }

    // Create cards
    std::vector<std::vector<Card>> cards;
    float cardSize = 100.f;
    float padding = 10.f;
    float startX = (800.f - (gridSize * (cardSize + padding))) / 2.f;
    float startY = (600.f - (gridSize * (cardSize + padding))) / 2.f;

    for (int i = 0; i < gridSize; i++) {
        std::vector<Card> row;
        for (int j = 0; j < gridSize; j++) {
            row.emplace_back(
                startX + j * (cardSize + padding),
                startY + i * (cardSize + padding),
                game.getBoardSymbol(i, j),
                font
            );
        }
        cards.push_back(std::move(row));
    }

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(
                        { event.mouseButton.x, event.mouseButton.y });

                    for (int i = 0; i < gridSize; i++) {
                        for (int j = 0; j < gridSize; j++) {
                            if (cards[i][j].contains(mousePos)) {
                                game.handleCardClick(i, j);
                            }
                        }
                    }
                }
            }
        }

        game.update();
        window.clear(sf::Color(50, 50, 50)); // Dark gray background

        // Draw cards
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                if (game.isRevealed(i, j)) {  // Fixed: Added missing parenthesis
                    cards[i][j].reveal();
                }
                else if (game.isTemporarilyFlipped(i, j)) {
                    cards[i][j].reveal();
                }
                else {
                    cards[i][j].hide();
                }
                cards[i][j].draw(window);
            }
        }

        window.display();

        // Check for game completion
        if (game.isFinished()) {
            std::cout << "Congratulations! You completed the game!\n";
            sf::sleep(sf::seconds(3));
            window.close();
        }
    }

    return EXIT_SUCCESS;
}