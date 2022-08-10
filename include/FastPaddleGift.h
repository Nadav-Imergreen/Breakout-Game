#pragma once
#include "Gift.h"


class FastPaddleGift : public Gift
{
public:
	FastPaddleGift(const sf::Vector2f& position, const sf::Vector2f& size);

	virtual void handleCollision(GameObject& otherobj) override;
	virtual void handleCollision(Paddle& paddle) override;

private:

};