#include "StaticObject.h"




StaticObject::StaticObject(const sf::Sprite& sprite) : GameObject(sprite)
{
    m_delete = false;
    m_replace = false;
}

bool StaticObject::toDelete()
{
    return m_delete;
}

void StaticObject::deleteObject()
{
    m_delete = true;
}

bool StaticObject::toReplace()
{
    return m_replace;
}

void StaticObject::replace()
{
    m_replace = true;
}
