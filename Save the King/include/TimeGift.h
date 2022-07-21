#pragma once
#include "Gifts.h"
#include "King.h"




class TimeGift : public Gifts
{
	int m_time;		//how much time the gift will give

public:

	TimeGift(const sf::Sprite&, const int);

	virtual void handleCollision(GameObject&) override;
	virtual void handleCollision(King&) override;
	virtual void handleCollision(Mage&) override;
	virtual void handleCollision(Warrior&) override;
	virtual void handleCollision(Thief&) override;

	void doYourThing(Controller&, std::vector<std::unique_ptr<Dwarf>>&) override;

	void print() const override {};
};