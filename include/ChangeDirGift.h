#pragma once
#include "Gift.h"


class ChangeDirGift : public Gift
{
public:
	ChangeDirGift(const sf::Vector2f& position, const sf::Vector2f& size);

	virtual void handleCollision(GameObject& otherobj) override;
	virtual void handleCollision(Paddle& paddle) override;

private:

};