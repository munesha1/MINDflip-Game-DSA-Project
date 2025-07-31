#include "Card.h"

Card::Card(float x, float y, const std::string& symbol, sf::Font& font)
    : symbol(symbol) {
    // Set up card shape
    shape.setSize(sf::Vector2f(100.f, 100.f));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color::Black);

    // Set up card back
    backShape.setSize(sf::Vector2f(100.f, 100.f));
    backShape.setPosition(x, y);
    backShape.setFillColor(sf::Color::Blue);

    // Set up text
    text.setFont(font);
    text.setString("?"); // Default hidden state
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

    // Center text in card
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    text.setPosition(x + 50.f, y + 50.f); // Center of card
}

void Card::draw(sf::RenderWindow& window) {
    if (isRevealed) {
        window.draw(shape);
        window.draw(text);
    }
    else {
        window.draw(backShape);
        window.draw(text);
    }
}