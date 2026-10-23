#pragma once
#include <SFML/Graphics.hpp>
//Every Bullet hell needs bullets.
class Bullet
{
public:
	Bullet(float x, float y);
	void update(float dt);
	void render(sf::RenderWindow& window);
	sf::FloatRect getBounds() const;
	bool isAlive() const { return _isAlive; }
	void destroy() { _isAlive = false; }

private:
	sf::RectangleShape _shape;
	bool _isAlive;
};

