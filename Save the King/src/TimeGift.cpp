#include "TimeGift.h"








TimeGift::TimeGift(const sf::Sprite& sprite, const int time) : Gifts(sprite, false), m_time(time)
{
}

void TimeGift::handleCollision(GameObject& gameObject)
{
	if (&gameObject == this) return;
	//double dispatch
	gameObject.handleCollision(*this);
}

void TimeGift::handleCollision(King& gameObject)
{
	Resources::instance().playSound(take_gift);
	Gifts::activated();
	StaticObject::deleteObject();
	gameObject.handleCollision(*this);
}

void TimeGift::handleCollision(Mage& gameObject)
{
	Resources::instance().playSound(take_gift);
	Gifts::activated();
	StaticObject::deleteObject();
	gameObject.handleCollision(*this);
}

void TimeGift::handleCollision(Warrior& gameObject)
{
	Resources::instance().playSound(take_gift);
	Gifts::activated();
	StaticObject::deleteObject();
	gameObject.handleCollision(*this);
}

void TimeGift::handleCollision(Thief& gameObject)
{
	Resources::instance().playSound(take_gift);
	Gifts::activated();
	StaticObject::deleteObject();
	gameObject.handleCollision(*this);
}

void TimeGift::doYourThing(Controller& controller, std::vector<std::unique_ptr<Dwarf>>&)
{
	controller.changeTime(m_time);
}
