#include "Fire.h"








Fire::Fire(const sf::Sprite& sprite) : StaticObject(sprite)
{
}

void Fire::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	//double dispatch
	gameObject.handleCollision(*this);
}

void Fire::handleCollision(King& gameObject)
{
	Resources::instance().playSound(burn);
	gameObject.handleCollision(*this);
}

void Fire::handleCollision(Mage&)
{
	Resources::instance().playSound(fire_extinguish);
	StaticObject::deleteObject();
}

void Fire::handleCollision(Warrior& gameObject)
{
	Resources::instance().playSound(burn);
	gameObject.handleCollision(*this);
}

void Fire::handleCollision(Thief& gameObject)
{
	Resources::instance().playSound(burn);
	gameObject.handleCollision(*this);
}

void Fire::handleCollision(Dwarf& gameObject)
{
	Resources::instance().playSound(burn);
	gameObject.handleCollision(*this);
}
