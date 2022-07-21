#include "Throne.h"






Throne::Throne(const sf::Sprite& sprite) : StaticObject(sprite)
{
}

void Throne::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	//double dispatch
	gameObject.handleCollision(*this);
}

void Throne::handleCollision(King& gameObject)
{
	gameObject.handleCollision(*this);
}

void Throne::handleCollision(Mage& gameObject)
{
	gameObject.handleCollision(*this);
}

void Throne::handleCollision(Warrior& gameObject)
{
	gameObject.handleCollision(*this);
}

void Throne::handleCollision(Thief& gameObject)
{
	gameObject.handleCollision(*this);
}

void Throne::handleCollision(Dwarf& gameObject)
{
	gameObject.handleCollision(*this);
}

