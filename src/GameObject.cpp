#include "GameObject.h"


GameObject::GameObject(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture)
	 :m_sprite(*texture)
{
	m_sprite.setPosition(position);
	m_sprite.setOrigin({ m_sprite.getGlobalBounds().width / 2 , m_sprite.getGlobalBounds().height / 2 });
	m_sprite.scale({ size.x / m_sprite.getGlobalBounds().width, size.y / m_sprite.getGlobalBounds().height });
}

GameObject::GameObject(const sf::Vector2f& position, const sf::Vector2f& size)
{
	m_rect.setSize(size);
	m_rect.setFillColor(sf::Color::White);
	m_rect.setPosition(position);
}

void GameObject::setPosition(sf::Vector2f position)
{
	m_sprite.setPosition(position);
}

sf::FloatRect GameObject::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

sf::FloatRect GameObject::getGlobalBoundsRect() const
{
	return m_rect.getGlobalBounds();
}

bool GameObject::collideWith(const GameObject& otherobj) const
{
	return getGlobalBounds().intersects(otherobj.getGlobalBounds());
}

bool GameObject::collideWithRect(const GameObject& otherobj) const
{
	return getGlobalBounds().intersects(otherobj.getGlobalBoundsRect());
}

sf::Vector2f GameObject::getPosition() const
{
	return m_sprite.getPosition();
}

void GameObject::drawSprite(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

void GameObject::drawRect(sf::RenderWindow& window) const
{
	window.draw(m_rect);
}