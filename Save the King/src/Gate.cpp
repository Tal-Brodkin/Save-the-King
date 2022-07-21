#include "Gate.h"









Gate::Gate(const sf::Sprite& sprite) : StaticObject(sprite)
{
}

void Gate::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	//double dispatch
	gameObject.handleCollision(*this);
}

void Gate::handleCollision(King& gameObject)
{
	gameObject.handleCollision(*this);
}

void Gate::handleCollision(Mage& gameObject)
{
	gameObject.handleCollision(*this);
}

void Gate::handleCollision(Warrior& gameObject)
{
	gameObject.handleCollision(*this);
}

void Gate::handleCollision(Thief& gameObject)
{
	gameObject.handleCollision(*this);
}

void Gate::handleCollision(Dwarf& gameObject)
{
	gameObject.handleCollision(*this);
}
