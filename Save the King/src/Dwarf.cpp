#include "Dwarf.h"
#include "Teleport.h"
#include "StaticObject.h"




Dwarf::Dwarf(const sf::Sprite& sprite) : DynamicObject(sprite), m_direction(0,1), m_speed(100), m_time(0)
{
    m_type = rand() % 2; 
}

void Dwarf::handleCollisionWithDynamic()
{
    this->setPosition(this->getPreviousPosition());
}

void Dwarf::handleCollision(GameObject& gameObject)
{
    if (&gameObject == this) return;
    // double dispatch
    gameObject.handleCollision(*this);
}

void Dwarf::handleCollision(Wall&)
{
    //Resources::instance().playSound(hit_wall);
    this->setPosition(this->getPreviousPosition());
    changeDirection();
}

void Dwarf::handleCollision(Fire&)
{
    this->setPosition(this->getPreviousPosition());
    changeDirection();
}

void Dwarf::handleCollision(Gate&)
{
    this->setPosition(this->getPreviousPosition());
    changeDirection();
}

void Dwarf::handleCollision(Orc&)
{
    Resources::instance().playSound(orc_groan);
    this->setPosition(this->getPreviousPosition());
    changeDirection();
}

void Dwarf::handleCollision(Throne&)
{
    this->setPosition(this->getPreviousPosition());
    changeDirection();
}

void Dwarf::handleCollision(Teleport& object)
{
    Resources::instance().playSound(teleportation);
    auto position = object.getMatePosition();
    sf::Vector2f prevPosition = this->getPreviousPosition();
    sf::Vector2f curentPosition = this->getPosition();
    sf::Vector2f offset;

    offset.x = this->getDirection().x;
    offset.y = this->getDirection().y;

    position.x += offset.x * 64;
    position.y += offset.y * 64;

    this->setPosition(position);
}

void Dwarf::move(const float deltaTime, GameObject& player)
{
    //regular dwarf, changes direction randomly every 2 seconds
    if (m_type == 0)
    {
        m_time += deltaTime;
        if (m_time > 2.0f)
        {
            changeDirection();
            m_time = 0;
        }
        this->makeMove(sf::Vector2f(deltaTime * m_direction.x * m_speed, deltaTime * m_direction.y * m_speed));
    }
    //smart dwarf, following the players position
    else
    {
        auto dwarf_position = this->getPosition();
        auto player_position = player.getPosition();

        auto new_direction_x = player_position.x - (int)dwarf_position.x;
        auto new_direction_y = player_position.y - (int)dwarf_position.y;

        if (new_direction_x > 1)
            new_direction_x = 1;
        else if (new_direction_x < -1)
            new_direction_x = -1;
        else
            new_direction_x = 0;

        if (new_direction_y > 1)
            new_direction_y = 1;
        else if (new_direction_y < -1)
            new_direction_y = -1;
        else
            new_direction_y = 0;

        this->makeMove(sf::Vector2f(deltaTime * new_direction_x * m_speed, deltaTime * new_direction_y * m_speed));
    }
}


void Dwarf::changeDirection()
{
    m_direction.x = (float)-1 + rand() % 3;
    m_direction.y = (float)-1 + rand() % 3;

    while (m_direction.x == 0 && m_direction.y == 0)
    {
        m_direction.x = (float)-1 + rand() % 3;
        m_direction.y = (float)-1 + rand() % 3;
    }
}

sf::Vector2f Dwarf::getDirection() const
{
    return m_direction;
}

void Dwarf::slowDown()
{
    m_speed = 20;
}
