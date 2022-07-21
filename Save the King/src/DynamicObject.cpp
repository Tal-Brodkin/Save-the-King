#include "DynamicObject.h"






DynamicObject::DynamicObject(const sf::Sprite& sprite) : GameObject(sprite), m_previous_position(0.f,0.f)
{
}

void DynamicObject::setPreviousPosition(const sf::Vector2f& position)
{
	m_previous_position = position;
}

sf::Vector2f DynamicObject::getPreviousPosition() const
{
	return m_previous_position;
}



