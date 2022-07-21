#pragma once
#include "DynamicObject.h"




class Dwarf : public DynamicObject
{
	sf::Vector2f m_direction;	// direction of the dwarfs movement
	int m_speed;				// speed of the dwarfs movement
	float m_time;				// the time that passed since dwarf changed direction
	int m_type;					// the type of the dwarf. 0 - regular: changing direction every 2 seconds
								// 1 - smart: following the players character

public:

	Dwarf(const sf::Sprite&);

	void handleCollisionWithDynamic();

	virtual void handleCollision(GameObject&) override;
	virtual void handleCollision(Wall&) override;
	virtual void handleCollision(Fire&) override;
	virtual void handleCollision(Gate&) override;
	virtual void handleCollision(Orc&) override;
	virtual void handleCollision(Throne&) override;
	virtual void handleCollision(Teleport&) override;

	void move(const float, GameObject&);
	void slowDown();
	void changeDirection();
	sf::Vector2f getDirection() const;
};