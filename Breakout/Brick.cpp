#include "Brick.h"
#include <cmath>

namespace 
{
    sf::Texture& gunTexture() {
        static sf::Texture tex;
		static bool loaded = tex.loadFromFile("images/glock.png");
        (void)loaded;
        tex.setSmooth(true);
        return tex;
    }

    const float GUN_SCALE = 0.015f;
    const sf::Vector2f GUN_PIVOT(95.f, 44.f);
	const sf::Vector2f GUN_MUZZLE(254.f, 17.f);
}

Brick::Brick(float x, float y, float width, float height) : _isDestroyed(false)
{
    _shape.setPosition(x, y);
    _shape.setSize(sf::Vector2f(width, height));
    _shape.setFillColor(sf::Color::Red);

    // The Gun Stuff
	_gun.setTexture(gunTexture());
	_gun.setOrigin(GUN_PIVOT);
	_gun.setScale(GUN_SCALE, GUN_SCALE);
	_gun.setPosition(x + 18.f, y + height / 2.f);
}

void Brick::render(sf::RenderWindow& window)
{
    if (!_isDestroyed) {
        window.draw(_shape);
		window.draw(_gun);
    }
}

void Brick::aimAt(sf::Vector2f target)
{
    sf::Vector2f d = target - _gun.getPosition();
	float len = std::sqrt(d.x * d.x + d.y * d.y); 
    if (len < 1.f) return;

	_aimDir = d / len;
	_gun.setRotation(std::atan2(_aimDir.y, _aimDir.x) * 180.f / 3.14f);

    _gun.setScale(GUN_SCALE, d.x < 0 ? -GUN_SCALE : GUN_SCALE);
}

sf::Vector2f Brick::getGunPosition() const
{
    return _gun.getTransform().transformPoint(GUN_MUZZLE);
}

sf::FloatRect Brick::getBounds() const
{
    return _shape.getGlobalBounds();
}
