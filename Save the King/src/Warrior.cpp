#include "Warrior.h"
#include "StaticObject.h"




Warrior::Warrior(const sf::Sprite& sprite) : DynamicObject(sprite)
{
    GameObject::changeColor();
}

void Warrior::handleCollision(GameObject& gameObject)
{
    if (&gameObject == this) return;
    // double dispatch
    gameObject.handleCollision(*this);
}

void Warrior::handleCollision(Wall&)
{
    Resources::instance().playSound(hit_wall);
    this->setPosition(this->getPreviousPosition());
}

void Warrior::handleCollision(Gate&)
{
    this->setPosition(this->getPreviousPosition());
}

void Warrior::handleCollision(Fire&)
{
    this->setPosition(this->getPreviousPosition());
}

void Warrior::handleCollision(Throne&)
{
    this->setPosition(this->getPreviousPosition());
}

void Warrior::handleCollision(Teleport& object)
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

void Warrior::handleCollision(Dwarf&)
{
    this->setPosition(this->getPreviousPosition());
}
