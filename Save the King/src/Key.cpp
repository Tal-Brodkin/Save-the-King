#include "Key.h"






Key::Key(const sf::Sprite& sprite) : StaticObject(sprite)
{
}

void Key::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	//double dispatch
	gameObject.handleCollision(*this);
}

void Key::handleCollision(Thief& gameObject)
{
	if (!gameObject.isThiefHasKey())
	{
		StaticObject::deleteObject();
		gameObject.handleCollision(*this);
	}
}
