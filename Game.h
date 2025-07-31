#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <SFML/System.hpp>

class Game {
public:
    Game(int gridSize);

    void initializeBoard();
    void displayBoard();
    bool flipCards(int row1, int col1, int row2, int col2);
    bool isFinished() const;
    std::string getBoardSymbol(int row, int col) const;
    int getSize() const;
    bool isRevealed(int row, int col) const;
    bool isTemporarilyFlipped(int row, int col) const;
    void handleCardClick(int row, int col);
    void update();

private:
    void resetTemporarilyFlipped();

    int size;
    int moves;
    bool isWaiting;
    sf::Vector2i firstFlippedCard;
    sf::Clock flipClock;
    std::vector<std::vector<std::string>> board;
    std::vector<std::vector<bool>> revealed;
    std::vector<std::vector<bool>> temporarilyFlipped;
};

#endif // GAME_H