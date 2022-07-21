#include "Mage.h"
#include "StaticObject.h"




Mage::Mage(const sf::Sprite& sprite) : DynamicObject(sprite)
{
    GameObject::changeColor();
}

void Mage::handleCollision(GameObject& gameObject)
{
    if (&gameObject == this) return;
    // double dispatch
    gameObject.handleCollision(*this);
}

void Mage::handleCollision(Wall&)
{
    Resources::instance().playSound(hit_wall);
    this->setPosition(this->getPreviousPosition());
}

void Mage::handleCollision(Gate&)
{
    this->setPosition(this->getPreviousPosition());
}

void Mage::handleCollision(Orc&)
{
    Resources::instance().playSound(orc_groan);
    this->setPosition(this->getPreviousPosition());
}

void Mage::handleCollision(Throne&)
{
    this->setPosition(this->getPreviousPosition());
}

void Mage::handleCollision(Dwarf&)
{
    this->setPosition(this->getPreviousPosition());
}
