#pragma once
#include "DynamicObject.h"
#include "Wall.h"
#include "Gate.h"
#include "Fire.h"
#include "Throne.h"


class StaticObjects;


class Warrior : public DynamicObject
{

public:

	Warrior(const sf::Sprite&);

	virtual void handleCollision(GameObject&) override;
	virtual void handleCollision(Wall&) override;
	virtual void handleCollision(Gate&) override;
	virtual void handleCollision(Fire&) override;
	virtual void handleCollision(Throne&) override;
	virtual void handleCollision(Teleport&) override;
	virtual void handleCollision(Dwarf&) override;
	virtual void handleCollision(TimeGift&) override {};
	virtual void handleCollision(BoardGift&) override {};
};