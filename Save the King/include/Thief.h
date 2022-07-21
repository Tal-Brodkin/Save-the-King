#pragma once
#include "DynamicObject.h"
#include "Wall.h"
#include "Gate.h"
#include "Fire.h"
#include "Orc.h"
#include "Key.h"
#include "Teleport.h"
#include "Throne.h"
#include "Dwarf.h"




class Thief : public DynamicObject
{
	bool m_key;		//is the thief has a key

public:

	Thief(const sf::Sprite&);

	virtual void handleCollision(GameObject&) override;
	virtual void handleCollision(Wall&) override;
	virtual void handleCollision(Gate&) override;
	virtual void handleCollision(Fire&) override;
	virtual void handleCollision(Orc&) override;
	virtual void handleCollision(Key&) override;
	virtual void handleCollision(Throne&) override;
	virtual void handleCollision(Teleport&) override;
	virtual void handleCollision(Dwarf&) override;
	virtual void handleCollision(TimeGift&) override {};
	virtual void handleCollision(BoardGift&) override {};

	bool isThiefHasKey();
};