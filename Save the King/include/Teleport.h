#pragma once
#include "StaticObject.h"
#include "King.h"



class Teleport : public StaticObject
{
	sf::Vector2f m_mate_position;	//posiotn of the exit teleport
	bool m_activated;				//is the teleport was used

public:

	Teleport(const sf::Sprite&);

	sf::Vector2f getMatePosition();
	void setMatePosition(sf::Vector2f);
	void deactivate();
	bool isActivated();

	virtual void handleCollision(GameObject&) override;
	virtual void handleCollision(King&) override;
	virtual void handleCollision(Warrior&) override;
	virtual void handleCollision(Thief&) override;
	virtual void handleCollision(Dwarf&) override;
	
	void print() const override {};
};