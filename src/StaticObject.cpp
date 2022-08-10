#include "StaticObject.h"

StaticObject::StaticObject(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture)
	:GameObject(position, size, texture)
{
}

StaticObject::StaticObject(const sf::Vector2f& position, const sf::Vector2f& size)
:GameObject(position, size)
{
}

bool StaticObject::haveToDelete() const
{
	return m_deleted;
}