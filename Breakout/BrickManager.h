#pragma once
#include <vector>
#include "Brick.h"
#include <SFML/Graphics.hpp>
#include "Bullet.h"

class GameManager;

class BrickManager {
public:
    BrickManager(sf::RenderWindow* window, GameManager* gameManager);
	void update(float dt);
    void createBricks(int rows, int cols, float brickWidth, float brickHeight, float spacing);
    void render();
    int checkCollision(sf::CircleShape& ball, sf::Vector2f& direction);

private:
    std::vector<Brick> _bricks;
    sf::RenderWindow* _window;
    void fire();
	std::vector<Bullet> _bullets;
	float _fireTimer = 0.0f;

    GameManager* _gameManager;
    static constexpr float TOP_PADDING = 100.0f;
};

// Included the intended info needed from Bullets - Calum Brown