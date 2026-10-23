#include "BrickManager.h"
#include "GameManager.h"

BrickManager::BrickManager(sf::RenderWindow* window, GameManager* gameManager)
    : _window(window), _gameManager(gameManager)
{
}

void BrickManager::createBricks(int rows, int cols, float brickWidth, float brickHeight, float spacing)
{
    float leftEdge;
    if (cols % 2 == 0) 
        leftEdge = _window->getSize().x / 2 - ((cols / 2.0f) * brickWidth + (cols / 2.0f - 0.5f) * spacing);
    else
        leftEdge = _window->getSize().x / 2 - ((cols / 2.0f - 0.5f) * brickWidth + (cols / 2.0f) * spacing);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            float x = j * (brickWidth + spacing) + leftEdge;
            float y = i * (brickHeight + spacing) + TOP_PADDING;
            _bricks.emplace_back(x, y, brickWidth, brickHeight);
        }
    }
}

// New Update function to control when the bullets are fired - Calum Brown
void BrickManager::update(float dt)
{
	_fireTimer += dt;
    if (_fireTimer >= BULLET_FIRE_RATE && !_bricks.empty())
    {
		_fireTimer = 0.0f;
        fire();
    }

	sf::FloatRect paddleBounds = _gameManager->getPaddle()->getBounds();
	float windowHeight = static_cast<float>(_window->getSize().y);


	// Bullet Collision Detection and Update - Calum Brown
    for (auto& bullet : _bullets)
    {
		bullet.update(dt);
        if (bullet.getBounds().intersects(paddleBounds))
        {
            bullet.destroy();
			_gameManager->loseLife();
        }
        else if (bullet.getBounds().top > windowHeight)
        {
            bullet.destroy();
        }
    }

    _bullets.erase(std::remove_if(_bullets.begin(), _bullets.end(), [](const Bullet& bullet) { return !bullet.isAlive(); }), _bullets.end());
}

// New Fire function for the bricks to shoot bullets - Calum Brown
void BrickManager::fire()
{
    std::vector<const Brick*> shooters;
    for (const auto& a : _bricks)
    {
		bool blocked = false;
        for (const auto& b : _bricks)
        {
            if (&a == &b) continue;
            if (std::abs(a.getBounds().left - b.getBounds().left) < 1.f && b.getBounds().top > a.getBounds().top)
            {
                blocked = true;
				break;
            }
        }
		if (!blocked) shooters.push_back(&a);
    }

    if (shooters.empty()) return;

	sf::Vector2f gunPosition = shooters[rand() % shooters.size()]->getGunPosition();
	_bullets.emplace_back(gunPosition.x, gunPosition.y);
}

void BrickManager::render()
{
    for (auto& brick : _bricks) {
        brick.render(*_window);
    }
    for (auto& bullet : _bullets) {
		bullet.render(*_window);
    }
}

int BrickManager::checkCollision(sf::CircleShape& ball, sf::Vector2f& direction)
{
    int collisionResponse = 0;  // set to 1 for horizontal collision and 2 for vertical.
    for (auto& brick : _bricks) {
        if (!brick.getBounds().intersects(ball.getGlobalBounds())) continue;    // no collision, skip.

        sf::Vector2f ballPosition = ball.getPosition();
        float ballY = ballPosition.y + 0.5f * ball.getGlobalBounds().height;
        sf::FloatRect brickBounds = brick.getBounds();

        // default vertical bounce (collision is top/bottom)
        collisionResponse = 2;
        if (ballY > brickBounds.top && ballY < brickBounds.top + brickBounds.height)
            // unless it's horizontal (collision from side)
            collisionResponse = 1;

        // Mark the brick as destroyed (for simplicity, let's just remove it from rendering)
        // In a complete implementation, you would set an _isDestroyed flag or remove it from the vector
        brick = _bricks.back();
        _bricks.pop_back();
        break;
    }
    if (_bricks.size() == 0)
    {
        _gameManager->levelComplete();
    }
    return collisionResponse;
}