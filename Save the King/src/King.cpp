#include "King.h"
#include "StaticObject.h"




King::King(const sf::Sprite& sprite) : DynamicObject(sprite), m_throne(false)
{
    GameObject::changeColor();
}

void King::handleCollision(GameObject& gameObject)
{
    if (&gameObject == this) return;
    // double dispatch
    gameObject.handleCollision(*this);
}

void King::handleCollision(Wall&)
{
    this->setPosition(this->getPreviousPosition());
    Resources::instance().playSound(hit_wall);
}

void King::handleCollision(Gate&)
{
    this->setPosition(this->getPreviousPosition());
}

void King::handleCollision(Fire&)
{
    this->setPosition(this->getPreviousPosition());
}

void King::handleCollision(Orc&)
{
    Resources::instance().playSound(orc_groan);
    this->setPosition(this->getPreviousPosition());
}

void King::handleCollision(Teleport& object)
{
    Resources::instance().playSound(teleportation);

    auto position = object.getMatePosition();
    sf::Vector2f prevPosition = this->getPreviousPosition();
    sf::Vector2f curentPosition = this->getPosition();
    sf::Vector2f offset;

    offset.x = curentPosition.x - prevPosition.x;
    offset.y = curentPosition.y - prevPosition.y;

    position.x += offset.x * 32;
    position.y += offset.y * 32;

    this->setPosition(position);
}

void King::handleCollision(Dwarf&)
{
    this->setPosition(this->getPreviousPosition());
}

void King::handleCollision(Throne&)
{
    Resources::instance().playSound(level_won);
    m_throne = true;
}

bool King::isKingReachedThrone()
{
    return m_throne;
}
