#include "Orc.h"









Orc::Orc(const sf::Sprite& sprite) : StaticObject(sprite)
{
}

void Orc::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	//double dispatch
	gameObject.handleCollision(*this);
}

void Orc::handleCollision(King& gameObject)
{
	gameObject.handleCollision(*this);
}

void Orc::handleCollision(Mage& gameObject)
{
	gameObject.handleCollision(*this);
}

void Orc::handleCollision(Warrior&)
{
	Resources::instance().playSound(sword);
	StaticObject::replace();
}

void Orc::handleCollision(Thief& gameObject)
{
	gameObject.handleCollision(*this);
}

void Orc::handleCollision(Dwarf& gameObject)
{
	gameObject.handleCollision(*this);
}
