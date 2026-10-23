#include "Brick.h"

Brick::Brick(float x, float y, float width, float height)
    : _isDestroyed(false)
{
    _shape.setPosition(x, y);
    _shape.setSize(sf::Vector2f(width, height));
    _shape.setFillColor(sf::Color::Red);

    // The Gun Stuff
	const float gunW = 8.0f, gunH = 8.0f;
	_gun.setSize(sf::Vector2f(gunW, gunH));
    _gun.setPosition(x + (width - gunW) / 2.0f, y + height);
	_gun.setFillColor(sf::Color(60,60,60));
}

void Brick::render(sf::RenderWindow& window)
{
    if (!_isDestroyed) {
		window.draw(_gun);
        window.draw(_shape);
    }
}

sf::Vector2f Brick::getGunPosition() const
{
    return _gun.getPosition();
}

sf::FloatRect Brick::getBounds() const
{
    return _shape.getGlobalBounds();
}
