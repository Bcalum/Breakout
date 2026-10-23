#include "Bullet.h"
#include "CONSTANTS.h"
#include <cmath>

Bullet::Bullet(float x, float y, sf::Vector2f direction) : _velocity(direction * BULLET_SPEED), _isAlive(true)
{
	_shape.setSize(sf::Vector2f(BULLET_WIDTH, BULLET_HEIGHT));
	_shape.setOrigin(BULLET_WIDTH / 2.0f, 0.f);
	_shape.setFillColor(sf::Color::Yellow);
	_shape.setPosition(x , y);

	float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14f;
	_shape.setRotation(angle + 90.f);
}

void Bullet::update(float dt)
{
	_shape.move(_velocity * dt);
}

void Bullet::render(sf::RenderWindow& window)
{
	window.draw(_shape);
}

sf::FloatRect Bullet::getBounds() const
{
	return _shape.getGlobalBounds();
}