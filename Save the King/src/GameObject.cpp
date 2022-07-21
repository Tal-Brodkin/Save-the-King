#include "GameObject.h"




//constructor taking Sprite
GameObject::GameObject(const sf::Sprite& sprite) : m_sprite(sprite)
{
}


void GameObject::draw(sf::RenderWindow* window)
{
	window->draw(m_sprite);
}

sf::Sprite GameObject::getSprite() const
{
	return m_sprite;
}

sf::Vector2f GameObject::getPosition() const
{
	return m_sprite.getPosition();
}

void GameObject::makeMove(const sf::Vector2f& offset)
{
	m_sprite.move(offset);
}

void GameObject::setPosition(const sf::Vector2f& position)
{
	m_sprite.setPosition(position);
}

void GameObject::changeColor()
{
	if (m_sprite.getColor() == sf::Color(179, 179, 179, 160))
		m_sprite.setColor(sf::Color::White);
	else
		m_sprite.setColor(sf::Color(179, 179, 179, 160));
}

bool GameObject::checkCollision(const GameObject& other) const
{
	return m_sprite.getGlobalBounds().intersects(other.getSprite().getGlobalBounds());
}
