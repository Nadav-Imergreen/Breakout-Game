#pragma once
#include "Gift.h"


class ResizePaddleGift : public Gift
{
public:
	ResizePaddleGift(const sf::Vector2f& position, const sf::Vector2f& size);

	virtual void handleCollision(GameObject& otherobj) override;
	virtual void handleCollision(Paddle& paddle) override;

private:

};