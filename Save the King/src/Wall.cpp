#include "Wall.h"









Wall::Wall(const sf::Sprite& sprite) : StaticObject(sprite)
{
}

void Wall::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	//double dispatch
	gameObject.handleCollision(*this);
}

void Wall::handleCollision(King& gameObject)
{
	gameObject.handleCollision(*this);
}

void Wall::handleCollision(Mage& gameObject)
{
	gameObject.handleCollision(*this);
}

void Wall::handleCollision(Warrior& gameObject)
{
	gameObject.handleCollision(*this);
}

void Wall::handleCollision(Thief& gameObject)
{
	gameObject.handleCollision(*this);
}

void Wall::handleCollision(Dwarf& gameObject)
{
	gameObject.handleCollision(*this);
}
