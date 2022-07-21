#pragma once
#include "DynamicObject.h"
#include "Wall.h"




class Mage : public DynamicObject
{

public:

	Mage(const sf::Sprite&);

	virtual void handleCollision(GameObject&) override;
	virtual void handleCollision(Wall&) override;
	virtual void handleCollision(Gate&) override;
	virtual void handleCollision(Orc&) override;
	virtual void handleCollision(Throne&) override;
	virtual void handleCollision(Dwarf&) override;
	virtual void handleCollision(TimeGift&) override {};
	virtual void handleCollision(BoardGift&) override {};
};