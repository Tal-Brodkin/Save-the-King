#include "Teleport.h"









Teleport::Teleport(const sf::Sprite& sprite) : StaticObject(sprite), m_activated(false)
{
}

void Teleport::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	//double dispatch
	gameObject.handleCollision(*this);
}

void Teleport::handleCollision(King& gameObject)
{
	m_activated = true;
	gameObject.handleCollision(*this);
}

void Teleport::handleCollision(Warrior& gameObject)
{
	m_activated = true;
	gameObject.handleCollision(*this);
}

void Teleport::handleCollision(Thief& gameObject)
{
	m_activated = true;
	gameObject.handleCollision(*this);
}

void Teleport::handleCollision(Dwarf& gameObject)
{
	m_activated = true;
	gameObject.handleCollision(*this);
}

void Teleport::setMatePosition(sf::Vector2f position)
{
	m_mate_position = position;
}

sf::Vector2f Teleport::getMatePosition()
{
	return m_mate_position;
}

bool Teleport::isActivated()
{
	return m_activated;
}

void Teleport::deactivate()
{
	m_activated = false;
}
