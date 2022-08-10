#pragma once
#include "GameObject.h"


class MovingObject: public GameObject
{
public:
	MovingObject(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture);

	virtual void move(const sf::Time& delta) = 0;

protected:
	sf::Sound m_sound;

private:
	
};