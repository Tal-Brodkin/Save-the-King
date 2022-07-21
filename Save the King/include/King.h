#pragma once
#include <SFML/Audio.hpp>
#include "DynamicObject.h"
#include "Wall.h"




class King : public DynamicObject
{
	bool m_throne;		//is the king reached the trone

public:

	King(const sf::Sprite&);

	virtual void handleCollision(GameObject&) override;
	virtual void handleCollision(Wall&) override;
	virtual void handleCollision(Gate&) override;
	virtual void handleCollision(Fire&) override;
	virtual void handleCollision(Orc&) override;
	virtual void handleCollision(Teleport&) override;
	virtual void handleCollision(Dwarf&) override;
	virtual void handleCollision(Throne&) override;
	virtual void handleCollision(TimeGift&) override {};
	virtual void handleCollision(BoardGift&) override {};

	bool isKingReachedThrone();
};