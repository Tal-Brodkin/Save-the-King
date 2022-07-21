#pragma once
#include "StaticObject.h"
#include "King.h"





class Throne : public StaticObject
{

public:

	Throne(const sf::Sprite&);

	virtual void handleCollision(GameObject&) override;
	virtual void handleCollision(King&) override;
	virtual void handleCollision(Mage&) override;
	virtual void handleCollision(Warrior&) override;
	virtual void handleCollision(Thief&) override;
	virtual void handleCollision(Dwarf&) override;

	void print() const override {};
};