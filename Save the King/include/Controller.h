#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "Menu.h"

//----------------------------------------------------
// Controller class - controls the technical running 
// of the game: menu loops, game loops, etc.
// Handles the cycling between the levels, 
// the control over the characters, etc.
//----------------------------------------------------

class Board;


class Controller
{
	sf::Time m_time;
	sf::RenderWindow* m_window;

	int m_player;
	int m_current_level;
	int m_current_level_characters;

	bool m_level_won;
	bool m_game_over;

	void startGame();
	void endMenu();
	void infoMenu(Menu&) const;
	void nextLevel(bool&);
	void changeCharacter(Board&);
	void setNumberOfCharacters(const Board&);
	void handleMouseHover(const sf::Vector2f&, Menu&);
	void handleMouseClick(const sf::Vector2f&, Menu&);

public:

	Controller();

	void run();
	void levelWon();
	void changeTime(const int);
	void nextLevel();

	sf::RenderWindow* getWindow() const;
	sf::Time getTime() const;

	int getLevel() const;
};