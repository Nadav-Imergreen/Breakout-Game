#pragma once
#include "GameObject.h"


class StaticObject : public GameObject
{
public:
	StaticObject(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture);
	StaticObject(const sf::Vector2f& position, const sf::Vector2f& size);
	
	bool haveToDelete() const;
	virtual void handleCollision(Frame& frame) override { }

protected:
	bool m_deleted = false;		//to know if a specific brick/gift need to be deleted

private:

};