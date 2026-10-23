#include "Bullet.h"
#include "CONSTANTS.h"

Bullet::Bullet(float x, float y) : _isAlive(true)
{
	_shape.setSize(sf::Vector2f(BULLET_WIDTH, BULLET_HEIGHT));
	_shape.setOrigin(BULLET_WIDTH / 2.0f, 0.f);
	_shape.setFillColor(sf::Color::Red);
	_shape.setPosition(x , y);
}

void Bullet::update(float dt)
{
	_shape.move(0.f, BULLET_SPEED * dt);
}

void Bullet::render(sf::RenderWindow& window)
{
	window.draw(_shape);
}

sf::FloatRect Bullet::getBounds() const
{
	return _shape.getGlobalBounds();
}