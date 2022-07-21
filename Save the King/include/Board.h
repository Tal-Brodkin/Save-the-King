#pragma once
#include "TimeGift.h"
#include "BoardGift.h"
#include "DynamicObject.h"
#include "StaticObject.h"
#include "io.h"
#include <vector>
#include <string>

//-------------------------------------------------------------
// Board class -  handles the visuals as all the objects 
// on the screen, moving and collisions of the objects, 
// deletion of objects from the screen and the information bar
//-------------------------------------------------------------

const int MAP_SCALE = 64;


class Controller;


class Board
{
	sf::RectangleShape m_board;
	sf::Vector2f m_board_size;
	sf::Vector2f m_board_position;
	sf::Sprite m_background;

	std::vector<std::unique_ptr<DynamicObject>> m_dynamic_objects;
	std::vector<std::unique_ptr<StaticObject>> m_static_objects;
	std::vector<std::unique_ptr<Dwarf>> m_dwarfs;

	bool m_key;

	void createGifts();
	void drawInfo(Controller&);
	void connectPortals() const;
	void handleCollisions(GameObject&);
	void handleMap(Controller&, DynamicObject&);
	void createObject(const ObjectType&, const sf::Vector2f&);

	std::vector<std::string> buildMap(const std::string&);

	int absolutPosition_x(const int) const;
	int absolutPosition_y(const int) const;

public:

	Board(const sf::RenderWindow*, const int);

	void draw(Controller&);
	void move(const int, const float, const float, Controller&);
	void moveDwarfs(const float, const int) const;
	void changePlayersVisual(const int) const;

	int getNumberOfCharacters() const;
};