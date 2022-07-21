#pragma once
#include "GameObject.h"




class StaticObject : public GameObject
{
	bool m_delete;			// need to be deleted if true
	bool m_replace;			// need to be replaced if true

public:

	StaticObject(const sf::Sprite&);

	bool toDelete();
	void deleteObject();

	bool toReplace();
	void replace();

	virtual void print() const = 0;
};