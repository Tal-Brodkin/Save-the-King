#pragma once
#include "StaticObject.h"
#include "Thief.h"



class Key : public StaticObject
{


public:

	Key(const sf::Sprite&);

	virtual void handleCollision(GameObject&) override;
	virtual void handleCollision(Thief&) override;

	void print() const override {};
};