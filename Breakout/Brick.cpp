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

Brick::Brick(float x, float y, float width, float height, BrickType type) : _isDestroyed(false)
{
	_type = type;
    _shape.setPosition(x, y);
    _shape.setSize(sf::Vector2f(width, height));

    switch (_type)
    {
    case BrickType::Normal: _shape.setFillColor(sf::Color::Red); break;
        break;
    case BrickType::Plain: _shape.setFillColor(sf::Color(120, 120, 120)); break;
        break;
    case BrickType::Split: _shape.setFillColor(sf::Color(160, 60, 200)); break;
        break;
    case BrickType::Big: _shape.setFillColor(sf::Color(255, 140, 0)); break;
        break;
    case BrickType::Repeat: _shape.setFillColor(sf::Color(0, 150, 255)); break;
        break;
    case BrickType::Dropper: _shape.setFillColor(sf::Color(60, 200, 80)); break;
        break;
    default:
        break;
    }

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
		if (hasGun()) window.draw(_gun);
    }
}

void Brick::aimAt(sf::Vector2f target)
{
    if (!hasGun()) return;

    sf::Vector2f d = (_type == BrickType::Dropper) ? sf::Vector2f(0.f, 1.f) : target - _gun.getPosition();
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

void Brick::queueFollowUp()
{
	_pendingShots = 1;
    _burstTimer = REPEAT_DELAY;
}

bool Brick::tickBurst(float dt)
{
	if (_pendingShots <= 0) return false;
	_burstTimer -= dt;
    if (_burstTimer > 0.f) return false;
    --_pendingShots;
    return true;
}