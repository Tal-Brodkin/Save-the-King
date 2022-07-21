#pragma once
#include "GameObject.h"






class DynamicObject : public GameObject
{
	sf::Vector2f m_previous_position;	// previous position of the object

public:

	DynamicObject(const sf::Sprite&);

	void setPreviousPosition(const sf::Vector2f&);
	sf::Vector2f getPreviousPosition() const;
};