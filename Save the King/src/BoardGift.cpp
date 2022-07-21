#include "BoardGift.h"








BoardGift::BoardGift(const sf::Sprite& sprite, const int type) : Gifts(sprite, false), m_type(type)
{
}

void BoardGift::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	//double dispatch
	gameObject.handleCollision(*this);
}

void BoardGift::handleCollision(King& gameObject)
{
	Resources::instance().playSound(take_gift);
	Gifts::activated();
	StaticObject::deleteObject();
	gameObject.handleCollision(*this);
}

void BoardGift::handleCollision(Mage& gameObject)
{
	Resources::instance().playSound(take_gift);
	Gifts::activated();
	StaticObject::deleteObject();
	gameObject.handleCollision(*this);
}

void BoardGift::handleCollision(Warrior& gameObject)
{
	Resources::instance().playSound(take_gift);
	Gifts::activated();
	StaticObject::deleteObject();
	gameObject.handleCollision(*this);
}

void BoardGift::handleCollision(Thief& gameObject)
{
	Resources::instance().playSound(take_gift);
	Gifts::activated();
	StaticObject::deleteObject();
	gameObject.handleCollision(*this);
}

void BoardGift::doYourThing(Controller&, std::vector<std::unique_ptr<Dwarf>>& dwarfs)
{
	if (m_type)
	{
		dwarfs.clear();
	}
	else
	{
		for (auto& object : dwarfs)
			object->slowDown();
	}
}