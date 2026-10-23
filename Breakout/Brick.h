#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    Brick(float x, float y, float width, float height);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    sf::Vector2f getGunPosition() const;

private:
    sf::RectangleShape _shape;
    bool _isDestroyed;

    // New Gun Thing - may change this to an image of a glock later
    sf::RectangleShape _gun;

};