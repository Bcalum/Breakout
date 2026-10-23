#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    Brick(float x, float y, float width, float height);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    sf::Vector2f getGunPosition() const;
    sf::Vector2f getAimDirection() const { return _aimDir; }
    void aimAt(sf::Vector2f target);

private:
    sf::RectangleShape _shape;
    bool _isDestroyed;

    // Gun Variables & Methods
    sf::Sprite _gun;
	sf::Vector2f _aimDir = { 0.f, 1.f };
 };