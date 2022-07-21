#pragma once
#include "Gifts.h"
#include "Thief.h"



class BoardGift : public Gifts
{
	int m_type;

public:

	BoardGift() = default;
	BoardGift(const sf::Sprite&, const int);

	virtual void handleCollision(GameObject&) override;
	virtual void handleCollision(King&) override;
	virtual void handleCollision(Mage&) override;
	virtual void handleCollision(Warrior&) override;
	virtual void handleCollision(Thief&) override;

	void print() const override {};

	void doYourThing(Controller&, std::vector<std::unique_ptr<Dwarf>>&) override;
};