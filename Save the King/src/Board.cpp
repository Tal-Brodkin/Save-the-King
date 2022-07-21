#include "Board.h"
#include "Controller.h"
#include "Resources.h"



//the constructor - creates all the visual objects on the screen
Board::Board(const sf::RenderWindow* window, const int level)
{	
	//background image
	m_background.setTexture(Resources::instance().getTexture(background));
	m_key = false;

	//creates a specific level (vector of string)
	auto map = Resources::instance().buildMap(level);
	int cals = (int)map[0].size();
	int rows = (int)map.size();

	//actual board size on the window, dependes of the real size from the level's file.
	//not handled if is to big for the screen
	m_board_size = sf::Vector2f((float)cals * MAP_SCALE, (float)rows * MAP_SCALE);

	//board position - centered in the center of the window
	m_board_position = sf::Vector2f(window->getSize().x / 2.f, window->getSize().y / 2.f);
	
	//board frame
	m_board = sf::RectangleShape(m_board_size);

	//board inside color - half transperent white
	m_board.setFillColor(sf::Color(255, 255, 255, 128));

	//board origin set to center
	m_board.setOrigin(m_board_size / 2.f);
	m_board.setPosition(m_board_position);

	//goes through the string vector of the map and read char by char
	for (int row = 0; row < rows; row++)
		for (int cal = 0; cal < cals; cal++)
		{
			//creates the correct position on the screen according to the position of the object in the vector
			int x = absolutPosition_x(cal);
			int y = absolutPosition_y(row);
			char c = map[row][cal];
			//creates the object by his type
			createObject((ObjectType)c, sf::Vector2f((float)x, (float)y));
		}

	//connects between the teleports
	connectPortals();

	//creates the different gits
	createGifts();
}

//main function of drawing all the objects on the screen
void Board::draw(Controller& controller)
{
	auto window = controller.getWindow();

	window->draw(m_background);	//background
	drawInfo(controller);		//info bar
	window->draw(m_board);		//game board

	for (auto& object : m_static_objects)
		object->draw(window);	//all the static objects
	for (auto& object : m_dynamic_objects)
		object->draw(window);	//all the dynamic objects
	for (auto& object : m_dwarfs)
		object->draw(window);	//dwarfs
}

//main function that handles the movement
void Board::move(const int player, const float x, const float y, Controller& controller)
{
	//saves the previous position. all the collisions handeled in the way
	m_dynamic_objects[player]->setPreviousPosition(m_dynamic_objects[player]->getPosition());

	//all the collisions handled in the way that first we do the move and then we check if the move
	//was legal, if not - the carachter goes back to his previous position
	m_dynamic_objects[player]->makeMove(sf::Vector2f(x, y));

	//handles all the collisions
	handleCollisions(*m_dynamic_objects[player]);

	//handles all the event on the map
	handleMap(controller, *m_dynamic_objects[player]);
}

void Board::handleCollisions(GameObject& gameObject)
{
	//checks collision between the character and all the static objects
	for (auto& unmovable : m_static_objects)
	{
		if (gameObject.checkCollision(*unmovable))
		{
			gameObject.handleCollision(*unmovable);
		}
	}
	//checks collision between the character and the dwarfs
	for (auto& movable : m_dwarfs)
	{
		if (gameObject.checkCollision(*movable))
		{
			gameObject.handleCollision(*movable);
		}
	}
}

//creates the dynamic objects
static std::unique_ptr<DynamicObject> createDynamicObject(ObjectType type, 
														const sf::Vector2f& position, 
														const std::vector<sf::Texture>& textures)
{
	auto sprite = sf::Sprite();
	sprite.setPosition(position);

	switch (type)
	{
	case ObjectType::KingObject:
		sprite.setTexture(textures[king]);
		return std::make_unique<King>(sprite);
	case ObjectType::MageObject:
		sprite.setTexture(textures[mage]);
		return std::make_unique<Mage>(sprite);
	case ObjectType::WarriorObject:
		sprite.setTexture(textures[warrior]);
		return std::make_unique<Warrior>(sprite);
	case ObjectType::ThiefObject:
		sprite.setTexture(textures[thief]);
		return std::make_unique<Thief>(sprite);
	}
	return nullptr;
}

//creates the static objects
static std::unique_ptr<StaticObject> createStaticleObject(ObjectType type, 
														const sf::Vector2f& position, 
														const std::vector<sf::Texture>& textures)
{
	auto sprite = sf::Sprite();
	sprite.setPosition(position);

	switch (type)
	{
	case ObjectType::WallObject:
		sprite.setTexture(textures[wall]);
		return std::make_unique<Wall>(sprite);
	case ObjectType::GateObject:
		sprite.setTexture(textures[gate]);
		return std::make_unique<Gate>(sprite);
	case ObjectType::FireObject:
		sprite.setTexture(textures[fire]);
		return std::make_unique<Fire>(sprite);
	case ObjectType::OrcObject:
		sprite.setTexture(textures[orc]);
		return std::make_unique<Orc>(sprite);
	case ObjectType::KeyObject:
		sprite.setTexture(textures[key]);
		return std::make_unique<Key>(sprite);
	case ObjectType::PortalObject:
		sprite.setTexture(textures[teleport]);
		return std::make_unique<Teleport>(sprite);
	case ObjectType::ThroneObject:
		sprite.setTexture(textures[throne]);
		return std::make_unique<Throne>(sprite);
	}
	return nullptr;
}

//creates the dwarfs
static std::unique_ptr<Dwarf> createDwarfObject(ObjectType type,
												const sf::Vector2f& position,
												const std::vector<sf::Texture>& textures)
{
	auto sprite = sf::Sprite();
	sprite.setPosition(position);

	switch (type)
	{
	case ObjectType::DwarfObject:
		sprite.setTexture(textures[dwarf]);
		return std::make_unique<Dwarf>(sprite);
	}
	return nullptr;
}

//the function receives the object and inserts to the correct vector
void Board::createObject(const ObjectType& type, const sf::Vector2f& position)
{
	auto& textures = Resources::instance().getTextures();

	std::unique_ptr<DynamicObject> dynamicObg = createDynamicObject(type, position, textures);
	if (dynamicObg)
	{
		m_dynamic_objects.push_back(std::move(dynamicObg));
		return;
	}

	std::unique_ptr<StaticObject> staticObg = createStaticleObject(type, position, textures);
	if (staticObg)
	{
		m_static_objects.push_back(std::move(staticObg));
		return;
	}

	std::unique_ptr<Dwarf> dwarfObg = createDwarfObject(type, position, textures);
	if (dwarfObg)
	{
		m_dwarfs.push_back(std::move(dwarfObg));
		return;
	}
}

//handles all the event on the board before the visual gets updated
void Board::handleMap(Controller& controller, DynamicObject& gameObject)
{
	for (int i = 0; i < m_dynamic_objects.size(); i++)
	{
		DynamicObject* p = m_dynamic_objects[i].get();

		//checks if king reached the throne
		King* king = dynamic_cast<King*>(p);
		if (king)
		{
			if (king->isKingReachedThrone())
			{
				controller.levelWon();
			}
		}

		//checks if the thief has a key
		Thief* thief = dynamic_cast<Thief*>(p);
		if (thief)
		{
			if (thief->isThiefHasKey())
				m_key = true;
			else
				m_key = false;
		}
	}

	for (int i = 0; i < m_static_objects.size(); i++)
	{
		StaticObject* p = m_static_objects[i].get();
		Gifts* gift = dynamic_cast<Gifts*>(p);

		//checks if activated a gift
		if (gift)
		{
			if (gift->isActivated())
			{
				gift->doYourThing(controller, m_dwarfs);
			}
		}

		Teleport* port = dynamic_cast<Teleport*>(p);

		//checks if activated a teleport, if so checks if there was a 
		//collision after the transition in the teleport, if so handles the collision.
		if (port)
		{
			if (port->isActivated())
			{
				for (auto& unmovable : m_static_objects)
				{
					if (gameObject.checkCollision(*unmovable))
					{
						gameObject.handleCollision(*unmovable);
					}

				}
				port->deactivate();
			}
		}
	}

	//replace the orc with a key
	for (int i = 0; i < m_static_objects.size(); i++)
	{
		if (m_static_objects[i]->toReplace())
		{
			auto sprite = m_static_objects[i]->getSprite();
			sprite.setTexture(Resources::instance().getTexture(key));
			m_static_objects.push_back(std::make_unique<Key>(sprite));
			m_static_objects[i]->deleteObject();
		}
	}

	//erase all the object that need to be erased (fire/orc)
	std::erase_if(m_static_objects, [](const auto& object) { return object->toDelete(); });	
}
 
//connects each pair of following teleports
void Board::connectPortals() const
{
	int counter = 0;
	Teleport* teleport[] = { 0, 0 };


	for (int index = 0; index < m_static_objects.size(); index++)
	{
		StaticObject* p = m_static_objects[index].get();

		Teleport* portal = dynamic_cast<Teleport*>(p);

		if (portal)
		{
			teleport[counter] = portal;
			counter++;
		}

		//each teleport have the position of his following teleport
		if (counter == 2)
		{
			teleport[0]->setMatePosition(teleport[1]->getPosition());
			teleport[1]->setMatePosition(teleport[0]->getPosition());
			counter = 0;
		}
	}
}

//handles the movement of the dwarfs
void Board::moveDwarfs(const float deltaTime, const int player_index) const
{
	 
	for (int i = 0; i < m_dwarfs.size(); i++)
	{
		//saves the previous position
		m_dwarfs[i]->setPreviousPosition(m_dwarfs[i]->getPosition());

		//makes the move
		m_dwarfs[i]->move(deltaTime, *m_dynamic_objects[player_index]);

		//checks for collision
		for (auto& unmovable : m_static_objects)
		{
			if (m_dwarfs[i]->checkCollision(*unmovable))
			{
				m_dwarfs[i]->handleCollision(*unmovable);
				//break;

				StaticObject* p = unmovable.get();

				Teleport* port = dynamic_cast<Teleport*>(p);

				//checks if activated a teleport, if so checks if there was a 
				//collision after the transition in the teleport, if handle the collision.
				if (port)
				{
					if (port->isActivated())
					{
						for (auto& unmovable2 : m_static_objects)
						{
							if (m_dwarfs[i]->checkCollision(*unmovable2))
							{
								m_dwarfs[i]->handleCollision(*unmovable2);
							}

						}
						port->deactivate();
					}
				}
			}
		}

		//checks for collision
		for (auto& movable : m_dynamic_objects)
		{
			if (m_dwarfs[i]->checkCollision(*movable))
			{
				m_dwarfs[i]->handleCollisionWithDynamic();
			}
		}

	}
}

//creates the info bar that displays the time, level and the key status
void Board::drawInfo(Controller& controller)
{
	auto window = controller.getWindow();
	auto font = Resources::instance().getFont(0);
	auto time = controller.getTime();
	auto level = controller.getLevel() + 1;

	std::string myTime = std::to_string((int)time.asSeconds());
	std::string myLevel = std::to_string(level);

	sf::RectangleShape bar;
	bar.setSize(sf::Vector2f(600.f, 100.f));
	bar.setFillColor(sf::Color(255, 255, 255, 170));
	bar.setOutlineColor(sf::Color::Black);
	bar.setOutlineThickness(2);
	bar.setOrigin(bar.getGlobalBounds().width / 2.0f, bar.getGlobalBounds().height / 2.0f);
	bar.setPosition(window->getSize().x / 2.0f, m_board.getGlobalBounds().top);

	sf::Text t_level;
	t_level.setFont(font);
	t_level.setStyle(sf::Text::Bold);
	t_level.setString("LEVEL: " + myLevel);
	t_level.setCharacterSize(30);
	t_level.setFillColor(sf::Color(0, 171, 255, 255));
	t_level.setOutlineColor(sf::Color::Black);
	t_level.setOutlineThickness(1);
	t_level.setPosition(bar.getGlobalBounds().left + bar.getGlobalBounds().width - t_level.getGlobalBounds().width - 10, bar.getGlobalBounds().top + 5);

	sf::Text t_key;
	if (m_key)
	{
		t_key.setFillColor(sf::Color(0, 171, 255, 255));
		t_key.setOutlineColor(sf::Color(0, 0, 0, 255));
	}
	else
	{
		t_key.setFillColor(sf::Color(0, 0, 0, 50));
		t_key.setOutlineColor(sf::Color(0, 0, 0, 0));
	}
	t_key.setString("KEY");
	t_key.setFont(font);
	t_key.setStyle(sf::Text::Bold);
	t_key.setCharacterSize(30);
	
	t_key.setOutlineThickness(1);
	t_key.setPosition(window->getSize().x / 2 - t_key.getGlobalBounds().width / 2, bar.getGlobalBounds().top + 5);

	sf::Text t_time;
	t_time.setFont(font);
	t_time.setStyle(sf::Text::Bold);
	t_time.setString("TIME: " + myTime);
	t_time.setCharacterSize(30);
	t_time.setFillColor(sf::Color(0, 171, 255, 255));
	t_time.setOutlineColor(sf::Color::Black);
	t_time.setOutlineThickness(1);
	t_time.setPosition(bar.getGlobalBounds().left + 10, bar.getGlobalBounds().top + 5);

	window->draw(bar);
	window->draw(t_time);
	window->draw(t_key);
	window->draw(t_level);
}

//creates the gifts
//will create up to 3 different gifts randomly 
//in random places on the map
//from 4 different gift options
void Board::createGifts()
{
	int num_of_gifts = rand() % 4;

	bool collosion;
	int min_x, max_x, min_y, max_y, position_x = 0, position_y = 0, giftType;

	//the boundaries of the area from which the location can be randomly selected
	min_x = (int)m_board.getGlobalBounds().left;
	max_x = (int)(min_x + m_board.getGlobalBounds().width - MAP_SCALE * 2);
	min_y = (int)m_board.getGlobalBounds().top;
	max_y = (int)(min_y + m_board.getGlobalBounds().height - MAP_SCALE * 2);

	sf::RectangleShape object;

	for (int i = 0; i < num_of_gifts; i++)
	{
		collosion = true;

		//as long the random position isnt good
		while (collosion)
		{
			collosion = false;

			position_x = min_x + rand() % ((max_x + 1) - min_x);	//gets random x position
			position_y = min_y + rand() % ((max_y + 1) - min_y);	//gets random y position

			object.setSize(sf::Vector2f(64.f, 64.f));
			object.setPosition(sf::Vector2f((float)position_x, (float)position_y));

			//checks if the possition is clear or not
			for (auto& unmovable : m_static_objects)
				if (object.getGlobalBounds().intersects(unmovable->getSprite().getGlobalBounds()))
				{
					collosion = true;
					break;
				}

			for (auto& movable : m_dynamic_objects)
				if (object.getGlobalBounds().intersects(movable->getSprite().getGlobalBounds()))
				{
					collosion = true;
					break;
				}
		}

		auto sprite = sf::Sprite();
		sprite.setPosition(sf::Vector2f((float)position_x, (float)position_y));
		sprite.setTexture(Resources::instance().getTexture(gift));

		//dont creat dwarf gifts if there wans dwarfs at the level
		if (m_dwarfs.size() != 0)
			giftType = rand() % 4;
		else
			giftType = rand() % 2;

		switch (giftType)
		{
		//+ 10 seconds
		case 0:
			m_static_objects.push_back(std::make_unique<TimeGift>(sprite, 10));
			break;
		//- 10 seconds
		case 1:
			m_static_objects.push_back(std::make_unique<TimeGift>(sprite, -10));
			break;
		//deletes all the dwarfs
		case 2:
			m_static_objects.push_back(std::make_unique<BoardGift>(sprite, 0));
			break;
		//slows down all the dwarfs
		case 3:
			m_static_objects.push_back(std::make_unique<BoardGift>(sprite, 1));
			break;
		}
	}
}

int Board::getNumberOfCharacters() const
{
	return (int)m_dynamic_objects.size();
}

int Board::absolutPosition_x(const int num) const
{
	return (int)((m_board_position.x - m_board_size.x / 2) + num * MAP_SCALE);
}

int Board::absolutPosition_y(const int num) const
{
	return (int)((m_board_position.y - m_board_size.y / 2) + num * MAP_SCALE);
}

void Board::changePlayersVisual(const int index) const
{
	m_dynamic_objects[index]->changeColor();
}