#include "BrickManager.h"
#include "GameManager.h"

namespace 
{
    sf::Vector2f normalise(sf::Vector2f v)
    {
		float len = std::sqrt(v.x * v.x + v.y * v.y);
		return len > 0.f ? v / len : sf::Vector2f(0.f, 1.f);
    }
}

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
            _bricks.emplace_back(x, y, brickWidth, brickHeight, randomType());
        }
    }
}

BrickType BrickManager::randomType()
{
    int roll = rand() % 100;
    if (roll < 20) return BrickType::Plain;
    if (roll < 50) return BrickType::Normal;
    if (roll < 62) return BrickType::Split;
    if (roll < 74) return BrickType::Big;
    if (roll < 87) return BrickType::Repeat;
    return BrickType::Dropper;
}

// New Update function to control when the bullets are fired - Calum Brown
void BrickManager::update(float dt)
{
	sf::FloatRect paddleBounds = _gameManager->getPaddle()->getBounds();
	sf::Vector2f paddleCenter = { paddleBounds.left + paddleBounds.width / 2.0f, paddleBounds.top + paddleBounds.height / 2.0f};

    for (auto& brick : _bricks)
    {
        brick.aimAt(paddleCenter);
        if (brick.tickBurst(dt)) shoot(brick);
    }

	_fireTimer += dt;
    if (_fireTimer >= BULLET_FIRE_RATE && !_bricks.empty())
    {
		_fireTimer = 0.0f;
        fire();
    }

    sf::Vector2f windowSize(_window->getSize());
    sf::FloatRect screen(0.0f, 0.0f, windowSize.x, windowSize.y);

	// Bullet Collision Detection and Update - Calum Brown
    for (auto& bullet : _bullets)
    {
		bullet.update(dt);
        if (bullet.getBounds().intersects(paddleBounds))
        {
            bullet.destroy();
			_gameManager->loseLife();
        }
        else if (!bullet.getBounds().intersects(screen))
        {
            bullet.destroy();
        }
    }

    _bullets.erase(std::remove_if(_bullets.begin(), _bullets.end(), [](const Bullet& bullet) { return !bullet.isAlive(); }), _bullets.end());
}

// New Fire function to determine which bricks fire - Calum Brown
void BrickManager::fire()
{
    std::vector<Brick*> shooters;
    for (auto& brick : _bricks)
        if (brick.hasGun()) shooters.push_back(&brick);

    if (shooters.empty()) return;

    Brick* shooter = shooters[rand() % shooters.size()];
    shoot(*shooter);

    if (shooter->getType() == BrickType::Repeat)
        shooter->queueFollowUp();
}

// Shoot Function which fires a bullet in a specific way based on the brick type - Calum Brown
void BrickManager::shoot(Brick& brick)
{
    sf::Vector2f muzzle = brick.getGunPosition();
    sf::Vector2f dir = brick.getAimDirection();

    switch (brick.getType())
    {
    case BrickType::Big:
        _bullets.emplace_back(muzzle.x, muzzle.y, dir, BIG_SCALE);
        break;

    case BrickType::Split:
    {
        sf::FloatRect p = _gameManager->getPaddle()->getBounds();
        sf::Vector2f centre(p.left + p.width / 2.0f, p.top + p.height / 2.0f);

        for (float side : { -1.0f, 1.0f })
        {
            sf::Vector2f target(centre.x + side * SPLIT_OFFSET, centre.y);
            sf::Vector2f d = normalise(target - muzzle);
            _bullets.emplace_back(muzzle.x, muzzle.y, d);
        }
        break;
    }
    case BrickType::Normal:
    case BrickType::Repeat:
    case BrickType::Dropper:    
    default:
        _bullets.emplace_back(muzzle.x, muzzle.y, dir);
        break;
    }
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