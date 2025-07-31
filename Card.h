#ifndef CARD_H
#define CARD_H

#include <SFML/Graphics.hpp>
#include <string>

class Card {
private:
    sf::RectangleShape shape;
    sf::RectangleShape backShape;
    sf::Text text;
    std::string symbol;
    bool isRevealed = false;

public:
    Card(float x, float y, const std::string& symbol, sf::Font& font);

    void draw(sf::RenderWindow& window);
    void reveal() {
        isRevealed = true;
        text.setString(symbol);
    }
    void hide() {
        isRevealed = false;
        text.setString("?");
    }
    bool contains(sf::Vector2f point) {
        return shape.getGlobalBounds().contains(point);
    }

    std::string getSymbol() const { return symbol; }
    bool getIsRevealed() const { return isRevealed; }
};

#endif // CARD_H