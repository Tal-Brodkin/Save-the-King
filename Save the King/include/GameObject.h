#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "io.h"


//----------------------------------------
// GameObject class - the base class for 
// almost all the objects on the screen
//----------------------------------------


class StaticObject;
class King;
class Mage;
class Warrior;
class Thief;
class Wall;
class Gate;
class Fire;
class Orc;
class Key;
class Teleport;
class Throne;
class Dwarf;
class TimeGift;
class BoardGift;

class GameObject
{
	sf::Sprite m_sprite;

public:

	GameObject(const sf::Sprite&);
	virtual ~GameObject() = default;

	sf::Sprite getSprite() const;
	sf::Vector2f getPosition() const;

	void draw(sf::RenderWindow*);
	void makeMove(const sf::Vector2f&);
	void setPosition(const sf::Vector2f&);
	void changeColor();

	bool checkCollision(const GameObject&) const;

	virtual void handleCollision(GameObject&) = 0;
	virtual void handleCollision(King&) {};
	virtual void handleCollision(Warrior&) {};
	virtual void handleCollision(Mage&) {};
	virtual void handleCollision(Dwarf&) {};
	virtual void handleCollision(Thief&) {};
	virtual void handleCollision(Wall&) {};
	virtual void handleCollision(Gate&) {};
	virtual void handleCollision(Fire&) {};
	virtual void handleCollision(Orc&) {};
	virtual void handleCollision(Key&) {};
	virtual void handleCollision(Teleport&) {};
	virtual void handleCollision(Throne&) {};
	virtual void handleCollision(TimeGift&) {};
	virtual void handleCollision(BoardGift&) {};
};