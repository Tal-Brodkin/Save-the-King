#pragma once
#include "StaticObject.h"
#include "Controller.h"



class Gifts : public StaticObject
{
	bool m_activated;		//is gift was taken

public:

	Gifts(const sf::Sprite&, const bool);

	void activated();
	bool isActivated();

	virtual void doYourThing(Controller&, std::vector<std::unique_ptr<Dwarf>>&) = 0;
};