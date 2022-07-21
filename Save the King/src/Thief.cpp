#include "Thief.h"
#include "StaticObject.h"




Thief::Thief(const sf::Sprite& sprite) : DynamicObject(sprite), m_key(false)
{
    GameObject::changeColor();
}

void Thief::handleCollision(GameObject& gameObject)
{
    if (&gameObject == this) return;
    // double dispatch
    gameObject.handleCollision(*this);
}

void Thief::handleCollision(Wall&)
{
    Resources::instance().playSound(hit_wall);
    this->setPosition(this->getPreviousPosition());
}

void Thief::handleCollision(Gate& gameObject)
{
    if (m_key)
    {
        gameObject.deleteObject();
        m_key = false;
        Resources::instance().playSound(open_door);
    }
    else
    {
        Resources::instance().playSound(locked_door);
        this->setPosition(this->getPreviousPosition());
    }
}

void Thief::handleCollision(Fire&)
{
    this->setPosition(this->getPreviousPosition());
}

void Thief::handleCollision(Orc&)
{
    Resources::instance().playSound(orc_groan);
    this->setPosition(this->getPreviousPosition());
}

void Thief::handleCollision(Key&)
{
    Resources::instance().playSound(key_pickup);
    m_key = true;
}

void Thief::handleCollision(Throne&)
{
    this->setPosition(this->getPreviousPosition());
}

void Thief::handleCollision(Teleport& object)
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

void Thief::handleCollision(Dwarf&)
{
    this->setPosition(this->getPreviousPosition());
}

bool Thief::isThiefHasKey()
{
    return m_key;
}
