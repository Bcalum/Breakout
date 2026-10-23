#pragma once
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"

enum class BrickType {
    Normal,
    Plain,
    Split,
    Big,
    Repeat,
    Dropper
    };

class Brick {
public:
    Brick(float x, float y, float width, float height, BrickType type);

	BrickType getType() const { return _type; }
	bool hasGun() const { return _type != BrickType::Plain; }

    void queueFollowUp();
    bool tickBurst(float dt);

	BrickType _type = BrickType::Normal;
    int _pendingShots = 0;
	float _burstTimer = 0.f;

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