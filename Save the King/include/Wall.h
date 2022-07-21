#pragma once
#include "StaticObject.h"
//#include "Controller.h"
#include "King.h"
#include "Mage.h"
#include "Warrior.h"
#include "Thief.h"
#include "Dwarf.h"



class Wall : public StaticObject
{



public:

	Wall(const sf::Sprite&);

	virtual void handleCollision(GameObject&) override;
	virtual void handleCollision(King&) override;
	virtual void handleCollision(Mage&) override;
	virtual void handleCollision(Warrior&) override;
	virtual void handleCollision(Thief&) override;
	virtual void handleCollision(Dwarf&) override;

	void print() const override {};
};