#include "Gifts.h"








Gifts::Gifts(const sf::Sprite& sprite, const bool status) : StaticObject(sprite), m_activated(status)
{
}

void Gifts::activated()
{
	m_activated = true;
}

bool Gifts::isActivated()
{
	return m_activated;
}
